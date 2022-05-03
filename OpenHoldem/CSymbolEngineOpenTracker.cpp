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
#include "CSymbolEngineOpenTracker.h"
#include "CSymbolEngineActiveDealtPlaying.h"

#include "CEngineContainer.h"
#include "CFormulaParser.h"
#include "CParseErrors.h"
#include "CParseTreeTerminalNodeEndOfFunction.h"
#include "..\OpenTracker DLL\opentracker_query_definitions.h"
#include "COpenTrackerThread.h"

#include "CSymbolEngineCallers.h"
#include "CSymbolEngineChairs.h"
#include "CSymbolengineDealerchair.h"
#include "CSymbolEngineIsRush.h"
#include "CSymbolEngineRaisers.h"
#include "CSymbolEngineUserchair.h"
#include "..\DLLs\WindowFunctions_DLL\window_functions.h"
#include "..\DLLs\StringFunctions_DLL\string_functions.h"
#include "..\OpenTracker DLL\CImporter.h"

CImporter OT_IMPORTER;


CSymbolEngineOpenTracker::CSymbolEngineOpenTracker()
{
	// The values of some symbol-engines depend on other engines.
	// As the engines get later called in the order of initialization
	// we assure correct ordering by checking if they are initialized.
	assert(p_engine_container->symbol_engine_isrush() != NULL); 
	assert(p_engine_container->symbol_engine_raisers() != NULL);
	assert(p_engine_container->symbol_engine_userchair() != NULL);
	assert(p_engine_container->symbol_engine_active_dealt_playing() != NULL);
}

CSymbolEngineOpenTracker::~CSymbolEngineOpenTracker() {
}

void CSymbolEngineOpenTracker::InitOnStartup() {
	check_for_identity_of_players_executed_this_heartbeat = false;
	ClearAllStats();
	OT_IMPORTER.StartThread();
}

void CSymbolEngineOpenTracker::UpdateOnConnection() {
	ClearAllStats();
	p_opentracker_thread->StartThread();
}

void CSymbolEngineOpenTracker::UpdateOnHandreset() {
  if (p_engine_container->symbol_engine_isrush()->isrush())
    ClearAllStats();
}

void CSymbolEngineOpenTracker::UpdateOnNewRound()
{}

void CSymbolEngineOpenTracker::UpdateOnMyTurn()
{}

void CSymbolEngineOpenTracker::UpdateOnHeartbeat()
{
	check_for_identity_of_players_executed_this_heartbeat = false;
}

void CSymbolEngineOpenTracker::WarnAboutInvalidOTSymbol(CString s) {
	CString error_message;
  error_message.Format("Invalid OpenTracker-symbol: %s\n", s);
	CParseErrors::MessageBox_Formula_Error(error_message, "Error");
}

bool CSymbolEngineOpenTracker::IsOldStyleOTSymbol(CString s) {
  if (s.Left(2) == "ot") {
    return false;
  }
  if (s.Left(3) != "ot_") {
    return true;
  } 
  if (s.Left(5) == "ot_r_") {
    return true;
  }
  return false;
}

void CSymbolEngineOpenTracker::CheckForChangedPlayersOncePerHeartbeatAndSymbolLookup() {
	if (check_for_identity_of_players_executed_this_heartbeat)
	{
		return;
	}
	check_for_identity_of_players_executed_this_heartbeat = true;
	ClearAllStatsOfChangedPlayers();
}

void CSymbolEngineOpenTracker::ClearSeatStats(int chair, bool clearNameAndFound) {
	assert(chair >= kFirstChair); 
	assert(chair <= kLastChair);
	write_log(Preferences()->debug_opentracker(), "[CSymbolEngineOpenTracker] ClearSeatStats() for chair %i\n", chair);
	OT_DLL_ClearPlayerStats(chair);
	if (clearNameAndFound) {
		_ot_player_data[chair].found = false;
		memset(_ot_player_data[chair].ot_name, 0, kMaxLengthOfPlayername);
		memset(_ot_player_data[chair].scraped_name, 0, kMaxLengthOfPlayername);
	}
	_ot_player_data[chair].skipped_updates = k_ot_advanced_stat_update_every;
}

void CSymbolEngineOpenTracker::ClearAllStatsOfChangedPlayers() {
	write_log(Preferences()->debug_opentracker(), "[CSymbolEngineOpenTracker] Executing ClearAllStatsOfChangedPlayers()\n");
	for (int i=0; i<kMaxNumberOfPlayers; i++)
	{
		if (p_opentracker_thread->CheckIfNameHasChanged(i))
		{
			ClearSeatStats(i, true);
		}
	}
}

void CSymbolEngineOpenTracker::ClearAllStats()
{
	for (int i=0; i<kMaxNumberOfPlayers; i++)
	{
		ClearSeatStats(i, true);
	}
}

int CSymbolEngineOpenTracker::PlayerIcon(const int chair) {
  assert(chair >= 0);
  assert(chair <= kLastChair);
  return OT_DLL_GetStat("icon", chair);
}

bool CSymbolEngineOpenTracker::EvaluateSymbol(const CString name, double *result, bool log /* = false */) {
  FAST_EXIT_ON_OPENPPL_SYMBOLS(name);
	if (memcmp(name, "ot_", 3) != 0) {
		// Symbol of a different symbol-engine
		return false;
	}
	CheckForChangedPlayersOncePerHeartbeatAndSymbolLookup();
	if (IsOldStyleOTSymbol(name))	{
		CString error_message;
		error_message.Format(
			"Old style OpenTracker symbol detected: %s.\n"
			"\n"
			"OpenTracker symbol start with \"ot_\".\n"
      "Possible postfixes:\n"
      "  * chair number (0..9)\n"
      "  * _raischair\n"
      "  * _headsupchair\n"
      "  * _smallblindchair\n"
      "  * _bigblindchair\n"
      "  * _dealerchair\n"
      "  * _cutoffchair\n"
      "  * _userchair\n"
      "  * _firstraiserchair\n"
      "  * _firstcallerchair\n"
      "  * _lastcallerchair\n", name);
		CParseErrors::MessageBox_Formula_Error(
			error_message,			 
			"ERROR: Invalid OpenTracker Symbol");
		*result = kUndefined;
		return true;
	}
	if (!OT_DLL_IsValidSymbol(CString(name)))	{
		// Invalid OpenTracker symbol
		WarnAboutInvalidOTSymbol(name);
		*result = kUndefined;
		return true;
	}
	int chair = 0;
	if (!p_opentracker_thread->IsConnected()) 	{
		if (!p_engine_container->symbol_engine_userchair()->userchair_confirmed() || p_formula_parser->IsParsing()) {
			// We are not yet seated or formula is getting parsed.
			// Symbol-lookup happens, because of Formula-validation.
			// Not a problem, if we do not yet have a DB-connection.
			// Don't throw a warning here.
      write_log(Preferences()->debug_opentracker(), "[OpenTracker] Not yet seated or formula parsing.\n");
		} else {
			// We are seated and playing, use a OT-symbol,
      // but are noit connected to a database
      if (CParseTreeTerminalNodeEndOfFunction::evaluating_defailt_logic()) {
        // Not a problem
        // The default-bot uses OT-symbols,
        // but also plays well against unknown.
        // Lots of people will use it without a DB
      } else {
        // Serious problem: OT-usage in user-code
        MessageBox_Error_Warning("Not connected to OpenTracker database.\n"
          "Can't use OpenTracker symbols.");
      }
		}
		*result = kUndefined;
		return true;
	}	else {
		CString last_character = name.Right(1);
    if (!isdigit(last_character[0])) {
      CString error_message;
      error_message.Format("Invalid OpenTracker Symbol: %s",
        name);
      CParseErrors::MessageBox_Formula_Error(error_message, "ERROR");
		  *result = kUndefined;
      return false;
    }
		chair = atoi(last_character);
	}


  // Catch undefined chair (e.g. ot_r_-symbol without raisee)
  if (chair < 0) {
    *result = kUndefined;
    return true;
  }
	AssertRange(chair, kFirstChair, kLastChair);
	*result = OT_DLL_GetStat(name, chair); 
	return true;
}

CString CSymbolEngineOpenTracker::SymbolsProvided() {
  CString list;
  for (int i=0; i<OT_DLL_GetNumberOfStats(); ++i) {
    CString basic_symbol_name = OT_DLL_GetBasicSymbolNameWithoutPTPrefix(i);
    // Add symbol for raise-chair
    CString new_symbol = "ot_" + basic_symbol_name + "_raischair";
    list.AppendFormat(" %s", new_symbol);
    // Add symbol for headsup-chair...
    new_symbol = "ot_" + basic_symbol_name + "_headsup";
	  list.AppendFormat(" %s", new_symbol);
    // ... and all similar symbols
    new_symbol = "ot_" + basic_symbol_name + "_smallblind";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_bigblind";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_cutoff";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_firstcaller";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_lastcaller";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_firstraiser";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_dealer";
	  list.AppendFormat(" %s", new_symbol);
    new_symbol = "ot_" + basic_symbol_name + "_user";
	  list.AppendFormat(" %s", new_symbol);

    // Add symbols for all chairs, indexed by trailing numbers
    for (int j=0; j<kMaxNumberOfPlayers; j++) {
	    new_symbol.Format("ot_%s%i", basic_symbol_name, j); 
	    list.AppendFormat(" %s", new_symbol);
    }
  }
  return list;
}
