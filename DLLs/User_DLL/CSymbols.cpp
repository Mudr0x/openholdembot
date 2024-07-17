#include "CSymbols.h"
#include "CSymbolsPokerTracker.h"

void CSymbols::UpdateOHSymbols()
{
	/////////////////////////////
	// double vars
	/////////////////////////////

	// money vars
	dirty_ac_first_doubleo_pot();
	dirty_ante();
	dirty_avgbetspf();
	dirty_balanceatstartofsession();
	dirty_bblind();
	dirty_sblind();
	dirty_call();
	dirty_lim();
	dirty_maxbalance();
	dirty_pot();
	dirty_potcommon();
	dirty_potplayer();

	//prwin vars;
	dirty_prlos();
	dirty_prlosnow();
	dirty_prtie();
	dirty_prwin();
	dirty_prwinnow();

	// seen betround % vars
	dirty_floppct();
	dirty_riverpct();
	dirty_turnpct();

	dirty_tablepfr();

	//////////////////////////
	// int vars
	//////////////////////////
	// common cards
	dirty_$$cc0();
	dirty_$$cc1();
	dirty_$$cc2();
	dirty_$$cc3();
	dirty_$$cc4();
	// common ranks
	dirty_$$cr0();
	dirty_$$cr1();
	dirty_$$cr2();
	dirty_$$cr3();
	dirty_$$cr4();
	// common suits
	dirty_$$cs0();
	dirty_$$cs1();
	dirty_$$cs2();
	dirty_$$cs3();
	dirty_$$cs4();
	// hero cards
	dirty_$$pc0();
	dirty_$$pc1();
	// hero ranks
	dirty_$$pr0();
	dirty_$$pr1();
	// hero suits
	dirty_$$ps0();
	dirty_$$ps1();
	// ac
	dirty_ac_agchair_after();
	dirty_ac_postflop_pos();
	dirty_ac_prefloprais_pos();

	// chairs
	dirty_bigblindchair();
	dirty_cutoffchair();
	dirty_dealerchair();
	dirty_firstcallerchair();
	dirty_firstraiserchair();
	dirty_headsupchair();
	dirty_lastcallerchair();
	dirty_lastraiserchair();
	dirty_smallblindchair();

	// position
	dirty_betposition();
	dirty_betpositionrais();
	dirty_callposition();
	dirty_dealposition();
	dirty_dealpositionrais();

	dirty_betround();
	dirty_handsplayed();

	// n
	dirty_nbetstocall();
	dirty_nbetstorais();
	dirty_ncallbets();
	dirty_ncardsbetter();
	dirty_ncardsknown();
	dirty_ncardsunknown();
	dirty_nchairs();
	dirty_nchairsdealtleft();
	dirty_nchairsdealtright();
	dirty_ncommoncardsknown();
	dirty_ncurrentbets();
	dirty_nhands();
	dirty_nhandshi();
	dirty_nhandslo();
	dirty_nhandsti();
	dirty_nopponentsactive();
	dirty_nopponentsbetting();
	dirty_nopponentsblind();
	dirty_nopponentscalling();
	dirty_nopponentschecking();
	dirty_nopponentsdealt();
	dirty_nopponentsfolded();
	dirty_nopponentsplaying();
	dirty_nopponentsseated();
	dirty_nopponentstruelyraising();
	dirty_nouts();
	dirty_nplayersactive();
	dirty_nplayersblind();
	dirty_nplayerscallshort();
	dirty_nplayersdealt();
	dirty_nplayersplaying();
	dirty_nplayersseated();
	dirty_nraisbets();
	dirty_nranked();
	dirty_nrankedcommon();
	dirty_nstraight();
	dirty_nstraightcommon();
	dirty_nstraightfill();
	dirty_nstraightfillcommon();
	dirty_nstraightflush();
	dirty_nstraightflushcommon();
	dirty_nstraightflushfill();
	dirty_nstraightflushfillcommon();
	dirty_nsuited();
	dirty_nsuitedcommon();

	dirty_elapsed();
	dirty_elapsedauto();
	dirty_elapsedhand();
	dirty_elapsedtoday();

	dirty_fmax();

	dirty_handrank1000();
	dirty_handrank1326();
	dirty_handrank169();
	dirty_handrank2652();
	dirty_handrankp();

	dirty_prevaction();

	dirty_rankhi();
	dirty_rankhicommon();
	dirty_rankhiplayer();
	dirty_rankhipoker();
	dirty_ranklo();
	dirty_ranklocommon();
	dirty_rankloplayer();
	dirty_ranklopoker();

	dirty_srankhi();
	dirty_srankhicommon();
	dirty_srankhiplayer();
	dirty_srankhipoker();

	dirty_sranklo();
	dirty_sranklocommon();
	dirty_srankloplayer();
	dirty_sranklopoker();

	dirty_trank();
	dirty_trankcommon();
	dirty_tsuit();
	dirty_tsuitcommon();

	dirty_raischair();
	dirty_userchair();

	dirty_didcall();
	dirty_didchec();
	dirty_didrais();
	dirty_didbetsize();


	/////////////////////////////
	// unsigned int vars
	/////////////////////////////
	dirty_bblindbits();
	dirty_flagbits();
	dirty_opponentsactivebits();
	dirty_opponentsblindbits();
	dirty_opponentsdealtbits();
	dirty_opponentsplayingbits();
	dirty_opponentsseatedbits();
	dirty_npcbits();
	dirty_pcbits();
	dirty_playersactivebits();
	dirty_playersblindbits();
	dirty_playersdealtbits();
	dirty_playersplayingbits();
	dirty_playersseatedbits();
	dirty_pokerval();
	dirty_pokervalcommon();
	dirty_rankbits();
	dirty_rankbitscommon();
	dirty_rankbitsplayer();
	dirty_rankbitspoker();
	dirty_srankbits();
	dirty_srankbitscommon();
	dirty_srankbitsplayer();
	dirty_srankbitspoker();
	dirty_myturnbits();

	//////////////////////////
	// bool vars
	//////////////////////////

	dirty_isautopost();
	dirty_isconnector();
	dirty_isfinalanswer();
	dirty_isfinaltable();
	dirty_isfl();
	dirty_isflush();
	dirty_isfourofakind();
	dirty_isfullhouse();
	dirty_ishandup();
	dirty_ishandupcommon();
	dirty_ishicard();
	dirty_ishiflush();
	dirty_ishipair();
	dirty_ishistraight();
	dirty_islopair();
	dirty_ismidpair();
	dirty_ismyturn();
	dirty_isnl();
	dirty_isomaha();
	dirty_isonepair();
	dirty_ispair();
	dirty_ispl();
	dirty_isroyalflush();
	dirty_issittingin();
	dirty_issittingout();
	dirty_isstraight();
	dirty_isstraightflush();
	dirty_issuited();
	dirty_isthreeofakind();
	dirty_istournament();
	dirty_istwopair();

	// chairs
	for (size_t i = 0; i < k_max_chairs; i++)
	{
		/////////////////////////////
		// double seat vars
		/////////////////////////////
		dirty_balance(i);
		dirty_currentbet(i);
		//dirty_icm_alliwin(i);
		dirty_stack(i);

		/////////////////////////////
		// int seat vars
		/////////////////////////////
		dirty_ac_betpos(i);
		dirty_ac_dealpos(i);
	}

	// rounds
	for (size_t i = 1; i < eRounds; i++)
	{
		/////////////////////////////
		// double round vars
		/////////////////////////////
		dirty_balance_rank(i);
		dirty_bet(i);

		/////////////////////////////
		// int round vars
		/////////////////////////////
		dirty_nbetsround(i);
		dirty_nplayersround(i);
		dirty_lastraised(i);

		/////////////////////////////
		// unsigned int round vars
		/////////////////////////////
		dirty_callbits(i);
		dirty_foldbits(i);
		dirty_raisbits(i);

		/////////////////////////////
		// bool round vars
		/////////////////////////////
		dirty_didcallround(i);
		dirty_didchecround(i);
		dirty_didraisround(i);
		dirty_didbetsizeround(i);
	}

	// suits
	for (size_t i = 0; i < 4; i++)
	{
		dirty_suitbitscommon(i);
	}

	/*
	dirty_flush();
	dirty_fourofakind();
	dirty_fullhouse();
	dirty_hicard();
	dirty_onepair();
	dirty_pokerval();
	dirty_pokervalcommon();
	dirty_pokervalplayer();
	dirty_straight();
	dirty_straightflush();
	dirty_royalflush();
	dirty_threeofakind();
	dirty_twopair();
	*/

	/*
	// f buttons on
	dirty_f0();
	dirty_f1();
	dirty_f2();
	dirty_f3();
	dirty_f4();
	dirty_f5();
	dirty_f6();
	dirty_f7();
	dirty_f8();
	dirty_f9();
	dirty_f10();
	dirty_f11();
	dirty_f12();
	dirty_f13();
	dirty_f14();
	dirty_f15();
	dirty_f16();
	dirty_f17();
	dirty_f18();
	dirty_f19();
	*/

	/*
	// tournament bubble stuff
	dirty_icm();
	// icm_alliloseX
	dirty_icm_allilose4();
	dirty_icm_allilose5();
	dirty_icm_alliloseBB();
	dirty_icm_alliloseCO();
	dirty_icm_alliloseD();
	dirty_icm_alliloseSB();
	dirty_icm_alliloseUTG();
	dirty_icm_alliloseUTG1();
	dirty_icm_alliloseUTG2();
	dirty_icm_alliloseUTG3();
	dirty_icm_alliloseUTG6();
	dirty_icm_allilose1();
	// icm_allitieX
	dirty_icm_allitie4();
	dirty_icm_allitie5();
	dirty_icm_allitieBB();
	dirty_icm_allitieCO();
	dirty_icm_allitieD();
	dirty_icm_allitieSB();
	dirty_icm_allitieUTG();
	dirty_icm_allitieUTG1();
	dirty_icm_allitieUTG2();
	dirty_icm_allitieUTG3();
	dirty_icm_allitieUTG6();
	// icm_alliwinX
	dirty_icm_alliwinBB();
	dirty_icm_alliwinCO();
	dirty_icm_alliwinD();
	dirty_icm_alliwinSB();
	dirty_icm_alliwinUTG();
	dirty_icm_alliwinUTG1();
	dirty_icm_alliwinUTG2();
	dirty_icm_alliwinUTG3();
	dirty_icm_alliwinUTG6();

	dirty_icm_calllose();
	dirty_icm_calltie();
	dirty_icm_callwin();
	dirty_icm_fold();
	*/

	/*
	// multi table tournament stuff
	dirty_mtt_number_entrants();
	dirty_mtt_players_remaining();
	dirty_mtt_paid_places();
	dirty_mtt_my_rank();
	dirty_mtt_largest_stack();
	dirty_mtt_average_stack();
	dirty_mtt_smallest_stack();
	*/

	/*
	// random stuff
	dirty_random();
	dirty_randomhand();
	dirty_randomheartbeat();
	dirty_randomround();
	*/

	//dirty_session();
	//dirty_version();

	/*
	// versus stuff - requires versus.bin
	dirty_vs$list();
	dirty_vs$nhands();
	dirty_vs$nhandshi();
	dirty_vs$nhandshinow();
	dirty_vs$nhandslo();
	dirty_vs$nhandslonow();
	dirty_vs$nhandsti();
	dirty_vs$nhandstinow();

	dirty_vs$prlos();
	dirty_vs$prloshi();
	dirty_vs$prloshinow();
	dirty_vs$prloslo();
	dirty_vs$prloslonow();
	dirty_vs$prlosti();
	dirty_vs$prlostinow();

	dirty_vs$prtie();
	dirty_vs$prtiehi();
	dirty_vs$prtiehinow();
	dirty_vs$prtielo();
	dirty_vs$prtielonow();
	dirty_vs$prtieti();
	dirty_vs$prtietinow();

	dirty_vs$prwin();
	dirty_vs$prwinhi();
	dirty_vs$prwinhinow();
	dirty_vs$prwinlo();
	dirty_vs$prwinlonow();
	dirty_vs$prwdoublei();
	dirty_vs$prwdoubleinow();
	*/

	_pt.UpdatePTSymbols();
}
