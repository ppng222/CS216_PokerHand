/* File: deck.cpp
 * Course: CS216-006
 * Project: Lab 8 (as part of Project 2)
 * Purpose: the implementation of member functions for the Deck class.
 */
#include "deck.h"
#include "card.h"
// create a Deck of cards
void Deck::createDeck()
{
	deck.clear();
    for (int s= (int)Card::cSuits::Spade; s < (int)Card::cSuits::Spade+SUITS; s++)
    {    
        for (Card::cPoints val = CARD_START; val < CARD_START+POINTS; val++)
        {
            Card::cSuits suit = static_cast<Card::cSuits>(s);
            Card newcard(suit, val);
            deck.push_back(newcard);
        }
    }
}

void Deck::shuffleDeck()
// shuffle the deck of cards
{
	srand(time(0));
    Card temp;  // for swapping
    for (int i = deck.size()-1; i>= 1; i--)
    {
        int j = rand() % (i+1);
        temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

Card Deck::deal_a_card()
{
	Card dealtCard = deck.back();
    deck.pop_back();
    return dealtCard;
}