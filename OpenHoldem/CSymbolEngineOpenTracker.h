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

#ifndef INC_CSYMBOLENGINEOPENTRACKER_H
#define INC_CSYMBOLENGINEOPENTRACKER_H

#include "CVirtualSymbolEngine.h"

class CSymbolEngineOpenTracker: public CVirtualSymbolEngine {
 public:
	CSymbolEngineOpenTracker();
	~CSymbolEngineOpenTracker();
 public:
	// Mandatory reset-functions
	void InitOnStartup();
	void UpdateOnConnection();
	void UpdateOnHandreset();
	void UpdateOnNewRound();
	void UpdateOnMyTurn();
	void UpdateOnHeartbeat();
 public:
	// Public accessors	
	bool EvaluateSymbol(const CString name, double *result, bool log = false);
	CString SymbolsProvided();
 public:
  int PlayerIcon(const int chair);
 private:
	void	CheckForChangedPlayersOncePerHeartbeatAndSymbolLookup();
	void	WarnAboutInvalidOTSymbol(CString s);
	bool	IsOldStyleOTSymbol(CString s);
	void	ClearSeatStats(int chair, bool clearNameAndFound);
	void	ClearAllStatsOfChangedPlayers();
	void	ClearAllStats();
 private:
	bool	check_for_identity_of_players_executed_this_heartbeat;
};

#endif INC_CSYMBOLENGINEOPENTRACKER_H