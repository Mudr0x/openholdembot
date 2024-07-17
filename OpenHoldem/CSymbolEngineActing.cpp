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
#include "CSymbolEngineActing.h"

#include "CBetroundCalculator.h"

#include "CScraper.h"
#include "CStringMatch.h"
#include "CTableState.h"


CSymbolEngineActing::CSymbolEngineActing() {
	// The values of some symbol-engines depend on other engines.
	// As the engines get later called in the order of initialization
	// we assure correct ordering by checking if they are initialized.
  //
	// This engine does not use any other engines.
}

CSymbolEngineActing::~CSymbolEngineActing() {
}

void CSymbolEngineActing::InitOnStartup() {
}

void CSymbolEngineActing::UpdateOnConnection() {
}

void CSymbolEngineActing::UpdateOnHandreset() {
}

void CSymbolEngineActing::UpdateOnNewRound() {
}

void CSymbolEngineActing::UpdateOnMyTurn() {
}

void CSymbolEngineActing::UpdateOnHeartbeat() {
}

bool CSymbolEngineActing::EvaluateSymbol(const CString name, double *result, bool log /* = false */) {
	FAST_EXIT_ON_OPENPPL_SYMBOLS(name);
	if (memcmp(name, "isacting", 8) != 0 && memcmp(name, "action", 6) != 0) {
		// Symbol of a different symbol-engine
		return false;
	}
	if ((memcmp(name, "isacting", 8) == 0) && (strlen(name) == 9)) {
		// isacting0..isacting9
		int index = RightDigitCharacterToNumber(name);
		*result = p_table_state->Player(index)->acting();
		return true;
	}
	if ((memcmp(name, "action", 6) == 0) && (strlen(name) == 7)) {
		// action0..action9
		int index = RightDigitCharacterToNumber(name);
		*result = p_table_state->Player(index)->get_action();
		return true;
	}
	// Symbol of a different symbol-engine
	return false;
}

CString CSymbolEngineActing::SymbolsProvided() {
	CString symbols;
	symbols += RangeOfSymbols("isacting%i", kFirstChair, kLastChair);
	symbols += RangeOfSymbols("action%i", kFirstChair, kLastChair);
	return symbols;
}

int CSymbolEngineActing::IsActing(const int chair) {
	assert(chair >= 0);
	assert(chair <= kLastChair);
	// Scraped colour-code 
	// Coloour-code for PT-Icon removed in rev. 4283,
	// as PT4 does no longer support the auto-rate-icon
	return p_table_state->Player(chair)->acting();
}