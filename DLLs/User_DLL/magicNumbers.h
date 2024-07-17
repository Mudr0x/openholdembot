#pragma once

const double epsilon = 1E-06;

//All-In
const int c_allin = -1;
//Raise
const int c_raise = -2;
//Call
const int c_call = -3;
//Check
const int c_check = -4;
//Fold
const int c_fold = -5;
//Error
const int c_error = -6;

const double call_value = 0.001;

/////////////////////////////
// Position values
/////////////////////////////
const int c_SB = 1;		// Small Blind
const int c_BB = 2;		// Big Blind
const int c_UTG = 3;	// Under The Gun
const int c_HJ = 4;		// Hijack
const int c_CO = 5;		// CutOff
const int c_BT = 6;		// Button

const int k_undefined = -1;
const int k_max_chairs = 10;
const int k_max_actions_per_round = 4;
const int k_num_suits = 4;
const int k_num_ranks = 13;
const int k_prw1326_suit[4] = { 0, 13, 26, 39 };

const int k_exponents[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

static const char* ctonum = "23456789TJQKA";
static const char* str_suits = "hdcs";
static const char* str_action[] = { " *", " F", " s", " b", " C", " X", " R" };
static const char* str_rounds[] = { "Unknown\n", "Preflop\n", "Flop\n", "Turn\n", "River\n" };
static const char* str_player_action[] = { "Unknown Action", "Folds", "SB", "BB", "Checks", "Calls", "Bets" };

////////////
// Enums
////////////
enum ePreflopPosition { ePosUnknown = -1, eSB = 1, eBB = 2, eUTG = 3, eHJ = 4, eCO = 5, eBT = 6, eTooBig1 = 7, eTooBig2 = 8, eTooBig3 = 9, eTooBig4 = 10 };
enum enumStreets { eUnknown = 0, ePreflop = 1, eFlop = 2, eTurn = 3, eRiver = 4, eRounds = 5 };

enum ePlayerAction { NoAction, actionFold, actionPostedSB, actionPostedBB, actionCheck, actionCall, actionBetRaise };
enum ePreflopAction { ePFActionUnknown, eLimp, eLimpCall, eCallRaise, eLimpRaise, eRaise, eRaiseStealPos, e3Bet, e3BetSteal, e4Bet, eBBDefenseCall, eBBDefense3Bet };
enum ePostflopAction { eActionUnknown, eActionCheck, eActionBet, eActionRaise, eActionCall, eActionCheckRaise, eActionCheckCall, eActionCallRaise, eActionCallCall, eActionBetCall, eActionBetBet };

