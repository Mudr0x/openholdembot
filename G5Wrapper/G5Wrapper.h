// G5Wrapper.h

#pragma once
#include <string>
#include <vector>
//#include <msclr/marshal.h>
//#include <msclr/marshal_cppstd.h>

//using namespace System;
//using namespace msclr::interop;

using namespace std;


class G5WrapperPrivate;

class G5Wrapper
{
private:
	//G5Logic::BotGame^ _botGame;
	G5WrapperPrivate* _private;

public:
	G5Wrapper();
	//~G5Wrapper();
	void startGame(int num_players, int blind_size, int hero_index, int button_index, vector<string> playerNames,
		vector<int> stackSizes, vector<int> sittingOutPlayers, vector<std::pair<int, int>> holeCards);
	void startNewHand(int hero_index, int button_index, vector<string> playerNames, vector<int> stackSizes,
		vector<int> sittingOutPlayers, vector<std::pair<int, int>> holeCards);
	void setPlayerAction(int chair, int actionType, int amountInPot, vector<std::pair<int, int>> holeCards);
	//void setPlayerAction(int chair, int action, int amountInPot);
	void nextStreet(int street, vector<std::pair<int, int>> boarCards);
	string GetDecision(int chair, int amountToCall, int* amountInPot);
	int getHeroInd();

private:
	int NUM_PLAYERS;
	bool is_busy = false;
};
