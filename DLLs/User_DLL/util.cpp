#include "util.h" 
#include <conio.h>

/*
* returns count of number of bits set in the given value
*/
int	bitcount(unsigned int u)
{
	unsigned int uCount = 0;

	uCount = u
		- ((u >> 1) & 033333333333)
		- ((u >> 2) & 011111111111);

	return ((uCount + (uCount >> 3)) & 030707070707) % 63;
}

void showbits(unsigned int x) 
{
	for (int i = (sizeof(int) * 8) - 1; i >= 0; i--) 
	{
		(x & (1u << i)) ? _cprintf("1") : _cprintf("0");
	}
	_cprintf("\n");
}

/*
*  Function used to compare doubles
*/
bool IsEqual(const double a, const double b)
{
	return ((a > (b - epsilon)) && (a < (b + epsilon)));
}

char GetRankChar(unsigned char c)
{
	const char randChars[] = "  23456789TJQKA";

	if (ISCARDBACK(c))
		return '?';
	if (ISUNKNOWN(c))
		return '_';

	return randChars[RANK(c)];
}

#if 0
char GetSuitChar(unsigned char c)
{
	const char suitChars[] = " hdcs";

	if (ISCARDBACK(c))
		return '?';
	if (ISUNKNOWN(c))
		return '_';

	return suitChars[SUIT(c)];
}
#endif
/*
int GetNSuited(StdDeck_CardMask hand)
{
	int nsuit[4];

	nsuit[0] = bitcount(StdDeck_CardMask_CLUBS(hand));
	nsuit[1] = bitcount(StdDeck_CardMask_DIAMONDS(hand));
	nsuit[2] = bitcount(StdDeck_CardMask_HEARTS(hand));
	nsuit[3] = bitcount(StdDeck_CardMask_SPADES(hand));

	for (int i = 0;i<4;i++)
	{
		for (int j = i;j<4;j++)
		{
			if (nsuit[i] > nsuit[j])
			{
				int temp = nsuit[i];
				nsuit[i] = nsuit[j];
				nsuit[j] = temp;
			}
		}
	}

	return nsuit[3];
}
*/
char Rank_ASC(int Rank)
{
	switch (Rank)
	{
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'T';
	case 11:
		return 'J';
	case 12:
		return 'Q';
	case 13:
		return 'K';
	case 14:
		return 'A';
	default:
		return '_';
	}
}

char Suit52_ASC(int Suit)
{
	switch (Suit)
	{
	case 0:
		return 'h';
	case 1:
		return 'd';
	case 2:
		return 'c';
	case 3:
		return 's';
	default:
		return '_';
	}
}

char* Pokerval_ASC(unsigned int pokerval)
{
	if (pokerval == (0x800edcba))
		return "royalflush    ";
	else if (pokerval & (1 << 31))
		return "straightflush ";
	else if (pokerval & (1 << 30))
		return "fourofakind   ";
	else if (pokerval & (1 << 29))
		return "fullhouse     ";
	else if (pokerval & (1 << 28))
		return "flush         ";
	else if (pokerval & (1 << 27))
		return "straight      ";
	else if (pokerval & (1 << 26))
		return "threeofakind  ";
	else if (pokerval & (1 << 25))
		return "twopair       ";
	else if (pokerval & (1 << 24))
		return "onepair       ";
	else if (pokerval & (1 << 0))
		return "hicard        ";
	else
		return "";
}

/*
* returns if player is playing at specified chair
*/
bool is_playing(int chair, int playersplayingbits)
{
	assert(chair >= 0 && chair < k_max_chairs);
	std::bitset<16> lok_play(playersplayingbits);

	return lok_play.test(chair);
}

/*
* returns if player is playing at specified chair
*/
bool is_active_bit(int chair, int testbits)
{
	assert(chair >= 0 && chair < k_max_chairs);
	std::bitset<16> lok_play(testbits);

	return lok_play.test(chair);
}

