#include "CPlayerState.h"
#include "magicNumbers.h"



CPlayerState::CPlayerState()
{
	Clear();
}

void CPlayerState::Clear()
{

	_b_was_in_game = true;
	_preflop_position = ePosUnknown;

	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < k_max_actions_per_round; j++)
		{
			_actions[i][j]._player_action = NoAction;
			_actions[i][j]._amount		= 0.0;
			_actions[i][j]._balance		= 0.0;
			_actions[i][j]._facing_bet	= 0.0;
			_actions[i][j]._num_calls	= 0;
			_actions[i][j]._num_raises	= 0;
			_actions[i][j]._num_checks	= 0;
			_actions[i][j]._left_to_act	= -1;
		}

		_prev_bet[i]			= 0.0;
		_total_actions[i]		= 0;
		_actions_this_round[i]  = " .";
	}
}

void CPlayerState::AddAction(int betround, ePlayerAction action, double amount, double balance, int ncalls, int nraises, int nchecks, double facing_bet, double pot)
{
	for (int i = 0; i < k_max_actions_per_round; i++)
	{
		if (_actions[betround][i]._player_action == NoAction) 
		{
			_actions[betround][i]._player_action	= action;
			_actions[betround][i]._amount			= amount;
			_actions[betround][i]._balance			= balance;
			_actions[betround][i]._facing_bet		= facing_bet;
			_actions[betround][i]._num_calls		= ncalls;
			_actions[betround][i]._num_raises		= nraises;
			_actions[betround][i]._num_checks		= nchecks;

			_total_actions[betround] = i+1;

			break;
		}
	}
}

ePreflopAction CPlayerState::GetPreflopAction(const bool bWasPreflopBlindStealAttempt)
{
	ePreflopAction ret = ePFActionUnknown;
	int nActions = 0, iFirstAction = 0;

	for (int i=0; i < k_max_actions_per_round; i++)
	{
		if (_actions[ePreflop][i]._player_action == NoAction || 
			_actions[ePreflop][i]._player_action == actionFold)
			break;

		if (_actions[ePreflop][i]._player_action == actionPostedSB || 
			_actions[ePreflop][i]._player_action == actionPostedBB)
			iFirstAction++;
		else
			nActions++;
	}

	if (nActions == 1) 
	{
		if (_actions[ePreflop][iFirstAction]._player_action == actionCall) 
		{
			if (bWasPreflopBlindStealAttempt && _preflop_position == eBB)
				ret = eBBDefenseCall;
			else
				ret = eCallRaise;
		} 

		else if (_actions[ePreflop][iFirstAction]._player_action == actionCheck)
			ret = eLimp;

		else if (_actions[ePreflop][iFirstAction]._player_action == actionBetRaise) 
		{
			if (_actions[ePreflop][iFirstAction]._num_raises == 0) 
			{
				if (_preflop_position == eBB && bWasPreflopBlindStealAttempt)
					ret = eBBDefense3Bet;
				else if (_preflop_position == eBT)
					ret = eRaiseStealPos;
				else
					ret = eRaise;
			}

			else if (_actions[ePreflop][iFirstAction]._num_raises == 1)
				ret = e3Bet;
			else if (_actions[ePreflop][iFirstAction]._num_raises > 1)
				ret = e4Bet;

			else 
			{
				// error
			}
		}
	} 
	else if (nActions > 1) 
	{
		if (_actions[ePreflop][iFirstAction]._player_action == actionCall) 
		{
			if (_actions[ePreflop][iFirstAction+1]._player_action == actionBetRaise)
				ret = eLimpRaise;
			else if (_actions[ePreflop][iFirstAction+1]._player_action == actionCall)
				ret = eLimpCall;

			else 
			{
				// error
			}
		}
	}

	return ret;
}

ePostflopAction CPlayerState::GetPostflopAction(int iRound)
{
	ePostflopAction ret = eActionUnknown;
	int nActions = _total_actions[iRound];

	if (_actions[iRound][nActions]._player_action == NoAction || 
		_actions[iRound][nActions]._player_action == actionFold)
		return ret;

	if (nActions == 1) 
	{
		if (_actions[iRound][0]._player_action == actionCall)
			ret = eActionCall;

		else if (_actions[iRound][0]._player_action == actionCheck)
			ret = eActionCheck;
		else if (_actions[iRound][0]._player_action == actionBetRaise) 
		{
			if (_actions[iRound][0]._num_raises == 0)
				ret = eActionBet;
			else if (_actions[iRound][0]._num_raises == 1)
				ret = eActionRaise;
			else if (_actions[iRound][0]._num_raises > 1)
				ret = eActionRaise;
			else 
			{
				// error
			}
		}
	} 

	// Hmmm...
	// Must finish this
	else if (nActions > 1) 
	{
		if (_actions[iRound][0]._player_action == actionCheck) 
		{
			if (_actions[iRound][1]._player_action == actionBetRaise)
				ret = eActionCheckRaise;
			else if (_actions[iRound][1]._player_action == actionCall)
				ret = eActionCheckCall;

			else 
			{
				// error
			}
		} 

		else if (_actions[iRound][0]._player_action == actionCall) 
		{
			if (_actions[iRound][1]._player_action == actionBetRaise)
				ret = eActionCallRaise;
			else if (_actions[iRound][1]._player_action == actionCall)
				ret = eActionCallCall;

			else 
			{
				// error
			}
		} 

		else if (_actions[iRound][0]._player_action == actionBetRaise) 
		{
			if (_actions[iRound][1]._player_action == actionBetRaise)
				ret = eActionBetBet;
			else if (_actions[iRound][1]._player_action == actionCall)
				ret = eActionBetCall;

			else 
			{
				// error
			}
		}
	}

	return ret;
}