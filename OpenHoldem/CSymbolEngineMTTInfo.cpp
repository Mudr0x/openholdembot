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
#include "CSymbolEngineMTTInfo.h"

#include "CBetroundCalculator.h"

#include "CScraper.h"
#include "CStringMatch.h"
#include "CTableState.h"


CSymbolEngineMTTInfo::CSymbolEngineMTTInfo() {
	// The values of some symbol-engines depend on other engines.
	// As the engines get later called in the order of initialization
	// we assure correct ordering by checking if they are initialized.
	//
	// This engine does not use any other engines.
}

CSymbolEngineMTTInfo::~CSymbolEngineMTTInfo() {
}

void CSymbolEngineMTTInfo::InitOnStartup() {
	UpdateOnConnection();
}

void CSymbolEngineMTTInfo::UpdateOnConnection() {
	_mtt_number_entrants.Reset();
	_mtt_players_remaining.Reset();
	_mtt_my_rank.Reset();
	_mtt_paid_places.Reset();
	_mtt_largest_stack.Reset();
	_mtt_average_stack.Reset();
	_mtt_blind_level.Reset();
	_mtt_tourney_type.Reset();
	_mtt_p0bounty.Reset();
	_mtt_p1bounty.Reset();
	_mtt_p2bounty.Reset();
	_mtt_p3bounty.Reset();
	_mtt_p4bounty.Reset();
	_mtt_p5bounty.Reset();
	_mtt_p6bounty.Reset();
	_mtt_p7bounty.Reset();
	_mtt_p8bounty.Reset();
	_mtt_p9bounty.Reset();
	_mtt_bubble00.Reset();
	_mtt_bubble01.Reset();
	_mtt_bubble02.Reset();
	_mtt_bubble03.Reset();
	_mtt_bubble04.Reset();
	_mtt_bubble05.Reset();
	_mtt_bubble06.Reset();
	_mtt_bubble07.Reset();
	_mtt_bubble08.Reset();
	_mtt_bubble09.Reset();
	_mtt_bubble10.Reset();
	_mtt_bubble11.Reset();
	_mtt_bubble12.Reset();
	_mtt_bubble13.Reset();
	_mtt_bubble14.Reset();
	_mtt_bubble15.Reset();
	_mtt_bubble16.Reset();
	_mtt_bubble17.Reset();	
	_mtt_bounty_value.Reset();
}

void CSymbolEngineMTTInfo::UpdateOnHandreset() {
}

void CSymbolEngineMTTInfo::UpdateOnNewRound() {
}

void CSymbolEngineMTTInfo::UpdateOnMyTurn() {
}

void CSymbolEngineMTTInfo::UpdateOnHeartbeat() {
}

bool CSymbolEngineMTTInfo::EvaluateSymbol(const CString name, double *result, bool log /* = false */)
{
  FAST_EXIT_ON_OPENPPL_SYMBOLS(name);
  if (memcmp(name, "mtt_", 4) != 0) {
    // Symbol of a different symbol-engine
	  return false;
  }
	// MTT symbols
  if (memcmp(name, "mtt_number_entrants", 19)==0)        *result = _mtt_number_entrants.GetValue();
  else if (memcmp(name, "mtt_players_remaining", 21)==0) *result = _mtt_players_remaining.GetValue();
  else if (memcmp(name, "mtt_my_rank", 11)==0)	         *result = _mtt_my_rank.GetValue();
  else if (memcmp(name, "mtt_paid_places", 15)==0)       *result = _mtt_paid_places.GetValue();
  else if (memcmp(name, "mtt_largest_stack", 17)==0)	   *result = _mtt_largest_stack.GetValue();
  else if (memcmp(name, "mtt_average_stack", 17)==0)	   *result = _mtt_average_stack.GetValue();
  else if (memcmp(name, "mtt_smallest_stack", 18)==0) 	 *result = _mtt_smallest_stack.GetValue();
  else if (memcmp(name, "mtt_blind_level", 15)==0) 	 *result = _mtt_blind_level.GetValue();
  else if (memcmp(name, "mtt_tourney_type", 16)==0) 	 *result = _mtt_tourney_type.GetValue();
  else if (memcmp(name, "mtt_timebank", 12)==0) 	 *result = _mtt_timebank.GetValue();
  else if (memcmp(name, "mtt_isbounty", 12)==0) 	 *result = _mtt_isbounty.GetValue();
  else if (memcmp(name, "mtt_p0bounty", 12)==0) 	 *result = _mtt_p0bounty.GetValue();
  else if (memcmp(name, "mtt_p1bounty", 12)==0) 	 *result = _mtt_p1bounty.GetValue();
  else if (memcmp(name, "mtt_p2bounty", 12)==0) 	 *result = _mtt_p2bounty.GetValue();
  else if (memcmp(name, "mtt_p3bounty", 12)==0) 	 *result = _mtt_p3bounty.GetValue();
  else if (memcmp(name, "mtt_p4bounty", 12)==0) 	 *result = _mtt_p4bounty.GetValue();
  else if (memcmp(name, "mtt_p5bounty", 12)==0) 	 *result = _mtt_p5bounty.GetValue();
  else if (memcmp(name, "mtt_p6bounty", 12)==0) 	 *result = _mtt_p6bounty.GetValue();
  else if (memcmp(name, "mtt_p7bounty", 12)==0) 	 *result = _mtt_p7bounty.GetValue();
  else if (memcmp(name, "mtt_p8bounty", 12)==0) 	 *result = _mtt_p8bounty.GetValue();
  else if (memcmp(name, "mtt_p9bounty", 12)==0) 	 *result = _mtt_p9bounty.GetValue();
  else if (memcmp(name, "mtt_bubble00", 12)==0) 	 *result = _mtt_bubble00.GetValue();
  else if (memcmp(name, "mtt_bubble01", 12)==0) 	 *result = _mtt_bubble01.GetValue();
  else if (memcmp(name, "mtt_bubble02", 12)==0) 	 *result = _mtt_bubble02.GetValue();
  else if (memcmp(name, "mtt_bubble03", 12)==0) 	 *result = _mtt_bubble03.GetValue();
  else if (memcmp(name, "mtt_bubble04", 12)==0) 	 *result = _mtt_bubble04.GetValue();
  else if (memcmp(name, "mtt_bubble05", 12)==0) 	 *result = _mtt_bubble05.GetValue();
  else if (memcmp(name, "mtt_bubble06", 12)==0) 	 *result = _mtt_bubble06.GetValue();
  else if (memcmp(name, "mtt_bubble07", 12)==0) 	 *result = _mtt_bubble07.GetValue();
  else if (memcmp(name, "mtt_bubble08", 12)==0) 	 *result = _mtt_bubble08.GetValue();
  else if (memcmp(name, "mtt_bubble09", 12)==0) 	 *result = _mtt_bubble09.GetValue();
  else if (memcmp(name, "mtt_bubble10", 12)==0) 	 *result = _mtt_bubble10.GetValue();
  else if (memcmp(name, "mtt_bubble11", 12)==0) 	 *result = _mtt_bubble11.GetValue();
  else if (memcmp(name, "mtt_bubble12", 12)==0) 	 *result = _mtt_bubble12.GetValue();
  else if (memcmp(name, "mtt_bubble13", 12)==0) 	 *result = _mtt_bubble13.GetValue();
  else if (memcmp(name, "mtt_bubble14", 12)==0) 	 *result = _mtt_bubble14.GetValue();
  else if (memcmp(name, "mtt_bubble15", 12)==0) 	 *result = _mtt_bubble15.GetValue();
  else if (memcmp(name, "mtt_bubble16", 12)==0) 	 *result = _mtt_bubble16.GetValue();
  else if (memcmp(name, "mtt_bubble17", 12)==0) 	 *result = _mtt_bubble17.GetValue();
  else if (memcmp(name, "mtt_bounty_value", 16)==0) 	 *result = _mtt_bounty_value.GetValue();
  else {
	  // Symbol of a different symbol-engine
	  return false;
  }
  return true;
}

// If any of these are true then we are connected to a MTT
bool CSymbolEngineMTTInfo::ConnectedToMTT() {
  return (_mtt_number_entrants.GetValue() > p_tablemap->nchairs()
	  || _mtt_players_remaining.GetValue() > p_tablemap->nchairs()
	  || _mtt_paid_places.GetValue() > p_tablemap->nchairs()
	  || _mtt_my_rank.GetValue() > p_tablemap->nchairs());
}

// If any of these are true then we are connected to a MTT or SNG
bool CSymbolEngineMTTInfo::ConnectedToAnyTournament() {
  return (_mtt_number_entrants.GetValue() > 0
    || _mtt_players_remaining.GetValue() > 0
    || _mtt_paid_places.GetValue() > 0
    || _mtt_my_rank.GetValue() > 0);
}

CString CSymbolEngineMTTInfo::SymbolsProvided() {
  return "mtt_number_entrants mtt_players_remaining mtt_paid_places mtt_my_rank "
    "mtt_largest_stack mtt_average_stack mtt_smallest_stack mtt_blind_level mtt_tourney_type mtt_timebank mtt_isbounty mtt_p0bounty mtt_p1bounty mtt_p2bounty mtt_p3bounty mtt_p4bounty mtt_p5bounty mtt_p6bounty mtt_p7bounty mtt_p8bounty mtt_p9bounty mtt_bubble00 mtt_bubble01 mtt_bubble02 mtt_bubble03 mtt_bubble04 mtt_bubble05 mtt_bubble06 mtt_bubble07 mtt_bubble08 mtt_bubble09 mtt_bubble10 mtt_bubble11 mtt_bubble12 mtt_bubble13  mtt_bubble14 mtt_bubble15 mtt_bubble16 mtt_bubble17 mtt_bounty_value";
}

double CSymbolEngineMTTInfo::blindlevel() {
	return _mtt_blind_level.GetValue();
}
