// This is the main DLL file.

#include "pch.h"
//#include "G5Wrapper.h"

#include <string>
#include <vector>
#include <utility>

#using "G5Logic.dll"


#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <msclr/auto_gcroot.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices; // Marshal
using namespace msclr::interop;

using namespace G5Logic;
using namespace std;


class G5WrapperPrivate
{
	public: msclr::auto_gcroot<BotGame^> BotGame;
};


class __declspec(dllexport) G5Wrapper
{
	private: G5WrapperPrivate* _private;

	public: G5Wrapper()
	{
		_private = new G5WrapperPrivate();
		//_private->BotGame = gcnew BotGame();
	}

	public: ~G5Wrapper()
	{
		delete _private;
	}

	public: void setPlayerAction(int chair, int actionType, int amountInPot, vector<std::pair<int, int>> holeCards)
	{
		List<Tuple<int, int>^>^ hole_cards = gcnew List<Tuple<int, int>^>();
		for (const auto& pair : holeCards)
			hole_cards->Add(Tuple::Create(pair.first, pair.second));

		_private->BotGame->setPlayerAction(chair, actionType, amountInPot, hole_cards);
	}

	public: void startGame(int num_players, int blind_size, int hero_index, int button_index, vector<string> playerNames,
		vector<int> stackSizes, vector<int> sittingOutPlayers, vector<std::pair<int, int>> holeCards)
	{
		cli::array<String^>^ player_names = gcnew cli::array<String^>(playerNames.size());  // + 1 ?
		for (size_t i = 0; i < playerNames.size(); i++)
			player_names[i] = marshal_as<String^>(playerNames[i]);

		cli::array<int>^ stack_sizes = gcnew cli::array<int>(stackSizes.size());  // + 1 ?
		for (size_t i = 0; i < stackSizes.size(); i++)
			stack_sizes[i] = stackSizes[i];

		List<int>^ sitting_out = gcnew List<int>();
		for (int value : sittingOutPlayers)
			sitting_out->Add(value);

		List<Tuple<int, int>^>^ hole_cards = gcnew List<Tuple<int, int>^>();
		for (const auto& pair : holeCards) 
			hole_cards->Add(Tuple::Create(pair.first, pair.second));

		_private->BotGame = gcnew BotGame(num_players, blind_size, hero_index, button_index, player_names, stack_sizes, sitting_out, hole_cards);
	}

	public: void startNewHand(int hero_index, int button_index, vector<string> playerNames, vector<int> stackSizes,
		vector<int> sittingOutPlayers, vector<std::pair<int, int>> holeCards)
	{
		cli::array<String^>^ player_names = gcnew cli::array<String^>(playerNames.size());  // + 1 ?
		for (size_t i = 0; i < playerNames.size(); i++)
			player_names[i] = marshal_as<String^>(playerNames[i]);

		cli::array<int>^ stack_sizes = gcnew cli::array<int>(stackSizes.size());  // + 1 ?
		for (size_t i = 0; i < stackSizes.size(); i++)
			stack_sizes[i] = stackSizes[i];

		List<int>^ sitting_out = gcnew List<int>();
		for (int value : sittingOutPlayers)
			sitting_out->Add(value);

		List<Tuple<int, int>^>^ hole_cards = gcnew List<Tuple<int, int>^>();
		for (const auto& pair : holeCards) 
			hole_cards->Add(Tuple::Create(pair.first, pair.second));

		_private->BotGame->startNewHand(hero_index, button_index, player_names, stack_sizes, sitting_out, hole_cards);
	}

	public: void nextStreet(int street, vector<std::pair<int, int>> boarCards)
	{
		List<Tuple<int, int>^>^ board_cards = gcnew List<Tuple<int, int>^>();
		for (const auto& pair : boarCards)
			board_cards->Add(Tuple::Create(pair.first, pair.second));
		_private->BotGame->nextStreet(street, board_cards);
	}

	public: string GetDecision(int chair, int amountToCall, int* amountInPot)
	{

		return marshal_as<std::string>(_private->BotGame->GetDecision(chair, amountToCall, amountInPot));
	}
};