using System.Collections.Generic;
using System.Diagnostics;

namespace G5Logic
{
    /// <summary>
    /// A structure that describes a single card. Contains suit and rank.
    /// </summary>
    public struct Card
    {
        /// <summary>
        /// An enum that represents the suit of the card
        /// </summary>
        public enum Suit
        {
            Unknown = -1,
            Clubs = 0,
            Diamonds,
            Hearts,
            Spades
        };

        /// <summary>
        /// An enum that represents the number (rank) of the card
        /// </summary>
        public enum Rank
        {
            Unknown = 0,
            Deuce   = 2,
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten,
            Jack,   // 11
            Queen,  // 12
            King,   // 13
            Ace     // 14
        }

        /// <summary>
        /// Card number/rank
        /// </summary>
        public Rank rank { get; set; }

        /// <summary>
        /// Color/sign/suit of cards
        /// </summary>
        public Suit suit { get; set; }

        public Card(int value) : this()
        {
            Debug.Assert(value >= 0 && value <= 51);

            suit = (Suit)(value % 4);
            rank = (Rank)(14 - value / 4);
        }

        /// <summary>
        /// Forms a suit and rank card
        /// </summary>
        /// <param name="aSuite">The suit of the future card</param>
        /// <param name="aRank">Rank of future cards</param>
        public Card(Suit aSuite, Rank aRank) : this()
        {
            suit = aSuite;
            rank = aRank;
        }

        /// <summary>
        /// The cards are formed from a string (Jh Ad 3c)
        /// </summary>
        /// <param name="stringRepresentation">A string representing the cards (Jh Ad 3c)</param>
        public Card(string stringRepresentation) : this()
        {
            Debug.Assert(stringRepresentation != null && (stringRepresentation.Length == 2 || stringRepresentation.Length == 3));

            rank = Rank.Unknown;
            suit = Suit.Unknown;

            if (stringRepresentation.Length == 2)
            {
                char charRank = stringRepresentation[0];
                char charSuite = stringRepresentation[1];

                if (charRank == '2')
                    rank = Rank.Deuce;
                else if (charRank == '3')
                    rank = Rank.Three;
                else if (charRank == '4')
                    rank = Rank.Four;
                else if (charRank == '5')
                    rank = Rank.Five;
                else if (charRank == '6')
                    rank = Rank.Six;
                else if (charRank == '7')
                    rank = Rank.Seven;
                else if (charRank == '8')
                    rank = Rank.Eight;
                else if (charRank == '9')
                    rank = Rank.Nine;
                else if (charRank == 'T')
                    rank = Rank.Ten;
                else if (charRank == 'J')
                    rank = Rank.Jack;
                else if (charRank == 'Q')
                    rank = Rank.Queen;
                else if (charRank == 'K')
                    rank = Rank.King;
                else if (charRank == 'A')
                    rank = Rank.Ace;

                if (charSuite == 'c')
                    suit = Suit.Clubs;
                else if (charSuite == 'h')
                    suit = Suit.Hearts;
                else if (charSuite == 'd')
                    suit = Suit.Diamonds;
                else if (charSuite == 's')
                    suit = Suit.Spades;
            }
            else if (stringRepresentation.Length == 3)
            {
                string stringRank = stringRepresentation.Substring(0, 2);
                char charSuite = stringRepresentation[2];

                if (stringRank == "10")
                    rank = Rank.Ten;

                if (charSuite == 'c')
                    suit = Suit.Clubs;
                else if (charSuite == 'h')
                    suit = Suit.Hearts;
                else if (charSuite == 'd')
                    suit = Suit.Diamonds;
                else if (charSuite == 's')
                    suit = Suit.Spades;
            }

            Debug.Assert(suit != Suit.Unknown && rank != Rank.Unknown);
        }

        public static string RankToString(Rank rank)
        {
            string stringCard = null;

            if (rank == Rank.Deuce)
                stringCard = "2";
            else if (rank == Rank.Three)
                stringCard = "3";
            else if (rank == Rank.Four)
                stringCard = "4";
            else if (rank == Rank.Five)
                stringCard = "5";
            else if (rank == Rank.Six)
                stringCard = "6";
            else if (rank == Rank.Seven)
                stringCard = "7";
            else if (rank == Rank.Eight)
                stringCard = "8";
            else if (rank == Rank.Nine)
                stringCard = "9";
            else if (rank == Rank.Ten)
                stringCard = "T";
            else if (rank == Rank.Jack)
                stringCard = "J";
            else if (rank == Rank.Queen)
                stringCard = "Q";
            else if (rank == Rank.King)
                stringCard = "K";
            else if (rank == Rank.Ace)
                stringCard = "A";

            return stringCard;
        }

        private string SuiteToString()
        {
            string stringCard = null;

            if (suit == Suit.Clubs)
                stringCard += "c";
            else if (suit == Suit.Diamonds)
                stringCard += "d";
            else if (suit == Suit.Hearts)
                stringCard += "h";
            else if (suit == Suit.Spades)
                stringCard += "s";

            return stringCard;
        }

        /// <summary>
        /// Returns a string representation of the cards (Tc, As, Kd, Qh ....)
        /// </summary>
        /// <returns>String representation of the cards (Tc, As, Kd, Qh ....)</returns>
        override public string ToString()
        {
            return RankToString(rank) + SuiteToString();
        }

        public int ToInt()
        {
            int value = (14 - (int)rank) * 4 + (int)suit;
            //Debug.Assert(value >= 0 && value <= 51);

            return value;
        }

        public dynamic ToRankSuite()
        {
            return new { rank = (int)rank - 2, suit = (int)suit };
        }

        public static List<Card> StringToCards(string stringRepresentation)
        {
            var cards = new List<Card>();

            if (stringRepresentation == null || stringRepresentation.Length < 2)
                return cards;

            for (var i = 0; i <= stringRepresentation.Length - 2; i += 2)
            {
                cards.Add(new Card(stringRepresentation.Substring(i, 2)));
            }

            return cards;
        }
    }
}
