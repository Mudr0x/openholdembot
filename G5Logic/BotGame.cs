using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace G5Logic
{
    public class BotGame /*: IDisposable*/
    {
        private static readonly int NUM_PLAYERS = 6;

        private OpponentModeling.Options _options;
        private OpponentModeling _opponentModeling;
        private BotGameState _botGameState; // = new BotGameState[NUM_PLAYERS];
        private Deck _deck = new Deck();

        private TableType _tableType;
        private int _heroInd;
        private int _buttonInd;
        private int _bigBlindSize;
        private int _startStackSize;
        private int[] _totalInvestedMoney = new int[6];
        private int[] _rebuysCount = new int[6];
        private int _handsPlayed;

        //private Thread t = new Thread(displayState).Start();
        //static readonly object locker = new object();

        public BotGame(int num_players, int blind_size, int hero_index, int button_index, string[] player_names, 
            int[] stack_sizes, List<int> sitting_out, List<Tuple<int, int>> hole_cards)
        {
            for (int i = 0; i < _rebuysCount.Length; i++)
                _rebuysCount[i] = 0;
            _handsPlayed = 0;
            _bigBlindSize = blind_size;
            _options = new OpponentModeling.Options();
            _options.recentHandsCount = 30;

            _tableType = (num_players == 2) ? TableType.HeadsUp : TableType.SixMax;
            var statListFile = (num_players == 2) ? "full_stats_list_hu.bin" : "full_stats_list_6max.bin";

            _opponentModeling = new OpponentModeling(statListFile, /*_bigBlindSize,*/ _tableType, _options);

            _heroInd = hero_index;
            _buttonInd = button_index;
            _startStackSize = blind_size * 100;

            //for (int i = 0; i < num_players; i++)
            //{
                _botGameState = new BotGameState(player_names, stack_sizes, hero_index, button_index, _bigBlindSize, PokerClient.G5, _tableType,
                    new Estimators.ModelingEstimator(_opponentModeling, PokerClient.G5));
            //}

            for (int i = 0; i < _totalInvestedMoney.Length; i++)
                _totalInvestedMoney[i] = _startStackSize;

            // New hand here!
            startNewHand(hero_index, button_index, player_names, stack_sizes, sitting_out, hole_cards);
        }

        private Card.Rank getRankById(int id)
        {
            switch (id)
            {
                case 0: return Card.Rank.Unknown;
                case 1: return Card.Rank.Ace;
                case 2: return Card.Rank.Deuce;
                case 3: return Card.Rank.Three;
                case 4: return Card.Rank.Four;
                case 5: return Card.Rank.Five;
                case 6: return Card.Rank.Six;
                case 7: return Card.Rank.Seven;
                case 8: return Card.Rank.Eight;
                case 9: return Card.Rank.Nine;
                case 10: return Card.Rank.Ten;
                case 11: return Card.Rank.Jack;
                case 12: return Card.Rank.Queen;
                case 13: return Card.Rank.King;
                case 14: return Card.Rank.Ace;
                case 15: return Card.Rank.Unknown;
                // Handle other cases or throw an exception for invalid IDs
                default:
                    //std::cerr << "Invalid rank ID: " << id << std::endl;
                    // You can throw an exception or return a default rank
                    return Card.Rank.Unknown; // Default to Unknown
            }
        }

        private Card.Suit getSuitById(int id)
        {
            switch (id)
            {
                case -1: return Card.Suit.Unknown;
                case 0: return Card.Suit.Hearts;
                case 1: return Card.Suit.Diamonds;
                case 2: return Card.Suit.Clubs;
                case 3: return Card.Suit.Spades;
                // Handle other cases or throw an exception for invalid IDs
                default:
                    //std::cerr << "Invalid suit ID: " << id << std::endl;
                    // You can throw an exception or return a default suit
                    return Card.Suit.Unknown; // Default to Unknown
            }
        }

        private Street getStreetById(int id)
        {
            switch (id)
            {
                case -1: return Street.Unknown;
                case 0: return Street.Unknown;
                case 1: return Street.PreFlop;
                case 2: return Street.Flop;
                case 3: return Street.Turn;
                case 4: return Street.River;
                // Handle other cases or throw an exception for invalid IDs
                default:
                    //std::cerr << "Invalid street ID: " << id << std::endl;
                    // You can throw an exception or return a default street
                    return Street.Unknown; // Default to Unknown
            }
        }

        private string moneyToString(int money)
        {
            return "$" + (money / 100.0f).ToString("f2");
        }

        private List<Player> getPlayers()
        {
            return _botGameState.getPlayers();
        }

        private void WriteLog(String str)
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine(str);
            Console.ResetColor();

            // Output logs to HandHistory log file
            File.AppendAllText("handhistory.txt", str + "\n");
        }

        private void finishHand()
        {
            var handStrengths = new List<int>();

            for (int i = 0; i < NUM_PLAYERS; i++)
            {
                if (_botGameState.getBoard().Count == 5) // TODO CHeeeeeeeeeeck
                {
                    var handStrength = _botGameState.calculateHeroHandStrength(i);
                    handStrengths.Add(handStrength.Value());
                }
                else
                {
                    handStrengths.Add(0);
                }
            }

            var winnings = Pot.calculateWinnings(getPlayers(), handStrengths);

            WriteLog("** Summary **");
            for (int i = 0; i < NUM_PLAYERS; i++)
            {
                var player = getPlayers()[i];
                bool has_kwown_cards = true;
                if (_botGameState.getPlayerHoleCards()[i].Card0.rank == Card.Rank.Unknown)
                    has_kwown_cards = false;
                else if (_botGameState.getPlayerHoleCards()[i].Card0.suit == Card.Suit.Unknown)
                    has_kwown_cards = false;
                else if (_botGameState.getPlayerHoleCards()[i].Card1.rank == Card.Rank.Unknown)
                    has_kwown_cards = false;
                else if (_botGameState.getPlayerHoleCards()[i].Card1.suit == Card.Suit.Unknown)
                    has_kwown_cards = false;
                if (has_kwown_cards && getPlayers()[i].StatusInHand != Status.Folded)
                    WriteLog(player.Name + " shows [ " + _botGameState.getPlayerHoleCards()[i].Card0 + ", " + _botGameState.getPlayerHoleCards()[i].Card1 + " ]");
            }

            for (int i = 0; i < winnings.Count; i++)
            {
                if (winnings[i] > 0)
                {
                    int winning;
                    var player = getPlayers()[i];
                    if (player.PreFlopPosition == Position.SB)
                        winning = winnings[i] - 2;
                    else if (player.PreFlopPosition == Position.BB)
                        winning = winnings[i] - 4;
                    else
                        winning = winnings[i];
                    WriteLog(player.Name + " collected [ " + moneyToString(winning) + " ]");
                }
            }
            // End of hand line break
            WriteLog("");

            //foreach (var botGameState in _botGameStates)
                _botGameState.finishHand(winnings);

            _opponentModeling.addHand(_botGameState.getCurrentHand());
        }

        public int getHandsPlayed()
        {
            return _handsPlayed;
        }

        public void startNewHand(int hero_index, int button_index, string[] player_names, int[] stack_sizes, List<int> sitting_out, List<Tuple<int, int>> hole_cards)
        {
            _handsPlayed++;
            _heroInd = hero_index;
            _buttonInd = button_index;
            _botGameState.setHeroInd(hero_index);
            _botGameState.setButtonInd(button_index);
            List<int> sittingOutPlayers = sitting_out;
            //_gameTableControl.updateHandsPlayed(_handsPlayed);

            DateTime currentDateTime = DateTime.Now;
            string rawDateTime = currentDateTime.ToString("FFFFFFF");
            string formattedDateTime = currentDateTime.ToString("dd MM yyyy HH:mm:ss");
            WriteLog("#Game No : " + rawDateTime);
            WriteLog("***** 888poker Hand History for Game " + rawDateTime + " *****");
            WriteLog("$0.02/$0.04 Blinds No Limit Holdem - *** " + formattedDateTime);
            WriteLog("Table Athens 6 Max (Real Money)");

            /*
            for (int i = 0; i < NUM_PLAYERS; i++)
            {
                var player = getPlayers()[i];

                if (player.Stack < _bigBlindSize * 2)
                {
                    if (_gameTableControl.getNoRebuy() && i != _heroInd && _handsPlayed > 1)
                    {
                        sittingOutPlayers.Add(i);
                    }
                    else
                    {
                        foreach (var botGameState in _botGameStates)
                            botGameState.playerBringsIn(i, _startStackSize);

                        //string pos = " (" + getPlayers()[_heroInd].PreFlopPosition.ToString() + ")";
                        //WriteLog(player.Name + pos + " Brings in " + moneyToString(_startStackSize));

                        if (_handsPlayed > 1)
                        {
                            _totalInvestedMoney[i] += _startStackSize;
                            _rebuysCount[i]++;
                        }
                    }
                }
                int playerStack = player.Stack;
                double bb100 = (((playerStack - _totalInvestedMoney[i]) / _bigBlindSize) * 100) / _handsPlayed;
                //_gameTableControl.updatebbWon(i, _rebuysCount[i], bb100);
            }

            _deck.reset();
            */

            _botGameState.startNewHand(sittingOutPlayers);
            for (int i = 0; i < NUM_PLAYERS; i++)
            {
                var player = getPlayers()[i];
                player.Name = player_names[i];
                player.Stack = stack_sizes[i];
                if (player.PreFlopPosition == Position.BU)
                    WriteLog("Seat " + (i + 1).ToString() + " is the button");
            }
            WriteLog("Total number of players : " + NUM_PLAYERS);
                Card card0 = new Card(); Card card1 = new Card();// Card ucard = new Card();
                card0.rank = getRankById(hole_cards[0].Item1);
                card0.suit = getSuitById(hole_cards[0].Item2);
                card1.rank = getRankById(hole_cards[1].Item1);
                card1.suit = getSuitById(hole_cards[1].Item2);
                //ucard.rank = Card.Rank.Unknown;
                //ucard.suit = Card.Suit.Unknown;
                //if (i == _heroInd)
                    _botGameState.dealHoleCards(card0, card1);
                //else
                //    _botGameStates[i].dealHoleCards(ucard, ucard);
            for (int i = 0; i < NUM_PLAYERS; i++)
            {
                var player = getPlayers()[i];
                int playerStack = player.Stack;
                string playerName = player.Name;
                //string position = " (" + player.PreFlopPosition.ToString() + ")";
                WriteLog("Seat " + (i + 1).ToString() + ": " + playerName + " ( " + moneyToString(playerStack) + " )");
            }
            for (int i = 0; i < NUM_PLAYERS; i++)
            {
                var player = getPlayers()[i];
                if (player.PreFlopPosition == Position.SB)
                    WriteLog(player.Name + " posts small blind [" + moneyToString(player.BetAmount) + "]");
                if (player.PreFlopPosition == Position.BB)
                    WriteLog(player.Name + " posts big blind [" + moneyToString(player.BetAmount) + "]");
            }

            WriteLog("** Dealing down cards **");
            string holeCards = _botGameState.getHeroHoleCards().Card0.ToString() + ", " + _botGameState.getHeroHoleCards().Card1.ToString();
            WriteLog("Dealt to " + getPlayers()[_heroInd].Name + " [ " + holeCards + " ]");
        }

        public void nextStreet(int next_street, List<Tuple<int, int>> board_cards)
        {
            Street street = getStreetById(next_street);
            int numCardsToDraw = (street == Street.PreFlop) ? 3 : 1;
            Card card0 = new Card(); Card card1 = new Card(); Card card2 = new Card();
            Card card3 = new Card(); Card card4 = new Card();
            List<Card> cards = new List<Card>();
            var cardStr = "";
            if (numCardsToDraw == 3)
            {
                card0.rank = getRankById(board_cards[0].Item1);
                card0.suit = getSuitById(board_cards[0].Item2);
                card1.rank = getRankById(board_cards[1].Item1);
                card1.suit = getSuitById(board_cards[1].Item2);
                card2.rank = getRankById(board_cards[2].Item1);
                card2.suit = getSuitById(board_cards[2].Item2);
                cardStr += card0.ToString() + ", "; cardStr += card1.ToString() + ", "; cardStr += card2.ToString();
                cards.Add(card0); cards.Add(card1); cards.Add(card2);
            }
            if (numCardsToDraw == 1)
            {
                if (street == Street.Flop)
                {
                    card3.rank = getRankById(board_cards[3].Item1);
                    card3.suit = getSuitById(board_cards[3].Item2);
                    cardStr += card3.ToString();
                    cards.Add(card3);
                }
                if (street == Street.Turn)
                {
                    card4.rank = getRankById(board_cards[4].Item1);
                    card4.suit = getSuitById(board_cards[4].Item2);
                    cardStr += card4.ToString();
                    cards.Add(card4);
                }
            }

            WriteLog("** Dealing " + (street + 1).ToString().ToLower() + " ** [ " + cardStr + " ]");

            //foreach (var botGameState in _botGameStates)
                _botGameState.goToNextStreet(cards);
        }

        public void setPlayerAction(int chair, int actionType, int amountInPot, List<Tuple<int, int>> holecards)
        {
            if (_botGameState.numActivePlayers() < 2)
                return;

            Card card0 = new Card(); Card card1 = new Card();// Card ucard = new Card();
            card0.rank = getRankById(holecards[0].Item1);
            card0.suit = getSuitById(holecards[0].Item2);
            card1.rank = getRankById(holecards[1].Item1);
            card1.suit = getSuitById(holecards[1].Item2);

            HoleCards hole_cards = new HoleCards(0);
            hole_cards.Card0 = card0; hole_cards.Card1 = card1;

            _botGameState.setPlayerHoleCards(chair, hole_cards);

            int playerToActInd = _botGameState.getPlayerToActInd();
            if (playerToActInd != chair && playerToActInd != -1)
            {
                /*if (_botGameState.numActivePlayers() < 2)
                    playerToActInd = -1;
                else*/
                playerToActInd = chair;
                _botGameState.setPlayerToActInd(chair);
            }

            /* if (playerToActInd < 0)
             {
                 Street street = _botGameState.getStreet();

                 if (street == Street.River || _botGameState.numActivePlayers() < 2)
                 {
                     finishHand();
                     //startNewHand();
                 }
             }
             else
             {*/
            //if (_botGameState.getHero().StatusInHand == Status.ToAct)
            //    Debug.Assert(playerToActInd != _heroInd);

            //var bd = _botGameStates[playerToActInd].calculateHeroAction();

            //double amount = Convert.ToDouble(bd.byAmount) / 100;
            //var workTimeStr = "[" + bd.timeSpentSeconds.ToString("f2") + "s]";

            //if (playerToActInd != -1)
            //{
                var actionStr = "";

                if (actionType == (int)ActionType.Fold)
                {
                    actionStr = " folds";
                    playerFolds();
                }
                else if (actionType == (int)ActionType.Check || actionType == (int)ActionType.Call)
                {
                    if (actionType == (int)ActionType.Check)
                        actionStr = " checks";

                    if (actionType == (int)ActionType.Call)
                        actionStr = " calls [" + moneyToString(amountInPot) + "]";

                    playerCheckCalls(amountInPot);
                }
                else if (actionType == (int)ActionType.Bet || actionType == (int)ActionType.Raise || actionType == (int)ActionType.AllIn)
                {
                    if (actionType == (int)ActionType.Bet)
                        actionStr = " bets [" + moneyToString(amountInPot) + "]";

                    if (actionType == (int)ActionType.Raise)
                        actionStr = " raises [" + moneyToString(amountInPot) + "]";

                    if (actionType == (int)ActionType.AllIn)
                        actionStr = ((_botGameState.getNumBets() > 0) ? " raises [" : " bets [") + moneyToString(amountInPot) + "]";

                    playerBetRaisesBy(amountInPot);
                }

                var botName = getPlayers()[playerToActInd].Name;
                WriteLog(botName + actionStr);
            //}

            //else {
                int numPlayersAtShowdown = 0;
                for (int i = 0; i < NUM_PLAYERS; i++)
                {
                    var player = getPlayers()[i];
                    card0.rank = Card.Rank.Unknown; card0.suit = Card.Suit.Unknown;
                    card1.rank = Card.Rank.Unknown; card1.suit = Card.Suit.Unknown;
                    hole_cards.Card0 = card0; hole_cards.Card1 = card1;
                    if (player.StatusInHand != Status.Folded && _botGameState.getPlayerHoleCards()[i] != hole_cards)
                        numPlayersAtShowdown++;
                }
                Street street = _botGameState.getStreet();
                if ((street == Street.River && playerToActInd == -1/* && numPlayersAtShowdown > 1*/) || _botGameState.numActivePlayers() < 2)
                    finishHand();
            //}
        }

        unsafe public string GetDecision(int chair, int amountToCall, int* amountInPot)
        {
            //if (_botGameState.calculateHeroAction(amountToCall, amountInPot) == "Fold")
            //    _botGameState.turnButton();
            int heroInd = _botGameState.getHeroInd();
            if (heroInd != chair)
            {
                heroInd = chair;
                _botGameState.setHeroInd(chair);
            }
            return _botGameState.calculateHeroAction(amountToCall, amountInPot);
        }

        private void playerCheckCalls(int amount)
        {
            //foreach (var botGameState in _botGameStates)
            //int playerToActInd = _botGameState.getPlayerToActInd();
            _botGameState.playerCheckCalls(amount);
        }

        private void playerBetRaisesBy(int amount)
        {
            //foreach (var botGameState in _botGameStates)
            //int playerToActInd = _botGameState.getPlayerToActInd();
            _botGameState.playerBetRaisesBy(amount);
        }

        private void playerFolds()
        {
            //foreach (var botGameState in _botGameStates)
            //int playerToActInd = _botGameState.getPlayerToActInd();
            _botGameState.playerFolds();
        }

        private void playerGoesAllIn()
        {
            //foreach (var botGameState in _botGameStates)
            //int playerToActInd = _botGameStates[_heroInd].getPlayerToActInd();
            _botGameState.playerGoesAllIn();
        }

        private void buttonFold_Click(object sender, EventArgs e)
        {
            WriteLog(_botGameState.getPlayerToAct().Name + " folds");
            playerFolds();
        }

        private void buttonCheckCall_Click(object sender, EventArgs e)
        {
            int callAmount = _botGameState.getAmountToCall();
            var actionStr = (callAmount > 0) ? " calls [" + moneyToString(callAmount) + "]" : " checks";
            WriteLog(_botGameState.getPlayerToAct().Name + actionStr);
            playerCheckCalls(callAmount);
        }

        private void buttonBetRaise_Click(object sender, int raiseAmount)
        {
            var ra = (raiseAmount == 0) ? _botGameState.getRaiseAmount(raiseAmount) : raiseAmount;
            var actionStr = (_botGameState.getNumBets() > 0) ? " raises [" : " bets [" + moneyToString(raiseAmount) + "]";
            WriteLog(_botGameState.getPlayerToAct().Name + actionStr);

            playerBetRaisesBy(ra);
        }

        private void buttonAllin_Click(object sender, int raiseAmount)
        {
            WriteLog(_botGameState.getPlayerToAct().Name + ((_botGameState.getNumBets() > 0) ? " raises [" : " bets [") + moneyToString(raiseAmount) + "]");
            playerGoesAllIn();
        }
        /*
        private void textBoxEditBet_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Return)
            {
                string str_betsize = _gameTableControl.textBoxEditBet.Text;
                int raiseAmount = Convert.ToInt32(Convert.ToDouble(str_betsize) * 100);
                var actionStr = ((_botGameStates[_heroInd].getNumBets() > 0) ? " raises [" : " bets [") + moneyToString(raiseAmount) + "]";
                WriteLog(_botGameStates[_heroInd].getPlayerToAct().Name + actionStr);

                playerBetRaisesBy(raiseAmount);
            }
        }*/

        /*
        public void Dispose()
        {
            //_actionEstimator.Dispose();
        }*/
    }
}
