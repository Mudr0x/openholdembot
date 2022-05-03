#pragma once
//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose:
//
//******************************************************************************


#include <string>
#include <sstream>
#include <iostream>
#include "any.h"
#include <map>
#include <vector>
#include <list>
#include <array>
#include <tuple>
#include <deque>
using namespace std;



class CHand : CObject
{
public:

	//////////////////////////////////////////////////////////////////
	//   Class Variables
	map<char, char> UPS = { {'a','A'}, {'t','T'}, {'j','J'}, {'q','Q'}, {'k','K'}, {'S','s'}, {'C','c'}, {'H','h'}, {'D','d'} };
	map<char, char> LCS = { {'H','h'}, {'D','d'}, {'C','c'}, {'S','s'} };
	map<string, string> SYMBOL = { {"USD","$"}, {"CAD","C$"}, {"EUR","€"}, {"GBP","£"}, {"SEK","kr."}, {"RS","РСД"}, {"mBTC","mɃ"}, {"T$",""}, {"play",""} };
	map<string, string> MS = { {"horse","HORSE"}, {"8game","8-Game"}, {"hose","HOSE"}, {"ha","HA"} };
	map<string, int> ACTION = { {"ante",1 }, {"small blind",2 }, {"secondsb",3 }, {"big blind",4 }, {"both",5 }, {"calls",6 }, {"raises",7 },
	{"bets",8 }, {"stands pat",9 }, {"folds",10 }, {"checks",11 }, {"discards",12 }, {"bringin",13 }, {"completes",14 } };

	CHand(string config, string sitename, string gametype, string handText, string builtFrom = "HHC");
	~CHand();
	operator string() const { //implement code that will produce an instance of string and return it here

		map<string, any> vars = {
			{ "BB", bb },
			{ "SB", sb },
			{ "BUTTON POS", buttonpos },
			{ "HAND NO.", handid },
			{ "SITE", _sitename },
			{ "TABLE NAME", tablename },
			{ "HERO", hero },
			{ "MAX SEATS", maxseats },
			{ "LEVEL", level },
			{ "MIXED", mixed },
			{ "LAST BET", lastBet },
			{ "ACTION STREETS", actionStreets },
			{ "STREETS", streets },
			{ "ALL STREETS", allStreets },
			{ "COMMUNITY STREETS", communityStreets },
			{ "HOLE STREETS", holeStreets },
			{ "COUNTED SEATS", counted_seats },
			{ "DEALT", dealt },
			{ "SHOWN", shown },
			{ "MUCKED", mucked },
			{ "TOTAL POT", totalpot },
			{ "TOTAL COLLECTED", totalcollected },
			{ "RAKE", rake },
			{ "START TIME", startTime },
			{ "TOURNAMENT NO", tourNo },
			{ "TOURNEY ID", tourneyId },
			{ "TOURNEY TYPE ID", tourneyTypeId },
			{ "BUYIN", buyin },
			{ "BUYIN CURRENCY", buyinCurrency },
			{ "BUYIN CHIPS", buyInChips },
			{ "FEE", fee },
			{ "IS REBUY", isRebuy },
			{ "IS ADDON", isAddOn },
			{ "IS KO", isKO },
			{ "KO BOUNTY", koBounty },
			{ "IS MATRIX", isMatrix },
			{ "IS SHOOTOUT", isShootout }
		};

		map<string, any> structs = {
			{ "PLAYERS", players },
			{ "STACKS", stacks },
			{ "POSTED", posted },
			{ "POT", pot },
			{ "SEATING", seating },
			{ "GAMETYPE", gametype },
			{ "ACTION", actions },
			{ "COLLECTEES", collectees },
			{ "BETS", bets },
			{ "BOARD", board },
			{ "DISCARDS", discards },
			{ "HOLECARDS", holecards },
			{ "TOURNEYS PLAYER IDS", tourneysPlayersIds }
		};

		stringstream ostr;
		for (auto const& var : vars) {
			ostr << "\n" << var.first << " = " << any_cast<string>(&var.second);
		}
		for (auto const& strct : structs) {
			ostr << "\n" << strct.first << " =\n" << any_cast<string>(&strct.second);
		}
		return ostr.str();
	};

private:
	void addHoleCards(string street, string player, string open = {}, string closed = {}, bool shown = false, bool mucked = false, bool dealt = false);

	string _config, _sitename, _gametype, _handText;
	string saveActions, callHud, cacheSessions, publicDB, siteId, in_path, tablename, hero;
	int startTime, handid, dbid_hands, dbid_pids, dbid_hpid, dbid_gt, maxseats, counted_seats, bb, sb, buttonpos, runItTimes;
	bool cancelled, uncalledbets, checkForUncalled, adjustCollected;
	list<int> stats;
	any gametype;

	//tourney stuff
	int tourNo, tourneyId, tourneyTypeId, buyin, buyInChips, fee, level, rebuyCost, addOnCost, koBounty, stepNo, chanceCount, timeAmt, guaranteeAmt;
	string buyinCurrency, speed, stack, addedCurrency, entryId;
	bool mixed, isSng, isRebuy, isAddOn, isKO, isMatrix, isShootout, isFast, isStep, isChance, isMultiEntry, isReEntry, isHomeGame,
		isNewToGame, isFifty50, isTime, isSatellite, isDoubleOrNothing, isCashOut, isOnDemand, isFlighted, isGuarantee, added;

	list<int> seating;
	list<string> players;
	// Cache used for checkPlayerExists.
	bool player_exists_cache;
	list<int> posted;
	map<int, string> tourneysPlayersIds;

	// Collections indexed by street names
	map<int, string> bets;
	map<int, string> lastBet;
	vector<string> streets;
	vector<map<string, string, string>> actions; // [['mct', 'bets', '$10'], ['mika', 'folds'], ['carlg', 'raises', '$20']]
	vector<int> actionStreets;
	map<string, string, string> allStreets;
	map<string, string, string> communityStreets;
	vector<int> holeStreets;
	vector<int> discardStreets;
	vector<map<int, string>> board; // dict from street names to community cards
	map<int, string> holecards;
	map<int, string> discards;
	vector<int> showdownStrings;
	// Collections indexed by player names
	map<int, string> rakes;
	map<int, string> stacks;
	list<string> collected;
	map<int, string> collectees;

	// Sets of players
	string folded;
	string dealt;  // 'dealt to' line to be printed
	string shown;  // cards were shown
	string mucked; // cards were mucked at showdown
	string sitout; // players sitting out or not dealt in(usually tournament)

	// Things to do with money
	int pot, totalpot, totalcollected, rake, roundPenny;
	bool fastFold;
	// currency symbol for this hand
	string sym;
	bool is_duplicate;
};

