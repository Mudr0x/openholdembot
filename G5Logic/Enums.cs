namespace G5Logic
{
    /// <summary>
    /// Enumarates all supported poker clients. Eg Ladbrokes, PokerStars. Used for HH parsing..
    /// </summary>
    public enum PokerClient
    {
        Unknown = 0,
        Ladbrokes,
        Poker770,
        PartyPoker,
        PokerStars,
        G5,
        Acpc,
        PokerKing
    }

    /// <summary>
    /// Game type (Omaha, Hold'Em ...)
    /// </summary>
    public enum GameType
    {
        Unknown = 0,
        HoldEm,
        Omaha
    }

    // HeadsUp, SixMax
    public enum TableType
    {
        HeadsUp = 2,
        SixMax = 6
    }

    /// <summary>
    /// HighCard, Flush, Poker ...
    /// </summary>
    public enum HandRank
    {
        HighCard = 0,
        OnePair,
        TwoPair,
        Trips,
        Set,
        Straight,
        Flush,
        FullHouse,
        Poker,
        SFlush,
        Count
    };

    /// <summary>
    /// A state in which there can be a game (Flop, Turn, River...)
    /// </summary>
    public enum Street
    {
        Unknown = 0,
        PreFlop,
        Flop,
        Turn,
        River,
        Count
    };

    /// <summary>
    /// Player position on table: Button, CutOff...
    /// </summary>
    public enum Position
    {
        BU = 0,
        SB = 1,
        BB = 2,
        UTG = 3,
        HJ = 4,
        CO = 5,
        Empty = 6,
    }

    /// <summary>
    /// Moguce akcije igraca: Fold, Call, Check, ukljucujuci Wins, MoneyReturned...
    /// </summary>
    public enum ActionType
    {
        Fold,
        Check,
        Call,
        Bet,
        Raise,
        AllIn,
        Wins,
        MoneyReturned,
        NoAction
    };

    public enum OmahaPreFlopStyle
    {
        Agressive,
        Passive
    }

    public enum RaiseAmount
    {
        OneThirdPot,
        HalfPot,
        TwoThirdsPot,
        PotSize
    }

    public enum LimitType
    {
        FL,
        PL,
        NL
    }

    /// <summary>
    /// Status of player in current Hand. Eg. Folded, AllIn...
    /// </summary>
    public enum Status
    {
        ToAct,
        Acted,
        Folded,
        AllIn
    };
}
