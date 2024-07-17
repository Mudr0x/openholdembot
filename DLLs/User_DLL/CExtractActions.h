#pragma once

#include "CHandHistory.h"
//#include "COpponentModeling.h"

#include <map>

class CExtractActions
{
public:
	// State Variables
	bool			_acted[10];
	bool			_b_new_game;
	bool			_b_new_round;
	bool			_b_skip_missed_action;
	bool			_is_heads_up;
	bool			_hero_in_blinds;
	int				_prev_betround;
	size_t			_start_index;
	size_t			_stop_index;
	CHandHistory	_current_hand_info;
	//COpponentModeling _opp_model;

public:

	//std::map<int, int> CExtractActions::SortPlayers();

	void ExtractActionsReset();
	void ExtractPreviousRoundActions();
	void ExtractPreviousTimesActedActions();
	void ExtractCurrentActions();
	bool ExtractMissedActions();
	void SetStartIndex(size_t start_index) { _start_index = start_index;  }
	void SetStopIndex(size_t stop_index) { _stop_index = stop_index; }
	int GetLastRaiser(bool previous = false);
	
	void ExtractActionsNewGame();
	void ExtractActionsNewRound();
	void ExtractRemainingActions();

	void ExtractActions();
};

extern CExtractActions* g_extract_actions;