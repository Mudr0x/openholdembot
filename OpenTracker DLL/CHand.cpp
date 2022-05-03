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


#include "stdafx.h"
#include "CHand.h"



CHand::CHand(string config, string sitename, string gametype, string handText, string builtFrom)
{
	//log.debug(_("Hand.init(): handText is ") + str(handText))
	_config = config;
	_sitename = sitename;
	_gametype = gametype;
	_handText = handText;
	//saveActions = config.get_import_parameters().get('saveActions');
	//callHud = config.get_import_parameters().get("callFpdbHud");
	//cacheSessions = config.get_import_parameters().get("cacheSessions");
	//publicDB = config.get_import_parameters().get("publicDB");
	//siteId = config.get_site_id(sitename);
	//stats = DerivedStats.DerivedStats();
	startTime = 0;
	handid = 0;
	in_path = "";
	cancelled = false;
	dbid_hands = 0;
	dbid_pids = NULL;
	dbid_hpid = NULL;
	dbid_gt = 0;
	tablename = "";
	hero = "";
	maxseats = NULL;
	counted_seats = 0;
	buttonpos = 0;
	runItTimes = 0;
	uncalledbets = false;
	checkForUncalled = false;
	adjustCollected = false;

	//tourney stuff
	tourNo = NULL;
	tourneyId = NULL;
	tourneyTypeId = NULL;
	buyin = NULL;
	buyinCurrency = "";
	buyInChips = NULL;
	fee = NULL;  // the Database code is looking for this one .. ?
	level = NULL;
	mixed = NULL;
	speed = "Normal";
	isSng = false;
	isRebuy = false;
	rebuyCost = 0;
	isAddOn = false;
	addOnCost = 0;
	isKO = false;
	koBounty = 0;
	isMatrix = false;
	isShootout = false;
	isFast = false;
	stack = "Regular";
	isStep = false;
	stepNo = 0;
	isChance = false;
	chanceCount = 0;
	isMultiEntry = false;
	isReEntry = false;
	isHomeGame = false;
	isNewToGame = false;
	isFifty50 = false;
	isTime = false;
	timeAmt = 0;
	isSatellite = false;
	isDoubleOrNothing = false;
	isCashOut = false;
	isOnDemand = false;
	isFlighted = false;
	isGuarantee = false;
	guaranteeAmt = 0;
	added = NULL;
	addedCurrency = "";
	entryId = 1;
	seating = {};
	players = {};
	// Cache used for checkPlayerExists.
	//player_exists_cache = set();
	posted = {};
	tourneysPlayersIds = {};

	// Collections indexed by street names
	bets = {};
	lastBet = {};
	streets = {};
	actions = {}; // [['mct', 'bets', '$10'], ['mika', 'folds'], ['carlg', 'raises', '$20']]
	board = {}; // dict from street names to community cards
	holecards = {};
	discards = {};
	showdownStrings = {};
	for (auto const& street : showdownStrings) {
		streets[street] = ""; // portions of the handText, filled by markStreets()
		actions[street] = { "", "", "" };
	}
	for (auto const& street : actionStreets) {
		bets[street] = "";
		lastBet[street] = "";
		board[street] = { "", "" };
	}
	for (auto const& street : holeStreets) {
		holecards[street] = ""; // dict from player names to holecards
	}
	for (auto const& street : discardStreets) {
		discards[street] = ""; // dict from player names to dicts by street ... of tuples ... of discarded holecards
	}
	// Collections indexed by player names
	rakes = {};
	stacks = {};
	collected = {}; //list of ?
	collectees = {}; // dict from player names to amounts collected(? )

	// Sets of players
	//folded = set();
	//dealt = set();  // 'dealt to' line to be printed
	//shown = set();;  // cards were shown
	//mucked = set(); // cards were mucked at showdown
	//sitout = set() // players sitting out or not dealt in(usually tournament)

	// Things to do with money
	//pot = Pot();
	totalpot = NULL;
	totalcollected = NULL;
	rake = NULL;
	roundPenny = NULL;
	fastFold = false;
	// currency symbol for this hand
	//sym = SYMBOL[self.gametype['currency']]; // save typing!delete this attr when done
	//pot.setSym(self.sym);
	is_duplicate = false;  // i.e.don't update hudcache if true
}

CHand::~CHand()
{
}

void CHand::addHoleCards(string street, string player, string open, string closed, bool shown, bool mucked, bool dealt) {
	/* Assigns observed holecards to a player.
		cards   list of card bigrams e.g.['2h', 'Jc']
		player(string) name of player
		shown   whether they were revealed at showdown
		mucked  whether they were mucked at showdown
		dealt   whether they were seen in a 'dealt to' line */
	string sum = open + closed;
	write_log("Hand.addHoleCards open+closed: %s, player: %s, shown: %s, mucked: %s, dealt: %s",
		sum.c_str(), player, shown, mucked, dealt);
	//checkPlayerExists(player, 'addHoleCards');
	if (dealt)  this->dealt.append(player);
	if (shown)  this->shown.append(player);
	if (mucked)  this->dealt.append(player);
}