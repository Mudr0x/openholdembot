#pragma once

#include <string>

#include "magicNumbers.h"

class CPlayerActionInfo
{
public:
	ePlayerAction _player_action;
	double	_amount;
	double	_balance;
	int		_num_calls, _num_raises, _num_checks;
	double	_facing_bet;
	int		_left_to_act;
	int		_facing_context;

public:

};


class CPlayerState
{
public:
	CPlayerState();

public:
	CPlayerActionInfo	_actions[eRounds][k_max_actions_per_round];
	int					_preflop_position;
	int					_total_actions[eRounds];
	bool				_b_was_in_game;
	double				_prev_bet[eRounds];

	// Dummy var for testing. Delete_Me :P
	std::string			_actions_this_round[eRounds];

public:
	void AddAction(int betround, ePlayerAction action, double amount, double balance, int ncalls, int nraises, int nchecks, double facing_bet, double pot);
	void Clear();
	ePreflopAction GetPreflopAction(const bool b_steal_attempt);
	ePostflopAction GetPostflopAction(int iRound);
};