#include "CHandHistory.h"

#include "CLogging.h"
#include "CSymbols.h"



CHandHistory::CHandHistory()
{
	NewHand();
}

void CHandHistory::NewHand()
{
	_recorded_bot_action	= false;
	_prev_dealer_chair		= g_symbols->get_dealerchair();
	_sb_chair				= g_symbols->get_smallblindchair();
	_bb_chair				= g_symbols->get_bigblindchair();

	memset(_amount_to_call, 0, eRounds*sizeof(_amount_to_call[0]));
	memset(_times_acted, 0, eRounds * sizeof(_times_acted[0]));

	for (int i=0; i < k_max_chairs; i++)
		_player_actions[i].Clear();

	_recorded_bot_action = false;
	_pot_round = .0;
	_n_calls_round = _n_checks_round = _n_raises_round = _n_times_acted = 0;

	// Set players with no balance and no current bet out of the game
	for (int chair_ndx = 0; chair_ndx < g_symbols->get_nchairs(); chair_ndx++)
	{
		if (!is_active_bit(chair_ndx, g_symbols->get_playersseatedbits()))
		{
			_player_actions[chair_ndx]._b_was_in_game = false;
			continue;
		}

		_player_actions[chair_ndx]._actions[ePreflop][0]._balance = g_symbols->get_balance(chair_ndx);
	}
}

void CHandHistory::NewBettingRound()
{
	_recorded_bot_action = false;
	_pot_round = 0;
	_n_calls_round = _n_checks_round = _n_raises_round = _n_times_acted = 0;
	_current_actor = g_symbols->get_dealerchair();

	for (int chair_ndx = 0; chair_ndx < g_symbols->get_nchairs(); chair_ndx++)
	{
		_player_actions[chair_ndx]._actions[g_symbols->get_betround()][0]._balance = g_symbols->get_balance(chair_ndx);
	}
}

// verify me
int CHandHistory::LeftToAct(int chair)
{
	int left_to_act = 0;
	int max_bet_chair = k_undefined;
	double max_bet = 0;

	for (int ndx = chair;; ndx++)
	{
		int chair_ndx = ndx % k_max_chairs;
		int stop_chair = g_symbols->get_dealerchair();

		if (chair_ndx == stop_chair)
			break;

		if (!_player_actions[chair_ndx]._b_was_in_game)
			continue;

		if (g_symbols->get_currentbet(chair_ndx) > max_bet)
		{
			max_bet = g_symbols->get_currentbet(chair_ndx);
			max_bet_chair = chair_ndx;
		}
#if 0
		g_log->WriteLog(eSeverityInfo, eCatInfo, "chair%d, max_bet:%.2f, max_bet_chair:%d, ac_dealpos:%d, ac_betpos:%d\n",
			chair_ndx,
			max_bet,
			max_bet_chair,
			g_symbols->get_ac_dealpos(chair_ndx),
			g_symbols->get_ac_betpos(chair_ndx)
		);
#endif
	}

	int wrap_around_count = 0;
	for (int ndx = chair + 1;; ndx++)
	{
		int chair_ndx = ndx % g_symbols->get_nchairs();
		int stop_chair = max_bet_chair != k_undefined ? (max_bet_chair + 1) % g_symbols->get_nchairs() : (g_symbols->get_dealerchair() + 1) % g_symbols->get_nchairs();

		if (chair_ndx == stop_chair)
			break;

		if (!_player_actions[chair_ndx]._b_was_in_game)
			continue;

		left_to_act++;

#if 0
		g_log->WriteLog(eSeverityInfo, eCatOHMessages, "Chair%d max_bet_chair:%d stopchair:%d - LeftToAct:%d\n",
			chair_ndx,
			max_bet_chair,
			stop_chair,
			left_to_act
		);
#endif
	}


	return left_to_act;
}

void CHandHistory::RecordPlayerAction(int betround, int chair, ePlayerAction action, double amount, double balance)
{
	double facing_bet =  _amount_to_call[betround] - _player_actions[chair]._prev_bet[betround];
	_current_actor = chair;
	_player_actions[chair].AddAction(betround, action, amount, balance, _n_calls_round, _n_raises_round, _n_checks_round, facing_bet, _pot_round);
	_player_actions[chair]._actions[betround][chair]._left_to_act = LeftToAct(chair);
	_player_actions[chair]._preflop_position = g_symbols->get_ac_dealpos(chair);

	if (action == actionBetRaise)
	{
		// should log error
		if (amount > _amount_to_call[betround])
			_amount_to_call[betround] = amount;
		_player_actions[chair]._prev_bet[betround] = amount;
		_n_raises_round++;
	}
	else if (action == actionCall)
	{
		if(amount > _amount_to_call[betround])
			_amount_to_call[betround] = amount;
		_player_actions[chair]._prev_bet[betround] = amount;
		_n_calls_round++;
	}
	else if (action == actionCheck)
	{
		_n_checks_round++;
	}
	else if (action == actionPostedSB)
	{
		if (amount > _amount_to_call[betround])
			_amount_to_call[betround] = amount;
		_player_actions[chair]._prev_bet[betround] = amount;
	}
	else if (action == actionPostedBB)
	{
		if (amount > _amount_to_call[betround])
			_amount_to_call[betround] = amount;
		_player_actions[chair]._prev_bet[betround] = amount;
	}
	else if (action == actionFold)

	{
		_player_actions[chair]._b_was_in_game = false;
		_fold_bits[betround][_n_times_acted] |= k_exponents[chair];
	}

	if (chair == g_symbols->get_userchair())
	{
		_recorded_bot_action = true;
		_n_times_acted++;
		_times_acted[betround] = _n_times_acted;

		for (int chair_ndx = 0; chair_ndx < g_symbols->get_nchairs(); chair_ndx++)
		{
			_player_actions[chair_ndx]._actions[betround][_n_times_acted]._balance = g_symbols->get_balance(chair_ndx);
		}
	}
	/*
	g_log->WriteLog(eSeverityInfo, eCatHandHistory, "[%-15s] Chair%d: %-7s:%-7.2f \n", 
		GetPlayerName(chair), 
		chair, 
		str_player_action[action], 
		amount
	);*/
}

bool CHandHistory::WasPreflopBlindStealAttempt()
{
	for (int i = 0; i < g_symbols->get_nchairs(); i++)
	{
		if (_player_actions[i]._preflop_position == eBT)
			return (_player_actions[i].GetPreflopAction(false) == eRaiseStealPos);
	}

	return false;
}
