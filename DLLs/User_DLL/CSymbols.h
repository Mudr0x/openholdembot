#pragma once

#include "OpenHoldemVariables.h"
#include "CSymbolsPokerTracker.h"

class CSymbols
{
	/////////////////////////////
	// double vars
	/////////////////////////////

	// money vars
	OH_VAR(ac_first_doubleo_pot);
	OH_VAR(ante);
	OH_VAR(avgbetspf);
	OH_VAR(balanceatstartofsession);
	OH_VAR(bblind);
	OH_VAR(sblind);
	OH_VAR(call);
	OH_VAR(lim);
	OH_VAR(maxbalance);
	OH_VAR(pot);
	OH_VAR(potcommon);
	OH_VAR(potplayer);

	//prwin vars
	OH_VAR(prlos);
	OH_VAR(prlosnow);
	OH_VAR(prtie);
	OH_VAR(prwin);
	OH_VAR(prwinnow);

	// seen betround % vars
	OH_VAR(floppct);
	OH_VAR(riverpct);
	OH_VAR(turnpct);
	
	OH_VAR(tablepfr);

	//////////////////////////
	// int vars
	//////////////////////////
	// common cards
	OH_VAR_INT($$cc0);
	OH_VAR_INT($$cc1);
	OH_VAR_INT($$cc2);
	OH_VAR_INT($$cc3);
	OH_VAR_INT($$cc4);
	// common ranks
	OH_VAR_INT($$cr0);
	OH_VAR_INT($$cr1);
	OH_VAR_INT($$cr2);
	OH_VAR_INT($$cr3);
	OH_VAR_INT($$cr4);
	// common suits
	OH_VAR_INT($$cs0);
	OH_VAR_INT($$cs1);
	OH_VAR_INT($$cs2);
	OH_VAR_INT($$cs3);
	OH_VAR_INT($$cs4);
	// hero cards
	OH_VAR_INT($$pc0);
	OH_VAR_INT($$pc1);
	// hero ranks
	OH_VAR_INT($$pr0);
	OH_VAR_INT($$pr1);
	// hero suits
	OH_VAR_INT($$ps0);
	OH_VAR_INT($$ps1);
	// ac
	OH_VAR_INT(ac_agchair_after);
	OH_VAR_INT(ac_postflop_pos);
	OH_VAR_INT(ac_prefloprais_pos);

	// chairs
	OH_VAR_INT(bigblindchair);
	OH_VAR_INT(cutoffchair);
	OH_VAR_INT(dealerchair);
	OH_VAR_INT(firstcallerchair);
	OH_VAR_INT(firstraiserchair);
	OH_VAR_INT(headsupchair);
	OH_VAR_INT(lastcallerchair);
	OH_VAR_INT(lastraiserchair);
	OH_VAR_INT(smallblindchair);

	// position
	OH_VAR_INT(betposition);
	OH_VAR_INT(betpositionrais);
	OH_VAR_INT(callposition);
	OH_VAR_INT(dealposition);
	OH_VAR_INT(dealpositionrais);

	OH_VAR_INT(betround);
	OH_VAR_INT(handsplayed);

	// n
	OH_VAR_INT(nbetstocall);
	OH_VAR_INT(nbetstorais);
	OH_VAR_INT(ncallbets);
	OH_VAR_INT(ncardsbetter);
	OH_VAR_INT(ncardsknown);
	OH_VAR_INT(ncardsunknown);
	OH_VAR_INT(nchairs);
	OH_VAR_INT(nchairsdealtleft);
	OH_VAR_INT(nchairsdealtright);
	OH_VAR_INT(ncommoncardsknown);
	OH_VAR_INT(ncurrentbets);
	OH_VAR_INT(nhands);
	OH_VAR_INT(nhandshi);
	OH_VAR_INT(nhandslo);
	OH_VAR_INT(nhandsti);
	OH_VAR_INT(nopponentsactive);
	OH_VAR_INT(nopponentsbetting);
	OH_VAR_INT(nopponentsblind);
	OH_VAR_INT(nopponentscalling);
	OH_VAR_INT(nopponentschecking);
	OH_VAR_INT(nopponentsdealt);
	OH_VAR_INT(nopponentsfolded);
	OH_VAR_INT(nopponentsplaying);
	OH_VAR_INT(nopponentsseated);
	OH_VAR_INT(nopponentstruelyraising);
	OH_VAR_INT(nouts);
	OH_VAR_INT(nplayersactive);
	OH_VAR_INT(nplayersblind);
	OH_VAR_INT(nplayerscallshort);
	OH_VAR_INT(nplayersdealt);
	OH_VAR_INT(nplayersplaying);
	OH_VAR_INT(nplayersseated);
	OH_VAR_INT(nraisbets);
	OH_VAR_INT(nranked);
	OH_VAR_INT(nrankedcommon);
	OH_VAR_INT(nstraight);
	OH_VAR_INT(nstraightcommon);
	OH_VAR_INT(nstraightfill);
	OH_VAR_INT(nstraightfillcommon);
	OH_VAR_INT(nstraightflush);
	OH_VAR_INT(nstraightflushcommon);
	OH_VAR_INT(nstraightflushfill);
	OH_VAR_INT(nstraightflushfillcommon);
	OH_VAR_INT(nsuited);
	OH_VAR_INT(nsuitedcommon);

	OH_VAR_INT(elapsed);
	OH_VAR_INT(elapsedauto);
	OH_VAR_INT(elapsedhand);
	OH_VAR_INT(elapsedtoday);

	OH_VAR_INT(fmax);

	OH_VAR_INT(handrank1000);
	OH_VAR_INT(handrank1326);
	OH_VAR_INT(handrank169);
	OH_VAR_INT(handrank2652);
	OH_VAR_INT(handrankp);

	OH_VAR_INT(prevaction);

	OH_VAR_INT(rankhi);
	OH_VAR_INT(rankhicommon);
	OH_VAR_INT(rankhiplayer);
	OH_VAR_INT(rankhipoker);
	OH_VAR_INT(ranklo);
	OH_VAR_INT(ranklocommon);
	OH_VAR_INT(rankloplayer);
	OH_VAR_INT(ranklopoker);

	OH_VAR_INT(srankhi);
	OH_VAR_INT(srankhicommon);
	OH_VAR_INT(srankhiplayer);
	OH_VAR_INT(srankhipoker);

	OH_VAR_INT(sranklo);
	OH_VAR_INT(sranklocommon);
	OH_VAR_INT(srankloplayer);
	OH_VAR_INT(sranklopoker);

	OH_VAR_INT(trank);
	OH_VAR_INT(trankcommon);
	OH_VAR_INT(tsuit);
	OH_VAR_INT(tsuitcommon);

	OH_VAR_INT(raischair);
	OH_VAR_INT(userchair);


	/////////////////////////////
	// unsigned int vars
	/////////////////////////////
	OH_VAR_UNSIGNED_INT(bblindbits);
	OH_VAR_UNSIGNED_INT(flagbits);
	OH_VAR_UNSIGNED_INT(opponentsactivebits);
	OH_VAR_UNSIGNED_INT(opponentsblindbits);
	OH_VAR_UNSIGNED_INT(opponentsdealtbits);
	OH_VAR_UNSIGNED_INT(opponentsplayingbits);
	OH_VAR_UNSIGNED_INT(opponentsseatedbits);
	OH_VAR_UNSIGNED_INT(npcbits);
	OH_VAR_UNSIGNED_INT(pcbits);
	OH_VAR_UNSIGNED_INT(playersactivebits);
	OH_VAR_UNSIGNED_INT(playersblindbits);
	OH_VAR_UNSIGNED_INT(playersdealtbits);
	OH_VAR_UNSIGNED_INT(playersplayingbits);
	OH_VAR_UNSIGNED_INT(playersseatedbits);
	OH_VAR_UNSIGNED_INT(pokerval);
	OH_VAR_UNSIGNED_INT(pokervalcommon);
	OH_VAR_UNSIGNED_INT(rankbits);
	OH_VAR_UNSIGNED_INT(rankbitscommon);
	OH_VAR_UNSIGNED_INT(rankbitsplayer);
	OH_VAR_UNSIGNED_INT(rankbitspoker);
	OH_VAR_UNSIGNED_INT(srankbits);
	OH_VAR_UNSIGNED_INT(srankbitscommon);
	OH_VAR_UNSIGNED_INT(srankbitsplayer);
	OH_VAR_UNSIGNED_INT(srankbitspoker);
	OH_VAR_UNSIGNED_INT(myturnbits);

	//////////////////////////
	// bool vars
	//////////////////////////

	OH_VAR_BOOL(isautopost);
	OH_VAR_BOOL(isconnector);
	OH_VAR_BOOL(isfinalanswer);
	OH_VAR_BOOL(isfinaltable);
	OH_VAR_BOOL(isfl);
	OH_VAR_BOOL(isflush);
	OH_VAR_BOOL(isfourofakind);
	OH_VAR_BOOL(isfullhouse);
	OH_VAR_BOOL(ishandup);
	OH_VAR_BOOL(ishandupcommon);
	OH_VAR_BOOL(ishicard);
	OH_VAR_BOOL(ishiflush);
	OH_VAR_BOOL(ishipair);
	OH_VAR_BOOL(ishistraight);
	OH_VAR_BOOL(islopair);
	OH_VAR_BOOL(ismidpair);
	OH_VAR_BOOL(ismyturn);
	OH_VAR_BOOL(isnl);
	OH_VAR_BOOL(isomaha);
	OH_VAR_BOOL(isonepair);
	OH_VAR_BOOL(ispair);
	OH_VAR_BOOL(ispl);
	OH_VAR_BOOL(isroyalflush);
	OH_VAR_BOOL(issittingin);
	OH_VAR_BOOL(issittingout);
	OH_VAR_BOOL(isstraight);
	OH_VAR_BOOL(isstraightflush);
	OH_VAR_BOOL(issuited);
	OH_VAR_BOOL(isthreeofakind);
	OH_VAR_BOOL(istournament);
	OH_VAR_BOOL(istwopair);

	/////////////////////////////
	// double seat vars
	/////////////////////////////
	OH_SEAT_VAR(balance);
	OH_SEAT_VAR(currentbet);
	OH_SEAT_VAR(icm_alliwin);
	OH_SEAT_VAR(stack);
	/////////////////////////////
	// int seat vars
	/////////////////////////////
	OH_SEAT_VAR_INT(ac_betpos);
	OH_SEAT_VAR_INT(ac_dealpos);


	/////////////////////////////
	// double round vars
	/////////////////////////////
	OH_ROUND_VAR(balance_rank);
	OH_ROUND_VAR(bet);

	/////////////////////////////
	// int round vars
	/////////////////////////////
	OH_ROUND_VAR_INT(nbetsround);
	OH_ROUND_VAR_INT(nplayersround);
	OH_ROUND_VAR_INT(lastraised);

	/////////////////////////////
	// unsigned int round vars
	/////////////////////////////
	OH_ROUND_VAR_UNSIGNED_INT(callbits);
	OH_ROUND_VAR_UNSIGNED_INT(foldbits);
	OH_ROUND_VAR_UNSIGNED_INT(raisbits);

	/////////////////////////////
	// bool round vars
	/////////////////////////////
	OH_VAR_INT(didcall);
	OH_ROUND_VAR_BOOL(didcallround);
	OH_VAR_INT(didchec);
	OH_ROUND_VAR_BOOL(didchecround);
	OH_VAR_INT(didrais);
	OH_ROUND_VAR_BOOL(didraisround);
	OH_VAR_INT(didbetsize);
	OH_ROUND_VAR_BOOL(didbetsizeround);


	OH_SUIT_VAR_UNSIGNED_INT(suitbitscommon);


	/*
	OH_VAR(flush);
	OH_VAR(fourofakind);
	OH_VAR(fullhouse);
	OH_VAR(hicard);
	OH_VAR(onepair);
	OH_VAR(pokervalplayer);
	OH_VAR(straight);
	OH_VAR(straightflush);
	OH_VAR(royalflush);
	OH_VAR(threeofakind);
	OH_VAR(twopair);
	*/

	/*
	// f buttons on
	OH_VAR_BOOL(f0);
	OH_VAR_BOOL(f1);
	OH_VAR_BOOL(f2);
	OH_VAR_BOOL(f3);
	OH_VAR_BOOL(f4);
	OH_VAR_BOOL(f5);
	OH_VAR_BOOL(f6);
	OH_VAR_BOOL(f7);
	OH_VAR_BOOL(f8);
	OH_VAR_BOOL(f9);
	OH_VAR_BOOL(f10);
	OH_VAR_BOOL(f11);
	OH_VAR_BOOL(f12);
	OH_VAR_BOOL(f13);
	OH_VAR_BOOL(f14);
	OH_VAR_BOOL(f15);
	OH_VAR_BOOL(f16);
	OH_VAR_BOOL(f17);
	OH_VAR_BOOL(f18);
	OH_VAR_BOOL(f19);
	*/

	/*
	// tournament bubble stuff
	OH_VAR(icm);
	// icm_alliloseX
	OH_VAR(icm_allilose4);
	OH_VAR(icm_allilose5);
	OH_VAR(icm_alliloseBB);
	OH_VAR(icm_alliloseCO);
	OH_VAR(icm_alliloseD);
	OH_VAR(icm_alliloseSB);
	OH_VAR(icm_alliloseUTG);
	OH_VAR(icm_alliloseUTG1);
	OH_VAR(icm_alliloseUTG2);
	OH_VAR(icm_alliloseUTG3);
	OH_VAR(icm_alliloseUTG6);
	OH_VAR(icm_allilose1);
	// icm_allitieX
	OH_VAR(icm_allitie4);
	OH_VAR(icm_allitie5);
	OH_VAR(icm_allitieBB);
	OH_VAR(icm_allitieCO);
	OH_VAR(icm_allitieD);
	OH_VAR(icm_allitieSB);
	OH_VAR(icm_allitieUTG);
	OH_VAR(icm_allitieUTG1);
	OH_VAR(icm_allitieUTG2);
	OH_VAR(icm_allitieUTG3);
	OH_VAR(icm_allitieUTG6);
	// icm_alliwinX
	OH_VAR(icm_alliwinBB);
	OH_VAR(icm_alliwinCO);
	OH_VAR(icm_alliwinD);
	OH_VAR(icm_alliwinSB);
	OH_VAR(icm_alliwinUTG);
	OH_VAR(icm_alliwinUTG1);
	OH_VAR(icm_alliwinUTG2);
	OH_VAR(icm_alliwinUTG3);
	OH_VAR(icm_alliwinUTG6);

	OH_VAR(icm_calllose);
	OH_VAR(icm_calltie);
	OH_VAR(icm_callwin);
	OH_VAR(icm_fold);
	*/

	/*
	// multi table tournament stuff
	OH_VAR(mtt_number_entrants);
	OH_VAR(mtt_players_remaining);
	OH_VAR(mtt_paid_places);
	OH_VAR(mtt_my_rank);
	OH_VAR(mtt_largest_stack);
	OH_VAR(mtt_average_stack);
	OH_VAR(mtt_smallest_stack);
	*/

	/*
	// random stuff
	OH_VAR(random);
	OH_VAR(randomhand);
	OH_VAR(randomheartbeat);
	OH_VAR(randomround);
	*/

	//OH_VAR(session);
	//OH_VAR(version);

	/*
	// versus stuff - requires versus.bin
	OH_VAR(vs$list);
	OH_VAR(vs$nhands);
	OH_VAR(vs$nhandshi);
	OH_VAR(vs$nhandshinow);
	OH_VAR(vs$nhandslo);
	OH_VAR(vs$nhandslonow);
	OH_VAR(vs$nhandsti);
	OH_VAR(vs$nhandstinow);

	OH_VAR(vs$prlos);
	OH_VAR(vs$prloshi);
	OH_VAR(vs$prloshinow);
	OH_VAR(vs$prloslo);
	OH_VAR(vs$prloslonow);
	OH_VAR(vs$prlosti);
	OH_VAR(vs$prlostinow);

	OH_VAR(vs$prtie);
	OH_VAR(vs$prtiehi);
	OH_VAR(vs$prtiehinow);
	OH_VAR(vs$prtielo);
	OH_VAR(vs$prtielonow);
	OH_VAR(vs$prtieti);
	OH_VAR(vs$prtietinow);

	OH_VAR(vs$prwin);
	OH_VAR(vs$prwinhi);
	OH_VAR(vs$prwinhinow);
	OH_VAR(vs$prwinlo);
	OH_VAR(vs$prwinlonow);
	OH_VAR(vs$prwdoublei);
	OH_VAR(vs$prwdoubleinow);
	*/

	CSymbolsPokerTracker _pt;
	

public:
	void UpdateOHSymbols();
};

extern CSymbols* g_symbols;