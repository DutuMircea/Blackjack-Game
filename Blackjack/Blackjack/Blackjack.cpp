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

enum class CardType {  // tipurile de carti
    clover,  // 0
    diamond,
    heart,
    spade, // 3

    max_type,  // nr total de tipuri (4)
};

enum class CardRank { // numarul cartilor 2 - as
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

    max_rank, // nr total de carti (13)
};

struct Card {
    CardType type{};  // var de tip (enum) CardType
    CardRank rank{};// var de tip enum CardRank
};

struct Player {
    int score{};
};

enum class Result {
    player_win,
    player_lose,
    tie,
};

void printCard(Card& card) {  // argument de tip (struct) Card  const? transmis prin referinta & pt a nu se face copie
    
    switch (card.type) // pt fiecare type printam tipul cartii
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
    case CardRank::rank_2:  // pt fiecare rank printam nr corespunzator
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

int getValue(Card& card) { 
    // in functie de rank fiecare carte reprez un anumit nr de pct

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
    // printare pachet

    for (auto& card : deck) { // for each loop, & ca sa nu creeze copie
        printCard(card); // e bun cand avem array de tip struct ca sa nu ne complicam
        std::cout << ' ';
    }

    /*for (std::array<Card, 52>::size_type i{ 0 }; i < deck.size(); i++) {
        std:: cout << printCard(deck.rank)
    }*/

    std::cout << '\n';
}
std::array<Card, 52> generateDeck() { 
    // fct ce returneaza un array
    std::array<Card, 52> deck{}; // pachetu de joc cu 52 de carti 
    // fiecare carte avand un type si un rank

    std::array<Card, 52>::size_type i{ 0 }; // indexul trb sa fie te tip array pt a face atribuire

    for (int type{ 0 }; type < static_cast<int>(CardType::max_type); type++) { // parcurgem toate tipurile si rankurile si dam convert la int
        for (int rank{ 0 }; rank < static_cast<int>(CardRank::max_rank); rank++) {
            deck[i].type = static_cast<CardType>(type); // pt fiecare carte din pachet atribuim tipul si rankul
            deck[i].rank = static_cast<CardRank>(rank); // dam si convert de la int la tipul enum CardRank/Type
            i++; // trecem la urmatoarea carte
        }
    }

    return deck;
}

void ShuffleDeck(std::array<Card, 52>& deck) {

    static std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    // fct random generator 
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
        if (player.score > MAX_SCORE) { // daca pct din carti e mai mare de 21 ai pierdut
            //std::cout << "YOU LOSE!\n";
            return true;
        }
        else {
            if (playerHitorStand()) { // daca jucatorul doreste inca o carte
                int cardValue{ getValue(deck[nextCard++]) }; // luam valoarea urmatoarei carti din pachet
                player.score += cardValue; // se aduna la total 

                std::cout << "You received a (";
                printCard(deck[nextCard - 1]);
                nextCard++;
                std::cout << ") " << cardValue << " with a TOTAL SCORE: " << player.score << '\n';
                // daca vrem sa afisam si ce carte am primit trb sa facem overload la ">>" pt ca deckul e de tip enum
            }
            else {
                return false; // jucatorul nu a pierdut
            }
        }
    }
}
bool DealerTurn(std::array<Card, 52>& deck, std::array<Card, 52>::size_type& nextCard, Player& dealer) {

    while (dealer.score < MIN_DEALER_SCORE) { // dealerul trage carti pana trece de scorul minim

        int cardValue{ getValue(deck[nextCard++]) };
        
        dealer.score += cardValue;
        std::cout << "The dealer received a (";
        printCard(deck[nextCard - 1]);
        nextCard++;
        std::cout << ") " << cardValue << " with a TOTAL SCORE: " << dealer.score << '\n';
    }

    if (dealer.score > MAX_SCORE) { // daca dealeru trece de pct max pierde
        std::cout << "The dealer lost! \n";
        return true;  
    }

    return false; // a tecut randul dealerului
}

Result playGame(std::array<Card, 52>& deck) { // Result playGame(std::array<Card, 52>& deck)
    std::array<Card, 52>::size_type nextCard{0}; // indexul arrayul trebuie sa fie de tipu asta  overflow(??) nope

    Player dealer{ getValue(deck[nextCard++]) }; // var de tip player si primeste o carte
    std::cout << "The dealer got (";
    printCard(deck[nextCard - 1]);
    nextCard++;
    std::cout << ") " << dealer.score <<  " points \n"; // scorul dealerului

    Player player{ getValue(deck[nextCard]) + getValue(deck[nextCard++]) }; // cream player si primeste doua carti
    nextCard += 2;

    std::cout << "You received " << player.score << " points \n";
    
    
    if (PlayerTurn(deck, nextCard, player)) 
        return Result::player_lose; // daca fct returneaza true playerul a pierdut // Result::player_lose
   
    if(DealerTurn(deck, nextCard, dealer))
        return Result::player_win; // daca fct returneaza true playerul a castigat  Result::player_win

    
   if (player.score > dealer.score)
        return Result::player_win;
    else {
        if (player.score == dealer.score)
            return Result::tie;
    }
    
   // return(player.score > dealer.score); // daca playerul are scor mai mare decat dealer a castigat(true)
}
int main()
{
    std::array<Card, 52> deck{generateDeck()}; // generam pachet

    while (true) {
        ShuffleDeck(deck); // amestecam pachetu

        /*if (playGame(deck))
            std::cout << "YOU WIN!";
        else
            std::cout << "YOU LOSE!";*/

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

