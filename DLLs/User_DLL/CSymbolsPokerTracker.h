#pragma once

#include "OpenHoldemVariables.h"

class CSymbolsPokerTracker
{
	//////////////////////////
	// Basic Group
	//////////////////////////

	OH_SEAT_VAR(pt_icon);
	// VP$IP
	OH_SEAT_VAR(pt_vpip);
	// number of hands in database
	OH_SEAT_VAR(pt_hands);
	// raise 1st in
	OH_SEAT_VAR(pt_rfi);
	// went to showdown
	OH_SEAT_VAR(pt_wtsd);
	// won $ at showdown
	OH_SEAT_VAR(pt_wssd);
	// attempt to steal blinds
	OH_SEAT_VAR(pt_steal_attempt);

	// 6max
	OH_SEAT_VAR(pt_rfi_btn_6max);
	OH_SEAT_VAR(pt_rfi_co_6max);
	OH_SEAT_VAR(pt_rfi_mp_6max);
	OH_SEAT_VAR(pt_rfi_ep_6max);
	OH_SEAT_VAR(pt_rfi_sb_6max);
	// 9max
	OH_SEAT_VAR(pt_rfi_btn_9max);
	OH_SEAT_VAR(pt_rfi_co_9max);
	OH_SEAT_VAR(pt_rfi_mp2_9max);
	OH_SEAT_VAR(pt_rfi_mp1_9max);
	OH_SEAT_VAR(pt_rfi_mp_9max);
	OH_SEAT_VAR(pt_rfi_ep1_9max);
	OH_SEAT_VAR(pt_rfi_ep_9max);
	OH_SEAT_VAR(pt_rfi_sb_9max);

	//////////////////////////
	// Positional Group
	//////////////////////////

	// folded bb to steal
	OH_SEAT_VAR(pt_bb_fold_to_steal);
	// folded sb to steal
	OH_SEAT_VAR(pt_sb_fold_to_steal);
	// 3bet vs steaal
	OH_SEAT_VAR(pt_3bet_vs_steal);
	// bb 3bet vs steaal
	OH_SEAT_VAR(pt_bb_3bet_vs_steal);
	// sb 3bet vs steaal
	OH_SEAT_VAR(pt_sb_3bet_vs_steal);
	// fold to 3bet after stealing
	OH_SEAT_VAR(pt_fold_to_resteal);
	// preflop fold to 4bet
	OH_SEAT_VAR(pt_fold_to_4bet);

	//////////////////////////
	// Advanced Group
	//////////////////////////

	// preflop raise %
	OH_SEAT_VAR(pt_pfr);
	// preflop called raise
	OH_SEAT_VAR(pt_preflop_called_raise);
	// 3bet preflop
	OH_SEAT_VAR(pt_3bet);
	// folded while facing 3bet preflop
	OH_SEAT_VAR(pt_fold_to_3bet);
	//folded while facing 3bet preflop ... after raise
	OH_SEAT_VAR(pt_fold_to_3bet_afterR);
	// preflop 4B
	OH_SEAT_VAR(pt_4bet);
	// squeeze preflop %
	OH_SEAT_VAR(pt_preflop_squeeze);

	// flop agression
	OH_SEAT_VAR(pt_flop_af);
	// turn agression
	OH_SEAT_VAR(pt_turn_af);
	// river agression
	OH_SEAT_VAR(pt_river_af);
	// total agression excluding preflop
	OH_SEAT_VAR(pt_total_af);

	// flop agression frequency
	OH_SEAT_VAR(pt_flop_afq);
	// turn agression frequency
	OH_SEAT_VAR(pt_turn_afq);
	// river agression frequency
	OH_SEAT_VAR(pt_river_afq);
	// total agression frequency excluding preflop
	OH_SEAT_VAR(pt_total_afq);

	// saw flop
	OH_SEAT_VAR(pt_flop_seen);
	// saw turn
	OH_SEAT_VAR(pt_turn_seen);
	// saw river
	OH_SEAT_VAR(pt_river_seen);

	// cbet
	OH_SEAT_VAR(pt_flop_cbet);
	// folded while facing cbet flop
	OH_SEAT_VAR(pt_flop_fold_to_cbet);
	// raise flop cbet
	OH_SEAT_VAR(pt_flop_raise_cbet);
	// turn cbet
	OH_SEAT_VAR(pt_turn_cbet);
	// folded while facing cbet turn
	OH_SEAT_VAR(pt_turn_fold_to_cbet);
	// folded while facing river cbet);
	OH_SEAT_VAR(pt_river_fold_to_cbet);

	// folded while facing 3bet total without preflop
	OH_SEAT_VAR(pt_postflop_fold_to_3bet);
	// folded while facing 3bet flop
	OH_SEAT_VAR(pt_flop_fold_to_3bet);

	// flop check-raise
	OH_SEAT_VAR(pt_flopcheckraise);
	// donk flop
	OH_SEAT_VAR(pt_donkbet);
	// flop float
	OH_SEAT_VAR(pt_flop_float);

	// turn check-raise
	OH_SEAT_VAR(pt_turncheckraise);
	// turn check-call
	OH_SEAT_VAR(pt_checkcall);

	// river bet
	OH_SEAT_VAR(pt_river_bet);

	// 4bet + ratio
	OH_SEAT_VAR(pt_4bet_plus_ratio);

	// fold to pf squeeze
	OH_SEAT_VAR(pt_fold_to_pf_squeeze);
	// fold to squeeze as raiser
	OH_SEAT_VAR(pt_fold_to_squeeze_as_raiser);
	// fold to squeeze as caller
	OH_SEAT_VAR(pt_fold_to_squeeze_as_caller);

	// donk bet in 3bet+ pot%
	OH_SEAT_VAR(pt_donk_flop_in_3bet_plus_pot);
	// fold to flop continuation bet % in 3bet Pot
	OH_SEAT_VAR(pt_fold_to_f_cbet_in_3bet_pot);
	// flop continuation bet % (3bet pot)
	OH_SEAT_VAR(pt_cbet_flop_in_3bet_pot);
	// flop check-raise in 3bet pot %
	OH_SEAT_VAR(pt_flop_check_raise_in_3bet_pot);
	// flop check-raise in 3bet+ pot %
	OH_SEAT_VAR(pt_flop_check_raise_in_3bet_plus_pot);

	// fold flop check raise %
	OH_SEAT_VAR(pt_fold_to_f_check_raise);
	// fold flop check-raise % in 3bet+ Pot
	OH_SEAT_VAR(pt_fold_to_f_check_raise_3b_plus_pot);

	// float flop %
	OH_SEAT_VAR(pt_float_flop);
	// float flop in 3bet pot%
	OH_SEAT_VAR(pt_float_flop_in_3bet_pot);
	// call flop float bet %
	OH_SEAT_VAR(pt_call_f_float_bet);
	// call flop float bet in 3bet pot %
	OH_SEAT_VAR(pt_call_f_float_bet_in_3b_pot);
	// fold to flop float bet in 3bet pot %
	OH_SEAT_VAR(pt_fold_to_f_float_bet_in_3b_pot);
	// fold to flop float bet in 3bet+ pot %
	OH_SEAT_VAR(pt_fold_to_f_float_bet_in_3b_plus_pot);
	// cbet flop opportunities in 3bet + Pot
	OH_SEAT_VAR(pt_cbet_flop_opp_in_3bet_pot);

	// cbet flop opportunities
	OH_SEAT_VAR(pt_cbet_flop_opp);
	// folded while facing 3bet preflop opportunities after raise
	OH_SEAT_VAR(pt_fold_to_3bet_afterR_opp);
	// squeeze preflop % opportunities
	OH_SEAT_VAR(pt_preflop_squeeze_opp);
	// opportunities for 2 stats: flop R cbet and flop fold to cbet
	OH_SEAT_VAR(pt_flop_fold_to_cbet__flop_raise_cbet_opp);
	// donk flop opportunities
	OH_SEAT_VAR(pt_donkbet_opp);
	// fold to flop cbet % in 3bet+ pot opportunities
	OH_SEAT_VAR(pt_fold_to_f_cbet_in_3bet_plus_pot_opp);
	// fold to flop check raise opportunities
	OH_SEAT_VAR(pt_fold_to_f_check_raise_opp);
	// fold to squeeze as raiser opportunities
	OH_SEAT_VAR(pt_fold_to_squeeze_as_raiser_opp);

public:

	void UpdatePTSymbols();

};




