#include "CSymbolsPokerTracker.h"

void CSymbolsPokerTracker::UpdatePTSymbols()
{
	//////////////////////////
	// Basic Group
	//////////////////////////

	for (size_t i = 0; i < 10; i++)
	{
		//////////////////////////
		// Basic Group
		//////////////////////////

		dirty_pt_icon(i);
		// VP$IP
		dirty_pt_vpip(i);
		// number of hands in database
		dirty_pt_hands(i);
		// raise 1st in
		dirty_pt_rfi(i);
		// went to showdown
		dirty_pt_wtsd(i);
		// won $ at showdown
		dirty_pt_wssd(i);
		// attempt to steal blinds
		dirty_pt_steal_attempt(i);

		// 6max
		dirty_pt_rfi_btn_6max(i);
		dirty_pt_rfi_co_6max(i);
		dirty_pt_rfi_mp_6max(i);
		dirty_pt_rfi_ep_6max(i);
		dirty_pt_rfi_sb_6max(i);
		// 9max
		dirty_pt_rfi_btn_9max(i);
		dirty_pt_rfi_co_9max(i);
		dirty_pt_rfi_mp2_9max(i);
		dirty_pt_rfi_mp1_9max(i);
		dirty_pt_rfi_mp_9max(i);
		dirty_pt_rfi_ep1_9max(i);
		dirty_pt_rfi_ep_9max(i);
		dirty_pt_rfi_sb_9max(i);

		//////////////////////////
		// Positional Group
		//////////////////////////

		// folded bb to steal
		dirty_pt_bb_fold_to_steal(i);
		// folded sb to steal
		dirty_pt_sb_fold_to_steal(i);
		// 3bet vs steaal
		dirty_pt_3bet_vs_steal(i);
		// bb 3bet vs steaal
		dirty_pt_bb_3bet_vs_steal(i);
		// sb 3bet vs steaal
		dirty_pt_sb_3bet_vs_steal(i);
		// fold to 3bet after stealing
		dirty_pt_fold_to_resteal(i);
		// preflop fold to 4bet
		dirty_pt_fold_to_4bet(i);

		//////////////////////////
		// Advanced Group
		//////////////////////////

		// preflop raise %
		dirty_pt_pfr(i);
		// preflop called raise
		dirty_pt_preflop_called_raise(i);
		// 3bet preflop
		dirty_pt_3bet(i);
		// folded while facing 3bet preflop
		dirty_pt_fold_to_3bet(i);
		//folded while facing 3bet preflop ... after raise
		dirty_pt_fold_to_3bet_afterR(i);
		// preflop 4B
		dirty_pt_4bet(i);
		// squeeze preflop %
		dirty_pt_preflop_squeeze(i);

		// flop agression
		dirty_pt_flop_af(i);
		// turn agression
		dirty_pt_turn_af(i);
		// river agression
		dirty_pt_river_af(i);
		// total agression excluding preflop
		dirty_pt_total_af(i);

		// flop agression frequency
		dirty_pt_flop_afq(i);
		// turn agression frequency
		dirty_pt_turn_afq(i);
		// river agression frequency
		dirty_pt_river_afq(i);
		// total agression frequency excluding preflop
		dirty_pt_total_afq(i);

		// saw flop
		dirty_pt_flop_seen(i);
		// saw turn
		dirty_pt_turn_seen(i);
		// saw river
		dirty_pt_river_seen(i);

		// cbet
		dirty_pt_flop_cbet(i);
		// folded while facing cbet flop
		dirty_pt_flop_fold_to_cbet(i);
		// raise flop cbet
		dirty_pt_flop_raise_cbet(i);
		// turn cbet
		dirty_pt_turn_cbet(i);
		// folded while facing cbet turn
		dirty_pt_turn_fold_to_cbet(i);
		// folded while facing river cbet(i);
		dirty_pt_river_fold_to_cbet(i);

		// folded while facing 3bet total without preflop
		dirty_pt_postflop_fold_to_3bet(i);
		// folded while facing 3bet flop
		dirty_pt_flop_fold_to_3bet(i);

		// flop check-raise
		dirty_pt_flopcheckraise(i);
		// donk flop
		dirty_pt_donkbet(i);
		// flop float
		dirty_pt_flop_float(i);

		// turn check-raise
		dirty_pt_turncheckraise(i);
		// turn check-call
		dirty_pt_checkcall(i);

		// river bet
		dirty_pt_river_bet(i);

		// 4bet + ratio
		dirty_pt_4bet_plus_ratio(i);

		// fold to pf squeeze
		dirty_pt_fold_to_pf_squeeze(i);
		// fold to squeeze as raiser
		dirty_pt_fold_to_squeeze_as_raiser(i);
		// fold to squeeze as caller
		dirty_pt_fold_to_squeeze_as_caller(i);

		// donk bet in 3bet+ pot%
		dirty_pt_donk_flop_in_3bet_plus_pot(i);
		// fold to flop continuation bet % in 3bet Pot
		dirty_pt_fold_to_f_cbet_in_3bet_pot(i);
		// flop continuation bet % (3bet pot)
		dirty_pt_cbet_flop_in_3bet_pot(i);
		// flop check-raise in 3bet pot %
		dirty_pt_flop_check_raise_in_3bet_pot(i);
		// flop check-raise in 3bet+ pot %
		dirty_pt_flop_check_raise_in_3bet_plus_pot(i);

		// fold flop check raise %
		dirty_pt_fold_to_f_check_raise(i);
		// fold flop check-raise % in 3bet+ Pot
		dirty_pt_fold_to_f_check_raise_3b_plus_pot(i);

		// float flop %
		dirty_pt_float_flop(i);
		// float flop in 3bet pot%
		dirty_pt_float_flop_in_3bet_pot(i);
		// call flop float bet %
		dirty_pt_call_f_float_bet(i);
		// call flop float bet in 3bet pot %
		dirty_pt_call_f_float_bet_in_3b_pot(i);
		// fold to flop float bet in 3bet pot %
		dirty_pt_fold_to_f_float_bet_in_3b_pot(i);
		// fold to flop float bet in 3bet+ pot %
		dirty_pt_fold_to_f_float_bet_in_3b_plus_pot(i);
		// cbet flop opportunities in 3bet + Pot
		dirty_pt_cbet_flop_opp_in_3bet_pot(i);

		// cbet flop opportunities
		dirty_pt_cbet_flop_opp(i);
		// folded while facing 3bet preflop opportunities after raise
		dirty_pt_fold_to_3bet_afterR_opp(i);
		// squeeze preflop % opportunities
		dirty_pt_preflop_squeeze_opp(i);
		// opportunities for 2 stats: flop R cbet and flop fold to cbet
		dirty_pt_flop_fold_to_cbet__flop_raise_cbet_opp(i);
		// donk flop opportunities
		dirty_pt_donkbet_opp(i);
		// fold to flop cbet % in 3bet+ pot opportunities
		dirty_pt_fold_to_f_cbet_in_3bet_plus_pot_opp(i);
		// fold to flop check raise opportunities
		dirty_pt_fold_to_f_check_raise_opp(i);
		// fold to squeeze as raiser opportunities
		dirty_pt_fold_to_squeeze_as_raiser_opp(i);
	}

}
