/* File: Project2.cpp
 * Course: CS216-006
 * Project: Project 2
 * Purpose: A simplified texas hold em game
 * Author: Phong Nguyen
 */

#include <iostream>
#include <vector>
#include <string>
#include "deck.h"
#include "card.h"
#include "rank.h"
#include "pokerhand.h"

using namespace std;

const int PLAYER_HANDS = 2;
const int TABLE_CARDS = 5;
const int HANDS = 5;
const int TOTALCARDS = 7;


// decide the best five cards out of seven cards
// best means the highest ranking of five-card poker hand defined in the poker game
// pass in a vector of seven cards 
// (const call by reference: safe for the arugment and no copy is made for efficiency)
// return the best PokerHand object which represents the best five-card poker hand
PokerHand best_FIVE_out_of_SEVEN(const vector<Card>& cards); 
// this function will print the players card onto the screen
void PrintPlayerCards(const vector<Card>& cards);
void PrintTableCards(const vector<Card>& cards);
	

int main()
{
	string userOption = "0";
	while (userOption != "Q" && userOption != "q")
	{
		// create the card deck
		Deck playDeck;
		playDeck.createDeck();
		playDeck.shuffleDeck();

		// create the two players
		vector<Card> Player1_Cards, Player2_Cards;

		// deal two cards to each player
		Player1_Cards.push_back(playDeck.deal_a_card());
		Player1_Cards.push_back(playDeck.deal_a_card());
		Player2_Cards.push_back(playDeck.deal_a_card());
		Player2_Cards.push_back(playDeck.deal_a_card());

		// create the table card holder
		vector<Card> TableCards;

		// deal 5 cards to the table
		for (int i=0; i < TABLE_CARDS; i++)
		{
			TableCards.push_back(playDeck.deal_a_card());
		}
		// display player 1's cards

		cout << "The cards in your hand are:\n";
		PrintPlayerCards(Player1_Cards);
		cout << "The FIVE cards on the deck to share are:\n";

		// display the table's cards
		PrintTableCards(TableCards);

		// display player 2's cards
		cout << "The cards in computer's hand are:\n";
		PrintPlayerCards(Player2_Cards);
		cout << endl;


		// create the full hand for each player
		for (int i=0; i < TABLE_CARDS; i++)
		{
			Player1_Cards.push_back(TableCards[i]);
			Player2_Cards.push_back(TableCards[i]);
		}

		// find the best hand out of all the cards
		PokerHand Player1_Hand, Player2_Hand;
		cout << "Player 1: You\n";
		Player1_Hand = best_FIVE_out_of_SEVEN(Player1_Cards);
		cout << "Player 2: Computer\n";
		Player2_Hand = best_FIVE_out_of_SEVEN(Player2_Cards);

		// check which player wins
		if (Player1_Hand.compareHand(Player2_Hand) < 0)
		{
			cout << "Sorry, the computer wins the game!\n\n";
		} else if (Player1_Hand.compareHand(Player2_Hand) == 0)
		{
			cout << "It is a tie game!\n\n";
		} else if (Player1_Hand.compareHand(Player2_Hand) > 0)
		{
			cout << "Congratulations, you win the game!\n\n";
		}
		// ask the user if they want to play again
		cout << "Do you want to play poker game again (Press \"q\" or \"Q\" to quit the program): ";
		getline(cin,userOption);
	}
	return 0;
}

void PrintPlayerCards(const vector<Card>& cards)
{
	// this function prints out the first two cards in a players hand
	cout << "    ";
	cards[0].print();
	cout << "\n        ";
	cards[1].print();
	cout << "\n";
}

void PrintTableCards(const vector<Card>& cards)
{
	// this function prints out the five cards provided
	cout << "    *************************\n";
	for (int i=0;i<cards.size();i++)
	{
		cout << "    *   ";
		cards[i].print();
		cout << "                *\n";
	}
	cout << "    *************************\n";
}

// this code was copied out of testPA2.cpp and slightly modified to fit the purpose of this project
PokerHand best_FIVE_out_of_SEVEN(const vector<Card>& cards)
{    

    PokerHand bestH;
    PokerHand cardsH;

    // check if the parameter is valid
    if (cards.size() != TOTALCARDS)
    {
        cout << "Invalid Cards, we need SEVEN cards!" << endl;
        return cardsH; // return a PokerHand object by default constructor
    }

    // Consider all possible ways of dropping two cards
    // from all seven cards 
    // i is the index of the first card dropped
    // and j is the index of the second card dropped.
    // There are 21 different ways to pick 5 cards out of 7
    for (int i=0; i < TOTALCARDS; i++) 
    {
        for (int j=i+1; j < TOTALCARDS; j++) 
        {
            Card pick[HANDS];
            int index = 0;

            // Iterate over all seven cards and assign them to the pick[] array
            // exclude cards with index numbers of #i and #j.
            for (int k=0 ; k < TOTALCARDS ; k++) 
            {
                if (k == i || k == j) 
                    continue;
                pick[index] = cards[k];
                index++;
            }
            
            // create a PokerHand with pick[]
            cardsH.setPokerHand(pick, HANDS);
            // Check to see if current pick is better than
            // the best you have seen so far
            if (bestH.compareHand(cardsH) < 0)
            {
                bestH = cardsH ;
            }
        }
    }

    // Now bestH holds the best poker hand among all 21 poker hands
    cout << "*** Best five-card hand ***" << endl;
    bestH.print();
    cout << endl << endl;
    return bestH;
}