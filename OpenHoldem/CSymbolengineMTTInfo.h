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

#ifndef INC_CSymbolEngineMTTInfo_H
#define INC_CSymbolEngineMTTInfo_H

#include "CVirtualSymbolEngine.h"
#include "CScrapedMoney.h"

class CSymbolEngineMTTInfo: public CVirtualSymbolEngine {
 public:
	CSymbolEngineMTTInfo();
	~CSymbolEngineMTTInfo();
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
	bool ConnectedToMTT();
  bool ConnectedToAnyTournament();
  double blindlevel();
 public:
	void set_mtt_number_entrants(CString s)   { _mtt_number_entrants.SetValue(s); }
	void set_mtt_players_remaining(CString s) { _mtt_players_remaining.SetValue(s); }
	void set_mtt_my_rank(CString s)           { _mtt_my_rank.SetValue(s); }
	void set_mtt_paid_places(CString s)       { _mtt_paid_places.SetValue(s); }
	void set_mtt_largest_stack(CString s)     { _mtt_largest_stack.SetValue(s); }
	void set_mtt_average_stack(CString s)     { _mtt_average_stack.SetValue(s); }
	void set_mtt_smallest_stack(CString s)    { _mtt_smallest_stack.SetValue(s); }
	void set_mtt_blind_level(CString s)    { _mtt_blind_level.SetValue(s); }
	void set_mtt_tipo_torneio(CString s)    { _mtt_tourney_type.SetValue(s); }
	void set_mtt_timebank(CString s)    { _mtt_timebank.SetValue(s); }
	void set_mtt_isbounty(bool s)    { _mtt_isbounty.SetValue(s); }
	void set_mtt_p0bounty(CString s)    { _mtt_p0bounty.SetValue(s); }
	void set_mtt_p1bounty(CString s)    { _mtt_p1bounty.SetValue(s); }
	void set_mtt_p2bounty(CString s)    { _mtt_p2bounty.SetValue(s); }
	void set_mtt_p3bounty(CString s)    { _mtt_p3bounty.SetValue(s); }
	void set_mtt_p4bounty(CString s)    { _mtt_p4bounty.SetValue(s); }
	void set_mtt_p5bounty(CString s)    { _mtt_p5bounty.SetValue(s); }
	void set_mtt_p6bounty(CString s)    { _mtt_p6bounty.SetValue(s); }
	void set_mtt_p7bounty(CString s)    { _mtt_p7bounty.SetValue(s); }
	void set_mtt_p8bounty(CString s)    { _mtt_p8bounty.SetValue(s); }
	void set_mtt_p9bounty(CString s)    { _mtt_p9bounty.SetValue(s); }
	void set_mtt_bubble00(CString s)    { _mtt_bubble00.SetValue(s); }
	void set_mtt_bubble01(CString s)    { _mtt_bubble01.SetValue(s); }
	void set_mtt_bubble02(CString s)    { _mtt_bubble02.SetValue(s); }
	void set_mtt_bubble03(CString s)    { _mtt_bubble03.SetValue(s); }
	void set_mtt_bubble04(CString s)    { _mtt_bubble04.SetValue(s); }
	void set_mtt_bubble05(CString s)    { _mtt_bubble05.SetValue(s); }
	void set_mtt_bubble06(CString s)    { _mtt_bubble06.SetValue(s); }
	void set_mtt_bubble07(CString s)    { _mtt_bubble07.SetValue(s); }
	void set_mtt_bubble08(CString s)    { _mtt_bubble08.SetValue(s); }
	void set_mtt_bubble09(CString s)    { _mtt_bubble09.SetValue(s); }
	void set_mtt_bubble10(CString s)    { _mtt_bubble10.SetValue(s); }
	void set_mtt_bubble11(CString s)    { _mtt_bubble11.SetValue(s); }
	void set_mtt_bubble12(CString s)    { _mtt_bubble12.SetValue(s); }
	void set_mtt_bubble13(CString s)    { _mtt_bubble13.SetValue(s); }
	void set_mtt_bubble14(CString s)    { _mtt_bubble14.SetValue(s); }
	void set_mtt_bubble15(CString s)    { _mtt_bubble15.SetValue(s); }
	void set_mtt_bubble16(CString s)    { _mtt_bubble16.SetValue(s); }
	void set_mtt_bubble17(CString s)    { _mtt_bubble17.SetValue(s); }
	void set_mtt_bounty_value(CString s)    { _mtt_bounty_value.SetValue(s); }
	
	
 private:
	// MTT regions
  CScrapedMoney _mtt_number_entrants;
  CScrapedMoney _mtt_players_remaining;
  CScrapedMoney _mtt_my_rank;
  CScrapedMoney _mtt_paid_places;
  CScrapedMoney _mtt_largest_stack;
  CScrapedMoney _mtt_average_stack;
  CScrapedMoney _mtt_smallest_stack;
  CScrapedMoney _mtt_blind_level;
  CScrapedMoney _mtt_tourney_type;
  CScrapedMoney _mtt_timebank;
  CScrapedMoney _mtt_isbounty;
  CScrapedMoney _mtt_p0bounty;
  CScrapedMoney _mtt_p1bounty;
  CScrapedMoney _mtt_p2bounty;
  CScrapedMoney _mtt_p3bounty;
  CScrapedMoney _mtt_p4bounty;
  CScrapedMoney _mtt_p5bounty;
  CScrapedMoney _mtt_p6bounty;
  CScrapedMoney _mtt_p7bounty;
  CScrapedMoney _mtt_p8bounty;
  CScrapedMoney _mtt_p9bounty;
  CScrapedMoney _mtt_bubble00;
  CScrapedMoney _mtt_bubble01;
  CScrapedMoney _mtt_bubble02;
  CScrapedMoney _mtt_bubble03;
  CScrapedMoney _mtt_bubble04;
  CScrapedMoney _mtt_bubble05;
  CScrapedMoney _mtt_bubble06;
  CScrapedMoney _mtt_bubble07;
  CScrapedMoney _mtt_bubble08;
  CScrapedMoney _mtt_bubble09;
  CScrapedMoney _mtt_bubble10;
  CScrapedMoney _mtt_bubble11;
  CScrapedMoney _mtt_bubble12;
  CScrapedMoney _mtt_bubble13;
  CScrapedMoney _mtt_bubble14;
  CScrapedMoney _mtt_bubble15;
  CScrapedMoney _mtt_bubble16;
  CScrapedMoney _mtt_bubble17;
  CScrapedMoney _mtt_bounty_value;
};

extern CSymbolEngineMTTInfo *p_symbol_engine_mtt_info;

#endif INC_CSymbolEngineMTTInfo_H