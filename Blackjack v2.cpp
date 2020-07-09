// Blackjack v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// A Simple Blackjack game created by Arun TK.

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include "Enums.h"
#include "Constants.h"

int randomNumberGenerator(int, int);

class Card
{
private:
    Rank m_rank{};
    Suit m_suit{};

public:
    Card(Rank rank = Rank::RANK_2, Suit suit = Suit::SPADES) : m_rank{ rank }, m_suit{ suit }
    {}

    void print() const
    {
        switch (m_rank) {
        case Rank::RANK_2: std::cout << 2;
            break;
        case Rank::RANK_3: std::cout << 3;
            break;
        case Rank::RANK_4: std::cout << 4;
            break;
        case Rank::RANK_5: std::cout << 5;
            break;
        case Rank::RANK_6: std::cout << 6;
            break;
        case Rank::RANK_7: std::cout << 7;
            break;
        case Rank::RANK_8: std::cout << 8;
            break;
        case Rank::RANK_9: std::cout << 9;
            break;
        case Rank::RANK_10: std::cout << 10;
            break;
        case Rank::RANK_JACK: std::cout << 'J';
            break;
        case Rank::RANK_QUEEN: std::cout << 'Q';
            break;
        case Rank::RANK_KING: std::cout << 'K';
            break;
        case Rank::RANK_ACE: std::cout << 'A';
            break;
        default: std::cout << '?';
        }

        switch (m_suit) {
        case Suit::SPADES: std::cout << 's';
            break;
        case Suit::DIAMONDS: std::cout << 'd';
            break;
        case Suit::CLUBS: std::cout << 'c';
            break;
        case Suit::HEARTS: std::cout << 'h';
            break;
        }
    }

    int value() const
    {
        if (m_rank <= Rank::RANK_10) {
            return (static_cast<int>(m_rank) + 2);
        }
        else {
            switch (m_rank) {
            case Rank::RANK_JACK:
            case Rank::RANK_QUEEN:
            case Rank::RANK_KING:
                return 10;
            case Rank::RANK_ACE: return 11;

            default: return 666;

            }
        }
    }
};

class Deck
{
private:
    std::vector<Card> m_hand{};
    int m_points{};

public:
    Deck(Members a)
    {
        addCard();
        if (a == Members::Player) {
            addCard();
        }
    }

    void addCard()
    {
        //Card a{ Rank::RANK_10, Suit::CLUBS };
        auto rank{ static_cast<Rank>(randomNumberGenerator(0, static_cast<int>(Rank::MAX_RANK) - 1)) };
        auto suit{ static_cast<Suit>(randomNumberGenerator(0, static_cast<int>(Suit::MAX_SUIT) - 1)) };

        m_hand.push_back({ rank, suit });
    }

    int getPoints()
    {
        int sum{};
        for (auto i : m_hand) {
            sum += i.value();
        }
        m_points = sum;
        return sum;
    }

    void showHand() const
    {
        for (auto i : m_hand) {
            i.print();
            std::cout << ' ';
        }
        std::cout << '\n';
    }

    bool crossedLimit(int limit = BlackjackConst::blackjack)
    {
        if (m_points > limit) {
            return true;
        }
        else {
            return false;
        }
    }

    bool higherThan(Deck& a)
    {
        if (m_points >= a.m_points) {
            return true;
        }
        else {
            return false;
        }
    }

};

int randomNumberGenerator(int min, int max)
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

bool chooseOne()
{
    std::string a;
    while (true) {
        std::cin >> a;
        if (a == "y") {
            return true;
        }
        else if (a == "n") {
            return false;
        }
        else {
            std::cout << "Invalid input! Please choose again: ";
        }
    }
}

void startScreen()
{
    std::cout << "---------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "      Welcome to Blackjack!      " << std::endl;
    std::cout << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

int main()
{
    while (true) {
        system("cls");
        startScreen();

        Deck dealer{ Members::Dealer };
        Deck player{ Members::Player };

        while (true) {
            std::cout << "Dealer: ";
            dealer.showHand();
            std::cout << "Dealer points: " << dealer.getPoints() << std::endl << std::endl;

            std::cout << "Player: ";
            player.showHand();
            std::cout << "Your points: " << player.getPoints() << std::endl;

            if (player.crossedLimit()) {
                std::cout << "You've exceeded 21! Game lost... \n";
                break;
            }

            std::cout << "Do you want another card (y/n): ";
            if (chooseOne()) {
                player.addCard();
                continue;
            }
            break;
        }

        if (!player.crossedLimit()) {
            std::cout << "Your final score: " << player.getPoints() << std::endl;
            std::cout << "Dealer's turn...\n";

            while (true) {
                if (!dealer.crossedLimit() && !dealer.crossedLimit(BlackjackConst::dealerLimit)) {
                    dealer.addCard();
                    dealer.getPoints();
                }
                else {
                    break;
                }
            }

            if (dealer.crossedLimit()) {
                std::cout << "Dealer crossed 21! " << dealer.getPoints() << std::endl;
                std::cout << "You win!\n";
            }

            else if (dealer.higherThan(player)) {
                std::cout << "Dealer got " << dealer.getPoints() << std::endl;
                std::cout << "You lose...\n";
            }

            else {
                std::cout << "Dealer got only " << dealer.getPoints() << std::endl;
                std::cout << "You win!!!\n";
            }
        }

        std::cout << "Do you want to play again (y/n): ";
        if (!chooseOne()) {
            break;
        }
    } // New game loop

    return 0;
}

//while (!dealer.crossedLimit()) {
//    if (!dealer.higherThan(player)) {
//        dealer.addCard();
//        dealer.getPoints();
//        continue;
//    }
//    else {
//        std::cout << "Dealer got " << dealer.getPoints() << std::endl;
//        std::cout << "You lose...\n";
//        break;
//    }
//}
//if(dealer.crossedLimit()) {
//    std::cout << "Dealer crossed 21! " << dealer.getPoints() << std::endl;
//    std::cout << "You win!\n";
//}
//break;