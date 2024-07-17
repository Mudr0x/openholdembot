#pragma once

#include <assert.h>
#include <string.h>

// Bye Bye
#include <bitset>

#include "magicNumbers.h"

//#include <poker_defs.h>

///////////////////////////////////// 
//card macros 
/////////////////////////////////////
#define RANK(c)			((c>>4)&0x0f) 
#define SUIT(c)			((c>>0)&0x0f) 
#define ISCARDBACK(c)	(c==0xff) 
#define ISUNKNOWN(c)	(c==0) 

/*
* returns count of number of bits set in the given value
*/
int	bitcount(unsigned int u);
void showbits(unsigned int x);

/*
*  Function used to compare doubles
*/
bool IsEqual(const double a, const double b);

char GetRankChar(unsigned char c);
char GetSuitChar(unsigned char c);
//int  GetNSuited(StdDeck_CardMask hand);
char Rank_ASC(int Rank);
char Suit52_ASC(int Suit);
char* Pokerval_ASC(unsigned int pokerval);

/*
* returns if player is playing at specified chair
*/
bool is_playing(int chair, int playersplayingbits);

/*
* returns if player is playing at specified chair
*/
bool is_active_bit(int chair, int testbits);