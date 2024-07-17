#include "CExtractActions.h"
#include "OpenHoldemFunctions.h"
#include "CLogging.h"
#include "CSymbols.h"
#include "user.h"

#include <locale>         // std::locale, std::tolower
#include <iostream>       // std::cout
#include <map>


int CExtractActions::GetLastRaiser(bool previous /*= false*/)
{
	int amount = 0;
	int index = 0;
	bool raise_found = false;
	int betround = g_symbols->get_betround();
	int times_acted = _current_hand_info._times_acted[betround];

	for (int ndx = 0; ndx < g_symbols->get_nchairs(); ndx++)
	{
		if (!_current_hand_info._player_actions[ndx]._b_was_in_game) {
			continue;
		}
		if (previous && _current_hand_info._player_actions[ndx]._actions[betround][times_acted]._num_raises < 1)
			continue;
		double bet_amount;
		if (previous)
			bet_amount = _current_hand_info._player_actions[ndx]._actions[betround][times_acted]._amount;
		else
			bet_amount = GetPlayerBet(ndx);
		if (betround == 1 && bet_amount <= g_symbols->get_bblind()) {
			continue;
		}
		if (bet_amount > amount) {
			amount = bet_amount;
			index = ndx;
			raise_found = true;
		}
	}
	if (raise_found)
		return index;
	else
		return -1;
}

void CExtractActions::ExtractActionsReset()
{
	_current_hand_info.NewHand();
	//_opp_model.HandReset();

	_b_new_game		= true;
	_b_new_round	= true;
	_b_skip_missed_action = false;
	_prev_betround	= k_undefined;
	_start_index = (g_symbols->get_betround() == 1 ? g_symbols->get_bigblindchair() + 1 : g_symbols->get_dealerchair() + 1);
}

void CExtractActions::ExtractPreviousRoundActions()
{
	/////////////////////////////////////////////////
	// PICKUP MISSING ACTIONS FROM PREVIOUS ROUND  //
	// if it didn't come back to hero either:      //
	// a) hero folded                              //
	// b) only fold check or call possible         //
	/////////////////////////////////////////////////

	for (int ndx = g_symbols->get_userchair() + 1;; ndx++)
	{
		// VERIFY ME - HU + Dealer Chair
		int stop_chair = g_symbols->get_userchair();
		int chair_ndx = ndx % g_symbols->get_nchairs();

		if ( chair_ndx == stop_chair )
			break;

		if ( !_current_hand_info._player_actions[chair_ndx]._b_was_in_game )
			continue;

		int betround = g_symbols->get_betround();
		int prev_times_acted = _current_hand_info._times_acted[_prev_betround];
		double current_bet = g_symbols->get_currentbet(chair_ndx);
		double balance = g_symbols->get_balance(chair_ndx);

		// Folded previous betround
		if ( !is_active_bit(chair_ndx, g_symbols->get_playersplayingbits()) )
		{
			_current_hand_info.RecordPlayerAction(_prev_betround,
				chair_ndx,
				actionFold,
				_current_hand_info._player_actions[chair_ndx]._prev_bet[_prev_betround],
				balance);
			setPlayerAction(chair_ndx, 0, 0);
		}
		// Checked
		else if ( IsEqual(_current_hand_info._player_actions[chair_ndx]._actions[_prev_betround][prev_times_acted]._balance, balance) )
		{
			_current_hand_info.RecordPlayerAction(_prev_betround,
				chair_ndx,
				actionCheck,
				_current_hand_info._amount_to_call[_prev_betround],
				balance);
			setPlayerAction(chair_ndx, 1, 0);

			//_opp_model.ModelOpponent(chair_ndx, _prev_betround, actionCheck);
		}
		// Called
		else if ( _current_hand_info._player_actions[chair_ndx]._actions[_prev_betround][prev_times_acted]._balance > balance )
		{
			_current_hand_info.RecordPlayerAction(_prev_betround,
				chair_ndx,
				actionCall,
				_current_hand_info._amount_to_call[_prev_betround],
				balance);
			setPlayerAction(chair_ndx, 2, int(current_bet * 100));

			//_opp_model.ModelOpponent(chair_ndx, _prev_betround, actionCall);
		}
	}
}

bool CExtractActions::ExtractMissedActions()
{
	///////////////////////////////////////////////////
	// Extract Missed Actions of players behind hero //
	///////////////////////////////////////////////////

	for (int ndx = _start_index;; ndx++)
	{
		// VERIFY ME - HU + Dealer Chair
		int chair_ndx = ndx % g_symbols->get_nchairs();
		int betround = g_symbols->get_betround();
		int stop_chair;

		if (chair_ndx == g_symbols->get_userchair()) {
			if (betround == 1)
				stop_chair = g_symbols->get_bigblindchair();
			else
				stop_chair = g_symbols->get_dealerchair();
			if (chair_ndx == stop_chair && GetLastRaiser(true) == -1 && g_symbols->get_nopponentscalling() == 0)
				return true;
		}

		stop_chair = _stop_index;
		if (chair_ndx == stop_chair) {
			return true;
		}

		if (!_current_hand_info._player_actions[chair_ndx]._b_was_in_game ||
			!GetPlayerPlaying(chair_ndx)) {
			_start_index = _start_index++ % g_symbols->get_nchairs();
			continue;
		}

		if (GetPlayerActing(chair_ndx) == "true")
			return false;

		std::locale loc;
		string action = GetPlayerAction(chair_ndx);
		for (auto& c : action) {
			c = std::tolower(c, loc);
		}
		if (action != "fold" && action != "check" && action != "call" && 
			action != "bet" && action != "raise" && action != "allin" && action != "all-in")
			return false;

		int times_acted = _current_hand_info._times_acted[betround];
		double balance = g_symbols->get_balance(chair_ndx);
		double amountToCall = _current_hand_info._amount_to_call[betround];
		//double amountToCall = g_symbols->get_call();
		//double current_bet = g_symbols->get_currentbet(chair_ndx);
		//double current_bet = GetPlayerBet(chair_ndx);
		int length;
		string region = "p" + to_string(chair_ndx) + "bet";
		string bet = ScrapeTableMapRegion(&region[0], length);
		if (bet.find("$") != -1)
			bet.replace(bet.find("$"), 1, "");
		if (bet.find("€") != -1)
			bet.replace(bet.find("€"), 1, "");
		if (bet.find(",") != -1)
			bet.replace(bet.find(","), 1, ".");
		double current_bet;
		try {
			current_bet = stod(bet);
		}
		catch (...) {
			current_bet = 0.0;
		}

		if (action == "fold") {
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionFold,
				0,
				balance);
			setPlayerAction(chair_ndx, 0, 0);
			_start_index = _start_index++ % g_symbols->get_nchairs();
		}
		else if (action == "check") {
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCheck,
				0,
				balance);
			setPlayerAction(chair_ndx, 1, 0);
			_start_index = _start_index++ % g_symbols->get_nchairs();
		}
		else if (action == "call") {
			if (current_bet == 0)
				current_bet = amountToCall;
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCall,
				current_bet,
				balance);
			setPlayerAction(chair_ndx, 2, int(current_bet * 100));
			_start_index = _start_index++ % g_symbols->get_nchairs();
		}
		else if (action == "bet") {
			if (current_bet == 0)
				current_bet = GetPlayerBet(chair_ndx);
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);
			setPlayerAction(chair_ndx, 3, int(current_bet * 100));
			_stop_index = chair_ndx;
			_start_index = _start_index++ % g_symbols->get_nchairs();
		}
		else if (action == "raise") {
			if (current_bet == 0)
				current_bet = GetPlayerBet(chair_ndx);
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);
			setPlayerAction(chair_ndx, 4, int(current_bet * 100));
			_stop_index = chair_ndx;
			_start_index = _start_index++ % g_symbols->get_nchairs();
		}
		else if (action == "allin" || action == "all-in") {
			if (current_bet == 0)
				current_bet = GetPlayerBet(chair_ndx);
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);
			setPlayerAction(chair_ndx, 4, int(current_bet * 100));
			_stop_index = chair_ndx;
			_start_index = _start_index++ % g_symbols->get_nchairs();
		}

		if (g_symbols->get_nplayersplaying() < 2) {
			return true;
		}

		if (betround == 1)
			stop_chair = _current_hand_info._bb_chair; // g_symbols->get_bigblindchair();
		else
			stop_chair = _current_hand_info._prev_dealer_chair; // g_symbols->get_dealerchair();
		if (chair_ndx == stop_chair && GetLastRaiser(true) == -1)
			return true;
	}
}

void CExtractActions::ExtractPreviousTimesActedActions()
{
	////////////////////////////////////////////
	// Extract Actions of players behind hero //
	////////////////////////////////////////////

	for (int ndx = g_symbols->get_userchair() + 1;; ndx++)
	{
		// VERIFY ME - HU + Dealer Chair
		int chair_ndx = ndx % g_symbols->get_nchairs();
		int stop_chair = (g_symbols->get_dealerchair() + 1) % g_symbols->get_nchairs();
		//int stop_chair = g_symbols->get_userchair();

		if ( chair_ndx == stop_chair )
			break;

		if ( !_current_hand_info._player_actions[chair_ndx]._b_was_in_game )
			continue;

		int betround = g_symbols->get_betround();
		int times_acted = _current_hand_info._times_acted[betround];
		double current_bet = _current_hand_info._player_actions[chair_ndx]._actions[betround][times_acted]._amount;
		//double current_bet = GetPlayerBet(chair_ndx);
		//double current_bet = g_symbols->get_currentbet(chair_ndx);
		double balance = g_symbols->get_balance(chair_ndx);

		double amountToCall = _current_hand_info._amount_to_call[betround];
		// Folded previous times acted
		if ( current_bet < amountToCall)
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionFold,
				_current_hand_info._player_actions[chair_ndx]._prev_bet[betround],
				balance);
			setPlayerAction(chair_ndx, 0, 0);
		}
		// Checked
		else if (IsEqual(_current_hand_info._player_actions[chair_ndx]._actions[betround][times_acted]._balance, balance) &&
			IsEqual(current_bet, _current_hand_info._player_actions[chair_ndx]._prev_bet[betround]))
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCheck,
				_current_hand_info._amount_to_call[betround],
				balance);
			setPlayerAction(chair_ndx, 1, 0);

			//_opp_model.ModelOpponent(chair_ndx, betround, actionCheck);
		}
		// Call
		else if ( IsEqual(current_bet, amountToCall) ||
			( IsEqual(balance, 0) && current_bet > epsilon ) )
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCall,
				_current_hand_info._amount_to_call[betround],
				balance);
			setPlayerAction(chair_ndx, 2, int(current_bet * 100));

			//_opp_model.ModelOpponent(chair_ndx, betround, actionCall);
		}
		// Raise
		else if ( current_bet > amountToCall)
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);
			setPlayerAction(chair_ndx, 3, int(current_bet * 100));

			//_opp_model.ModelOpponent(chair_ndx, betround, actionBetRaise);
		}
	}
}


void CExtractActions::ExtractCurrentActions()
{
	//////////////////////////////////////////////
	// Extract Actions of players ahead of hero //
	//////////////////////////////////////////////

	for (size_t ndx = _current_hand_info._current_actor + 1;; ndx++)
	{
		int chair_ndx = ndx % g_symbols->get_nchairs();

		if (chair_ndx == g_symbols->get_userchair())
			break;

		if (!_current_hand_info._player_actions[chair_ndx]._b_was_in_game ||
			!GetPlayerPlaying(chair_ndx))
			continue;

		int betround = g_symbols->get_betround();
		int prev_times_acted = _current_hand_info._times_acted[_prev_betround];
		double current_bet = g_symbols->get_currentbet(chair_ndx);
		//double current_bet = GetPlayerBet(chair_ndx);
		double balance = g_symbols->get_balance(chair_ndx);

		/*
		g_log->WriteLog(eSeverityInfo, eCatExtractActions, "current_actor:%d cb:%g pb:%g\n",
			ndx,
			current_bet,
			_current_hand_info._amount_to_call[betround]);
		*/

		// Fold
		if (current_bet < _current_hand_info._amount_to_call[betround])
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionFold,
				0,
				balance);
			setPlayerAction(chair_ndx, 0, 0);
		}
		// Checked
		else if (IsEqual(current_bet, _current_hand_info._amount_to_call[betround]) &&
			IsEqual(current_bet, _current_hand_info._player_actions[chair_ndx]._prev_bet[betround]))
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCheck,
				0,
				balance);
			setPlayerAction(chair_ndx, 1, 0);

			//_opp_model.ModelOpponent(chair_ndx, betround, actionCheck);
		}
		// Call - player may have less than call amount and go all-in
		else if ((IsEqual(current_bet, _current_hand_info._amount_to_call[betround]) &&
			_current_hand_info._amount_to_call[betround] > epsilon) ||
			(IsEqual(balance, .0) && current_bet > epsilon))
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionCall,
				current_bet,
				balance);
			setPlayerAction(chair_ndx, 2, int(current_bet * 100));

			//_opp_model.ModelOpponent(chair_ndx, betround, actionCall);
		}
		// Raise
		else if (current_bet > _current_hand_info._amount_to_call[betround])
		{
			_current_hand_info.RecordPlayerAction(betround,
				chair_ndx,
				actionBetRaise,
				current_bet,
				balance);
			if (g_symbols->get_ncurrentbets() > 0)
				setPlayerAction(chair_ndx, 4, int(current_bet * 100));
			else
				setPlayerAction(chair_ndx, 3, int(current_bet * 100));
			_stop_index = chair_ndx;

			//_opp_model.ModelOpponent(chair_ndx, betround, actionBetRaise);
		}
	}
}

void CExtractActions::ExtractActionsNewGame()
{
	//////////////
	// NEW GAME //
	//////////////

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Starting New Hand\n");
	_current_hand_info.NewHand();
	//_opp_model.HandReset();

	////////////////////////
	// We Know the Blinds //
	////////////////////////

	// account for missing small blind
	if(g_symbols->get_smallblindchair() != k_undefined)
	{
		_current_hand_info.RecordPlayerAction(g_symbols->get_betround(),
			g_symbols->get_smallblindchair(),
			actionPostedSB,
			g_symbols->get_sblind(),
			g_symbols->get_balance(g_symbols->get_smallblindchair()));
	}
	_current_hand_info.RecordPlayerAction(g_symbols->get_betround(),
		g_symbols->get_bigblindchair(),
		actionPostedBB,
		g_symbols->get_bblind(),
		g_symbols->get_balance(g_symbols->get_bigblindchair()));

	//////////////////////////////////
	// Remaining actions up to hero //
	//////////////////////////////////

	ExtractCurrentActions();

	_b_new_game = false;
}

void CExtractActions::ExtractActionsNewRound()
{
	///////////////
	// NEW ROUND //
	///////////////

	//g_log->WriteLog(eSeverityInfo, eCatInfo, "Picking missed Actions\n");
	//ExtractPreviousRoundActions();

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Starting New Round\n");
	_current_hand_info.NewBettingRound();
	ExtractCurrentActions();
}

void CExtractActions::ExtractRemainingActions()
{
	g_log->WriteLog(eSeverityInfo, eCatInfo, "Picking missed Actions\n");
	ExtractPreviousTimesActedActions();

	g_log->WriteLog(eSeverityInfo, eCatInfo, "Extracting current Round\n");
	ExtractCurrentActions();
}

void CExtractActions::ExtractActions()
{
	_b_new_round = (g_symbols->get_betround() > ePreflop && (g_symbols->get_betround() != _prev_betround));
	
	if (_b_new_game || _b_new_round) {
		g_log->WriteLog(eSeverityInfo, eCatGeneral, "Board: %c%c %c%c %c%c %c%c %c%c\n",
			Rank_ASC(g_symbols->get_$$cr0()), Suit52_ASC(g_symbols->get_$$cs0()),
			Rank_ASC(g_symbols->get_$$cr1()), Suit52_ASC(g_symbols->get_$$cs1()),
			Rank_ASC(g_symbols->get_$$cr2()), Suit52_ASC(g_symbols->get_$$cs2()),
			Rank_ASC(g_symbols->get_$$cr3()), Suit52_ASC(g_symbols->get_$$cs3()),
			Rank_ASC(g_symbols->get_$$cr4()), Suit52_ASC(g_symbols->get_$$cs4())
		);
		g_log->WriteLog(eSeverityInfo, eCatGeneral, "Player Cards: %c%c %c%c\n",
			Rank_ASC(g_symbols->get_$$pr0()), Suit52_ASC(g_symbols->get_$$ps0()),
			Rank_ASC(g_symbols->get_$$pr1()), Suit52_ASC(g_symbols->get_$$ps1())
		);

		g_log->WriteLog(eSeverityInfo, eCatGeneral, "Pokervalcommon: %u %s\n",
			g_symbols->get_pokervalcommon(), Pokerval_ASC(g_symbols->get_pokervalcommon())
		);
		g_log->WriteLog(eSeverityInfo, eCatGeneral, "Pokerval      : %u %s\n",
			g_symbols->get_pokerval(), Pokerval_ASC(g_symbols->get_pokerval())
		);
	}
	
	if (_b_new_game)
		ExtractActionsNewGame();
	else if (_b_new_round)
		ExtractActionsNewRound();
	/*else
		ExtractCurrentActions();
		//ExtractRemainingActions();*/

	_prev_betround = g_symbols->get_betround();
}
