//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: Very simple user-DLL as a starting-point
//
// Required OpenHoldem version: 12.1.6
//
//******************************************************************************

// Needs to be defined here, before #include "user.h"
// to generate proper export- and inport-definitions
#define USER_DLL

#include "user.h"
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <iostream>

#include "OpenHoldemFunctions.h"

#include "CLogging.h"
#include "CSymbols.h"
#include "CExtractActions.h"
#include "magicNumbers.h"


//******************************************************************************
//
// Place all your initalizations in the functions below
// DLLOnLoad() amd DLLOnUnLoad() get called by the DLL,
// the other functions get called by OpenHoldem
//
//******************************************************************************

static int NUM_PLAYERS = 6;

CLogging* g_log = nullptr;
CSymbols* g_symbols = nullptr;
CExtractActions* g_extract_actions;
CWrapper* g_wrapper = nullptr;

int index_offset = 0;
int _heroInd;
int _buttonInd;
int _bigBlindSize;
int _startStackSize;
int* _amountInPot = new int();
//int _totalInvestedMoney[NUM_PLAYERS];
//int _rebuysCount[NUM_PLAYERS];
int _handsPlayed;
bool is_busy = false;
bool is_bad_scrape = false;
bool is_a_call = false;
bool is_resetted = false;
bool is_reset_inplay = false;
bool is_acted = false;


int RankCharacterToRankNumber(char rank) {
	switch (rank) {
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 't':
	case 'T': return 10;
	case 'j':
	case 'J': return 11;
	case 'q':
	case 'Q': return 12;
	case 'k':
	case 'K': return 13;
	case 'a':
	case 'A': // Ace high
		return 14;
	default:
		// Just accept silently
		// We might get input like "Ac3d" or "KJTsuited"
		//assert(false);
		return 0;
	}
}

int SuitCharacterToSuitNumber(char suit) {
	switch (suit) {
	case 'h':
	case 'H': return 0;
	case 'd':
	case 'D': return 1;
	case 'c':
	case 'C': return 2;
	case 's':
	case 'S': return 3;
	default: // Fail silently
		//assert(false);
		return -1;
	}
}

void setPlayerAction(int chair, int actionType, int amountInPot)
{
	if (_handsPlayed > 0) {
		if (actionType == 2 && amountInPot == 0)
			actionType = 1;
		if ((actionType == 0 || actionType == 1) && amountInPot > 0)
			amountInPot = 0;
		try {
			vector<std::pair<int, int>> holeCards;
			if (chair == g_symbols->get_userchair()) {
				std::pair<int, int> card0 = { g_symbols->get_$$pr0(), g_symbols->get_$$ps0() };
				std::pair<int, int> card1 = { g_symbols->get_$$pr1(), g_symbols->get_$$ps1() };
				holeCards.push_back(card0); holeCards.push_back(card1);
			}
			else {
				string scraped_result;
				int result_lenght;
				string rank0 = "p" + to_string(chair) + "cardface0rank";
				string suit0 = "p" + to_string(chair) + "cardface0suit";
				string rank1 = "p" + to_string(chair) + "cardface1rank";
				string suit1 = "p" + to_string(chair) + "cardface1suit";
				std::cout << rank0.data() << std::endl;
				rank0 = (ScrapeTableMapRegion(&rank0[0], result_lenght) == nullptr ? "0" : ScrapeTableMapRegion(&rank0[0], result_lenght));
				suit0 = (ScrapeTableMapRegion(&suit0[0], result_lenght) == nullptr ? "-1" : ScrapeTableMapRegion(&suit0[0], result_lenght));
				rank1 = (ScrapeTableMapRegion(&rank1[0], result_lenght) == nullptr ? "0" : ScrapeTableMapRegion(&rank1[0], result_lenght));
				suit1 = (ScrapeTableMapRegion(&suit1[0], result_lenght) == nullptr ? "-1" : ScrapeTableMapRegion(&suit1[0], result_lenght));

				int irank0 = RankCharacterToRankNumber(rank0[0]);
				int isuit0 = SuitCharacterToSuitNumber(suit0[0]);
				int irank1 = RankCharacterToRankNumber(rank1[0]);
				int isuit1 = SuitCharacterToSuitNumber(suit1[0]);
				
				std::pair<int, int> card0 = { irank0, isuit0 };
				std::pair<int, int> card1 = { irank1, isuit1 };
				holeCards.push_back(card0); holeCards.push_back(card1);
			}

			g_wrapper->GetWrapper().setPlayerAction(chair - index_offset, actionType, amountInPot, holeCards);
		}
		catch (...) {
			// Handle exception errors here
			return;
		}
	}
}


void DLLOnLoad()
{
	_handsPlayed = 0;
}

void DLLOnUnLoad()
{
	if (g_extract_actions)
		delete g_extract_actions;

	if (g_symbols)
		delete g_symbols;

	if (g_log)
		delete g_log;

	if (g_wrapper)
		delete g_wrapper;

	if (_amountInPot)
		delete _amountInPot;
}

void __stdcall DLLUpdateOnNewFormula()
{
	if (g_extract_actions)
		delete g_extract_actions;

	if (g_symbols)
		delete g_symbols;

	if (g_log)
		delete g_log;

	if (g_wrapper)
		delete g_wrapper;

	g_log = new CLogging();
	g_log->WriteLogNoHeading(eSeverityInfo, eCatGeneral, ">>> Loading Formula.\n");
	g_symbols = new CSymbols();
	g_extract_actions = new CExtractActions();
	g_wrapper = new CWrapper();
}

void __stdcall DLLUpdateOnConnection()
{
}

void __stdcall DLLUpdateOnHandreset()
{
	g_symbols->UpdateOHSymbols();
	int betround = g_symbols->get_betround();
	if (betround != 1) {
		is_reset_inplay = true;
		return;
	}
	is_reset_inplay = false;
	if (!is_resetted) {
		//g_extract_actions->ExtractActions();

		//for (int i = 0; i < NUM_PLAYERS; i++)
		//  _rebuysCount[i] = 0;
		is_acted = false;
		g_extract_actions->ExtractActionsReset();
		//g_extract_actions->SetStopIndex((g_symbols->get_bigblindchair() + 1) % g_symbols->get_nchairs());
		g_extract_actions->SetStopIndex(-1);

	}
}

void __stdcall DLLUpdateOnNewRound()
{
	is_acted = false;
	//Street street = _botGameStates[_heroInd]->getStreet();
	g_symbols->UpdateOHSymbols();
	//g_extract_actions->ExtractActionsNewRound();
	int street = g_symbols->get_betround();
	if (_handsPlayed == 0) {
		is_reset_inplay = true;
		return;
	}
	is_reset_inplay = false;
	if (street > 1) {
		vector<std::pair<int, int>> boardCards;

		std::pair<int, int> card0 = { g_symbols->get_$$cr0(), g_symbols->get_$$cs0() };
		std::pair<int, int> card1 = { g_symbols->get_$$cr1(), g_symbols->get_$$cs1() };
		std::pair<int, int> card2 = { g_symbols->get_$$cr2(), g_symbols->get_$$cs2() };
		std::pair<int, int> card3 = { g_symbols->get_$$cr3(), g_symbols->get_$$cs3() };
		std::pair<int, int> card4 = { g_symbols->get_$$cr4(), g_symbols->get_$$cs4() };
		boardCards.push_back(card0); boardCards.push_back(card1); boardCards.push_back(card2);
		if (street > 2) {
			boardCards.push_back(card3);
			if (street > 3)
				boardCards.push_back(card4);
		}
		try {
			g_wrapper->GetWrapper().nextStreet(street - 1, boardCards);
			//g_extract_actions->ExtractActions();
		}
		catch (...) {
			// Handle exception errors here
			return;
		}
	}

	int userchair = g_symbols->get_userchair();
	if (!g_extract_actions->_current_hand_info._player_actions[userchair]._b_was_in_game || !GetPlayerHasAnyCards(userchair)) {  // !g_extract_actions->_current_hand_info._player_actions[userchair]._b_was_in_game
		//_sleep(500);
		is_acted = true;
		g_extract_actions->SetStartIndex((g_symbols->get_dealerchair() + 1) % g_symbols->get_nchairs());
		//g_extract_actions->SetStopIndex((g_symbols->get_dealerchair() + 1) % g_symbols->get_nchairs());
		g_extract_actions->SetStopIndex(-1);
		//DLLUpdateOnHeartbeat();
	}
}

void __stdcall DLLUpdateOnMyTurn()
{
	if (!is_resetted) {
		//size_t start_index = (_current_hand_info._current_actor + 1) % g_symbols->get_nchairs();
		//g_extract_actions->SetStartIndex(start_index);
		//g_extract_actions->SetStopIndex(g_symbols->get_bigblindchair() + 1);
		g_symbols->UpdateOHSymbols();
		//g_extract_actions->ExtractActionsReset();
		//g_extract_actions->ExtractActions();

		//for (int i = 0; i < NUM_PLAYERS; i++)
		//  _rebuysCount[i] = 0;

		int betround = g_symbols->get_betround();
		if (betround != 1 || GetSymbol("didfoldround1") || GetSymbol("didchecround1") || GetSymbol("didcallround1") ||
			GetSymbol("didraisround1") || GetSymbol("didbetsizeround1") || GetSymbol("didalliround1")) {
			//is_reset_inplay = true;
			return;
		}
		//is_reset_inplay = false;

		int nchairs = g_symbols->get_nchairs();
		int nseated = g_symbols->get_nplayersseated();
		g_symbols->get_nplayersseated() == 2 ? NUM_PLAYERS = 2 : NUM_PLAYERS = 6;
		index_offset = nchairs - NUM_PLAYERS;
		double bblind = g_symbols->get_bblind();
		_bigBlindSize = int(g_symbols->get_bblind() * 100);

		_heroInd = g_symbols->get_userchair() - index_offset;
		_buttonInd = g_symbols->get_dealerchair() - index_offset;

		vector<string> playerNames;
		vector<int> stackSizes;
		vector<int> sittingOutPlayers;
		vector<std::pair<int, int>> holeCards;

		for (int i = 0 + index_offset; i < NUM_PLAYERS + index_offset; i++)
		{
			string name = GetPlayerName(i);
			if (i == _heroInd) {
				name == "" ? playerNames.push_back("Hero") : playerNames.push_back(name);
			}
			else {
				name == "" ? playerNames.push_back("Player" + to_string(i)) : playerNames.push_back(name);
			}
			if (((g_symbols->get_playersseatedbits() >> i) & 1) == 0) {
				sittingOutPlayers.push_back(i - index_offset);
				_startStackSize = 0;
			}
			else {
				_startStackSize = (int)(GetPlayerStack(i) * 100);
			}
			stackSizes.push_back(_startStackSize);
			//_totalInvestedMoney[i] = _startStackSize;
		}

		std::pair<int, int> card0 = { g_symbols->get_$$pr0(), g_symbols->get_$$ps0() };
		std::pair<int, int> card1 = { g_symbols->get_$$pr1(), g_symbols->get_$$ps1() };
		holeCards.push_back(card0); holeCards.push_back(card1);
		if (card0.second < 0 || card0.second > 3 || _bigBlindSize <= 0 || _heroInd < 0 || _buttonInd < 0) {
			is_bad_scrape = true;
			return;
		}
		else is_bad_scrape = false;

		if (_handsPlayed == 0) {
			try {
				g_wrapper->GetWrapper().startGame(NUM_PLAYERS, _bigBlindSize, _heroInd, _buttonInd, playerNames, stackSizes, sittingOutPlayers, holeCards);
			}
			catch (...) {
				// Handle exception errors here
				return;
			}
		}
		else if (_handsPlayed > 0) {
			try {
				g_wrapper->GetWrapper().startNewHand(_heroInd, _buttonInd, playerNames, stackSizes, sittingOutPlayers, holeCards);
			}
			catch (...) {
				// Handle exception errors here
				return;
			}
		}

		is_resetted = true;
		_handsPlayed++;
		//return;
	}
	is_acted = false;
}

void __stdcall DLLUpdateOnHeartbeat()
{
	//g_log->WriteLogNoHeading(eSeverityInfo, eCatGeneral, ">>> Heartbeat.\n");
	if (is_acted) {
		if (g_extract_actions->ExtractMissedActions()) {
			is_acted = false;
		}
	}
}

//******************************************************************************
//
// ProcessQuery()
// Handling the lookup of dll$symbols
//
//******************************************************************************

DLL_IMPLEMENTS double __stdcall ProcessQuery(const char* pquery)
{
	if (pquery == nullptr)
	{
		return 0;
	}
	if (strncmp(pquery, "dll$test", 8) == 0)
	{
		MessageBox(0, GetTableTitle(), TEXT("Table title"), 0);
		MessageBox(0, GetPlayerName(0), TEXT("Name of player 0"), 0);
		return GetSymbol("random");
	}

	if (strncmp(pquery, "dll$scrape", 10) == 0)
	{
		char* scraped_result;
		int result_lenght;
		scraped_result = ScrapeTableMapRegion("p0balance", result_lenght);
		if (scraped_result != nullptr)
		{
			// The TEXT() macro supports both ASCII and Unicode.
			// For the people who use Unicode but don't understand the "error".
			// http://www.maxinmontreal.com/forums/viewtopic.php?f=174&t=19999
			// http://stackoverflow.com/questions/15498070/what-does-t-stands-for-in-a-cstring
			MessageBox(0, scraped_result, TEXT("Scraped custom region"), 0);
			LocalFree(scraped_result);
		}
	}

	if (strncmp(pquery, "dll$iswait", 10) == 0)
	{
		return is_busy;
	}

	if (strncmp(pquery, "dll$betsize", 11) == 0) {
		if (is_reset_inplay || is_bad_scrape || is_a_call)
			return 0;
		return ((double)*_amountInPot / 100);
	}

	if (strncmp(pquery, "dll$decision", 12) == 0) {
		if (is_reset_inplay || is_bad_scrape)
			return 0;
		bool isfinalanswer = GetSymbol("isfinalanswer");
		if (isfinalanswer && !is_acted) {
			is_busy = true;
			g_symbols->UpdateOHSymbols();
			g_extract_actions->ExtractActions();

			int amountToCall = (int)(GetSymbol("call") * 100);
			//GetSymbol("cmd$recalc");
			string result;
			try {
				result = g_wrapper->GetWrapper().GetDecision(_heroInd, amountToCall, _amountInPot).c_str();
			}
			catch (...) {
				// Handle exception errors here
				return 0;
			}
			int actionType = (result == "Fold" ? 0 : result == "Check" ? 1 : result == "Call" ? 2 : result == "Bet" ? 3 : result == "Raise" ? 4 : result == "RaiseMax" ? 5 : 0);
			if (result == "Check" || result == "Call")
				*_amountInPot = amountToCall;
			if (result == "Check" && *_amountInPot > 0) {
				result = "Fold";
				*_amountInPot = 0;
			}

			int chair_ndx = _heroInd + index_offset; // g_symbols->get_userchair();
			int betround = g_symbols->get_betround();
			int times_acted = g_extract_actions->_current_hand_info._times_acted[betround];
			double balance = g_symbols->get_balance(chair_ndx);
			double current_bet = (double)*_amountInPot / 100;
			double current_bet_final = current_bet - g_extract_actions->_current_hand_info._player_actions[chair_ndx]._actions[betround][times_acted - 1]._amount;

			if (*_amountInPot < amountToCall)
			{
				g_extract_actions->_current_hand_info.RecordPlayerAction(betround,
					chair_ndx,
					actionFold,
					0,
					balance);
			}

			else if (*_amountInPot == 0 && GetPlayerHasAnyCards(chair_ndx)) {
				g_extract_actions->_current_hand_info.RecordPlayerAction(betround,
					chair_ndx,
					actionCheck,
					0,
					balance);
			}
			else if (*_amountInPot == amountToCall) {
				g_extract_actions->_current_hand_info.RecordPlayerAction(betround,
					chair_ndx,
					actionCall,
					current_bet_final,
					balance);
			}
			else if (*_amountInPot > amountToCall) {
				g_extract_actions->_current_hand_info.RecordPlayerAction(betround,
					chair_ndx,
					actionBetRaise,
					current_bet_final,
					balance);
				g_extract_actions->SetStopIndex(chair_ndx);
			}

			setPlayerAction(_heroInd + index_offset, actionType, *_amountInPot);

			if (result == "Check") result = "Call";
			if (result == "Bet") result = "Raise";
			if (result == "Call") is_a_call = true;
			else is_a_call = false;

			double decision = GetSymbol(result.c_str());
			//double decision = g_decision->Decision();
			is_resetted = false;
			is_busy = false;

			g_extract_actions->SetStartIndex((chair_ndx + 1) % g_symbols->get_nchairs());
			//_sleep(500);
			is_acted = true;

			//system("pause");

			return decision;
		}
	}
	return 0;
}

//******************************************************************************
//
// DLL entry point
//
//******************************************************************************

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
#ifdef _DEBUG
		//AllocConsole();
#endif _DEBUG
		InitializeOpenHoldemFunctionInterface();
		DLLOnLoad();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		DLLOnUnLoad();
#ifdef _DEBUG
		//FreeConsole();
#endif _DEBUG
		break;
	}

	return TRUE;
}