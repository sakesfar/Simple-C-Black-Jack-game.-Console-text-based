#include <iostream>
#include<array>
#include <random>
#include <algorithm>
#include <ctime>
#include <string>

enum class CardRanks
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_Jack,
    rank_Queen,
    rank_King,
    rank_Ace,

    max_rank,

};

enum class CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,

    max_suits,

};

struct Card
{
    CardRanks rank{};
    CardSuits suit{};

};

constexpr int maximumScore{ 21 };
constexpr int minimumDealerScore{ 17 };
using arrayElType = std::array<Card, 52>::size_type;


void PrintCard(const Card& ref)
{
    switch (ref.rank)
    {
    case CardRanks::rank_2:
        std::cout << 2;
        break;
    case CardRanks::rank_3:
        std::cout << 3;
        break;

    case CardRanks::rank_4:
        std::cout << 4;
        break;

    case CardRanks::rank_5:
        std::cout << 5;
        break;

    case CardRanks::rank_6:
        std::cout << 6;
        break;

    case CardRanks::rank_7:
        std::cout << 7;
        break;

    case CardRanks::rank_8:
        std::cout << 8;
        break;

    case CardRanks::rank_9:
        std::cout << 9;
        break;

    case CardRanks::rank_10:
        std::cout << 10;
        break;

    case CardRanks::rank_Jack:
        std::cout << "J";
        break;

    case CardRanks::rank_Queen:
        std::cout << "Q";
        break;

    case CardRanks::rank_King:
        std::cout << "K";
        break;
    case CardRanks::rank_Ace:
        std::cout << "A";
        break;


    }

    switch (ref.suit)
    {
    case CardSuits::clubs:
        std::cout << "C";
        break;
    case CardSuits::spades:
        std::cout << "S";
        break;
    case CardSuits::hearts:
        std::cout << "H";
        break;
    case CardSuits::diamonds:
        std::cout << "D";
        break;


    }
}

std::array<Card, 52> CreateDeck()
{

    std::array<Card, 52> deck{};

    std::array<Card, 52>::size_type index{ 0 };

    for (int suit{ 0 }; suit < static_cast<int>(CardSuits::max_suits); ++suit)
    {
        for (int rank{ 0 }; rank < static_cast<int>(CardRanks::max_rank); ++rank)
        {
            deck[index].rank = static_cast<CardRanks>(rank);
            deck[index].suit = static_cast<CardSuits>(suit);
            ++index;
        }
    }

    return deck;

}

void PrintDeck(const std::array<Card, 52>& deck)
{
    for (const auto& i : deck)
    {
        PrintCard(i);
        std::cout << ' ';
    }
}

std::array<Card, 52> Shuffle(std::array<Card, 52>& deck)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(deck.begin(), deck.end(), mt);
    return deck;
}

int getCardValue(Card card)
{
    if (static_cast<int>(card.rank) <= 8)
        return(static_cast<int>(card.rank) + 2);
    else if (card.rank == CardRanks::rank_Ace)
        return 11;
    else
        return 10;

}

bool HitOrStand()
{
    while (true)
    {
        std::cout << "You want to hit or stand? (h/s): ";
        char hs{};
        std::cin >> hs;
        switch (hs)
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
}




bool PlayBlackJack(const std::array<Card, 52>& deck)

{
    arrayElType index{ 0 };
    int DealerCard{ getCardValue(deck.at(index++)) };
    int PlayerCards{ getCardValue(deck.at(index)) + getCardValue(deck.at(index + 1)) };
    index = index + 2;

    std::cout << "You cards show " << PlayerCards << '\n';
    std::cout << "Dealer has " << DealerCard << '\n';

    while (HitOrStand())
    {
        if (PlayerCards > maximumScore)
        {
            std::cout << "You went bust\n";
            return false;
        }

            int newCard{ getCardValue(deck.at(index++)) };
            PlayerCards += newCard;
            std::cout << "You have withdrawn a card of value " << newCard << " and now your score is " << PlayerCards << '\n';

            if (PlayerCards > maximumScore)
            {
                std::cout << "You went bust\n";
                return false;
            }
    }

    while (DealerCard < minimumDealerScore)
    {
        int newCard{ getCardValue(deck.at(index++)) };
        DealerCard += newCard;
        std::cout << "The dealer has withdrawn " << newCard << " and now has " << DealerCard<<'\n';

        if (DealerCard > maximumScore)
        {
            std::cout << "The dealer went bust\n";
            return true;
        }



    }
    
    return (PlayerCards > DealerCard);
   
}






int main()
{
    auto deck{ CreateDeck() };
    //PrintDeck(deck);
    Shuffle(deck);
    //std::cout << "\nAfter shuffling\n";
    //PrintDeck(deck);
    std::cout << "\nThe game is on\n";
    if (std::cin.fail()) // has a previous extraction failed or overflowed?
    {
        // yep, so let's handle the failure
        std::cin.clear(); // put us back in 'normal' operation mode
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
    }
    
    if (PlayBlackJack(deck))
        std::cout << "You won\n";
    else
        std::cout << "You lost\n";

    






    return 0;
}

