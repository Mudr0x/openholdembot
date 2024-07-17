#pragma once
#include "Common.h"


namespace G5Decision
{
    class PostFlopParams
    {
        TableType tableType;
        Street street;
        int round;
        ActionType prevStreetAction;
        int numBets;
        bool inPosition;
        int numPlayers;

    public:
        PostFlopParams(TableType tt, Street street, int round, ActionType prevStreetAction, int numBets, bool inPosition, int numPlayers);

        bool forcedAction() const;
        int toIndex() const;
    };
}
