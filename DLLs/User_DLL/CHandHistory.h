#pragma once


#include "CSymbols.h"
#include "CPlayerState.h"
#include "magicNumbers.h"


class CHandHistory
{
public:
	CHandHistory();

public:
	CPlayerState _player_actions[k_max_chairs];

	double	_amount_to_call[eRounds];
	double	_pot_round;
	int		_n_calls_round;
	int		_n_checks_round;
	int		_n_raises_round;
	bool	_recorded_bot_action;

	int		_sb_chair, _bb_chair;
	int		_prev_dealer_chair;
	int		_current_actor;

	int     _n_times_acted;
	int		_times_acted[eRounds];
	int		_fold_bits[eRounds][k_max_actions_per_round];


public:
	int  LeftToAct(int chair);
	void RecordPlayerAction(int betround, int chair, ePlayerAction action, double amount, double balance);
	void NewHand();
	void NewBettingRound();

	bool WasPreflopBlindStealAttempt();
};