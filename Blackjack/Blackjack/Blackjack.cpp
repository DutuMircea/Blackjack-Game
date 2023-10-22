// Blackjack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <cstddef>
#include <random>
#include <algorithm>
#include <ctime>

const int MAX_SCORE{ 21 };
const int MIN_DEALER_SCORE{ 17 };

enum class CardType {  // all types of cards
    clover,  // 0
    diamond,
    heart,
    spade, // 3

    max_type,  

enum class CardRank { 
    rank_2, // 0
    rank_3, // 1
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace, // 12

    max_rank, 
};

struct Card {
    CardType type{};  // each card has a type and a rank
    CardRank rank{};
};

struct Player {  
    int score{};
};

enum class Result {  // all the possible outcomes
    player_win,
    player_lose,
    tie,
};

void printCard(const Card& card) {  // function for printing the type and rank of a card
    
    switch (card.type) 
    {
    case CardType::clover:
        std::cout << 'C';
        break;
    case CardType::diamond:
        std::cout << 'D';
        break;
    case CardType::heart:
        std::cout << 'H';
        break;
    case CardType::spade:
        std::cout << 'S';
        break;
    }

    switch (card.rank) 
    {
    case CardRank::rank_2: 
        std::cout << '2';
        break;
    case CardRank::rank_3:  
        std::cout << '3';
        break;
    case CardRank::rank_4:
        std::cout << '4';
        break;
    case CardRank::rank_5:
        std::cout << '5';
        break;
    case CardRank::rank_6:
        std::cout << '6';
        break;
    case CardRank::rank_7:
        std::cout << '7';
        break;
    case CardRank::rank_8:
        std::cout << '8';
        break;
    case CardRank::rank_9:
        std::cout << '9';
        break;
    case CardRank::rank_10:
        std::cout << 'T';
        break;
    case CardRank::rank_jack:
        std::cout << 'J';
        break;
    case CardRank::rank_queen:
        std::cout << 'Q';
        break;
    case CardRank::rank_king:
        std::cout << 'K';
        break;
    case CardRank::rank_ace:
        std::cout << 'A';
        break;
    }
    
}

int getValue(const Card& card) { 

    switch (card.rank) {
    case CardRank::rank_2:
        return 2;
    case CardRank::rank_3:
        return 3;
    case CardRank::rank_4:
        return 4;
    case CardRank::rank_5:
        return 5;
    case CardRank::rank_6:
        return 6;
    case CardRank::rank_7:
        return 7;
    case CardRank::rank_8:
        return 8;
    case CardRank::rank_9:
        return 9;
    case CardRank::rank_10:
        return 10;
    case CardRank::rank_jack:
        return 10;
    case CardRank::rank_queen:
        return 10;
    case CardRank::rank_king:
        return 10;
    case CardRank::rank_ace:
        return 11;     
    }
}

void printDeck(std::array<Card,52>& deck) {
    

    for (auto& card : deck) { // iterating through the deck and printing the card
        printCard(card); 
        std::cout << ' ';
    }

    std::cout << '\n';
}
std::array<Card, 52> generateDeck() { 
   
    std::array<Card, 52> deck{}; // the deck has 52 cards

    std::array<Card, 52>::size_type i{ 0 }; // indexul trb sa fie te tip array pt a face atribuire

    for (int type{ 0 }; type < static_cast<int>(CardType::max_type); type++) { // iteratin through all the card
        for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_rank); rank++) {
            deck[i].type = static_cast<CardType>(type); 
            deck[i].rank = static_cast<CardRank>(rank); 
            i++; // next card
        }
    }

    return deck;
}

void ShuffleDeck(std::array<Card, 52>& deck) {

    static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    // generating a random number
    std::shuffle(deck.begin(), deck.end(), mt);
}

bool playerHitorStand() {

    std::cout << "Press (h) to hit or (s) to stand: ";

    char ch{};
    std::cin >> ch;

    if (ch == 'h')
        return true;
    if (ch == 's')
        return false;
}

bool PlayerTurn(std::array<Card,52>& deck, std::array<Card, 52>::size_type& nextCard, Player& player ) {

    while (true) {
        if (player.score > MAX_SCORE) { // losing condition of the player
            //std::cout << "YOU LOSE!\n";
            return true;
        }
        else {
            if (playerHitorStand()) { 
                int cardValue{ getValue(deck[nextCard++]) }; // drawing a card from the deck
                player.score += cardValue; // adding the value of the card to the score

                std::cout << "You received a (";
                printCard(deck[nextCard - 1]);
                nextCard++;
                std::cout << ") " << cardValue << " with a TOTAL SCORE: " << player.score << '\n';
                
            }
            else {
                return false; 
            }
        }
    }
}
bool DealerTurn(std::array<Card, 52>& deck, std::array<Card, 52>::size_type& nextCard, Player& dealer) {

    while (dealer.score < MIN_DEALER_SCORE) { // dealer keeps drawing card until it passes the min score

        int cardValue{ getValue(deck[nextCard++]) };
        
        dealer.score += cardValue;
        std::cout << "The dealer received a (";
        printCard(deck[nextCard - 1]);
        nextCard++;
        std::cout << ") " << cardValue << " with a TOTAL SCORE: " << dealer.score << '\n';
    }

    if (dealer.score > MAX_SCORE) { // losing condition of the dealer
        std::cout << "The dealer lost! \n";
        return true;  
    }

    return false; // a tecut randul dealerului
}

Result playGame(std::array<Card, 52>& deck) {
    std::array<Card, 52>::size_type nextCard{0}; // indexul arrayul trebuie sa fie de tipu asta  overflow(??) nope

    Player dealer{ getValue(deck[nextCard++]) }; // the dealer draws a card
    std::cout << "The dealer got (";
    printCard(deck[nextCard - 1]);
    nextCard++;
    std::cout << ") " << dealer.score <<  " points \n"; // the score is shown each time the player draws

    Player player{ getValue(deck[nextCard]) + getValue(deck[nextCard++]) }; //the player draws 2 cards
    nextCard += 2;

    std::cout << "You received " << player.score << " points \n";
    
    
    if (PlayerTurn(deck, nextCard, player)) 
        return Result::player_lose;   // the player loses
   
    if(DealerTurn(deck, nextCard, dealer))
        return Result::player_win; // the player wins

    
   if (player.score > dealer.score)
        return Result::player_win;
    else {
        if (player.score == dealer.score)  // draw condition
            return Result::tie;
    }
    
 
}
int main()
{
    std::array<Card, 52> deck{generateDeck()}; // generating the deck

    while (true) {
        ShuffleDeck(deck); 

        switch (static_cast<int>(playGame(deck))) {
                case 0: 
                    std::cout << "YOU WIN!";
                    break;
                case 1:
                    std::cout << "YOU LOSE!";
                    break;
                case 2: 
                    std::cout << "IT'S A DRAW!";
                    break;
        }

        std::cout << "\nTry again?  YES(any button) / NO(n): \n";
        char ch{};
        std::cin >> ch;

        if (ch == 'n')
            break;
    }
}

