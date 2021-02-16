/* File: pokerhand.cpp
 * Course: CS216-006
 * Project: Project 2
 * Purpose: the implementation for the PokerHand class.
 */

#include "card.h"
#include "rank.h"
#include "pokerhand.h"
#include "SortedLinkedList.h"
#include <iostream>

using namespace std;

PokerHand::PokerHand()
{
    // make a new rank object to ensure the hand has NoRank
    Rank tmp(Rank::hRanks::NoRank,0);
    hand_rank = tmp;
}

// private functions
void PokerHand::sort()
{
    // using a bubble sort algorithm
    for (int i=0;i<HANDS-1;i++)
    {
        for (int j=i+1;j<HANDS;j++)
        {
            if (cards[i].compareTo(cards[j]) == -1)
            {
                Card tmp = cards[i];
                cards[i] = cards[j];
                cards[j] = tmp;
            }
        }
    }

}
bool PokerHand::isAllOneSuit() const
{
    // this checks whether all the cards have the same suit
    Card::cSuits card0 = cards[0].suit;
    Card::cSuits card1 = cards[1].suit;
    Card::cSuits card2 = cards[2].suit;
    Card::cSuits card3 = cards[3].suit;
    Card::cSuits card4 = cards[4].suit;
    bool allOneSuit = false;
    if ((card0 == card1) && (card1 == card2) && (card2 == card3) && (card3 == card4))
    {
        allOneSuit = true;
    }
    return allOneSuit;
}
bool PokerHand::isSequence() const
{
    // this checks whether all the cards are in a sequence
    // by seeing whether the next card matches the last+1
    Card::cPoints card0 = cards[0].point;
    Card::cPoints card1 = cards[1].point;
    Card::cPoints card2 = cards[2].point;
    Card::cPoints card3 = cards[3].point;
    Card::cPoints card4 = cards[4].point;
    bool isASequence = false;
    if ((card0 == card1+1) && (card1 == card2+1) && (card2 == card3+1) && (card3 == card4+1))
    {
        isASequence = true;
    }
    return isASequence;
}

// public functions

void PokerHand::setPokerHand(Card in_hand[], int size)
{
    // check whether the provided size is INVALID
    if (size != HANDS)
    {
        // the cards are invalid
        cout << "Invalid number of cards!";
    } else {
        for (int i=0;i<HANDS;i++){
            // the cards are valid, assign them
            cards[i] = in_hand[i];
        }
    }
    // sort the cards first
    sort();

    // determining rank, just run through all the ranks from low to high
    // this ensures the highest rank will be the most recent
    isHighCard();
    isPair();
    isThreeOfAKind();
    isStraight();
    isFlush();
    isFullHouse();
    isFourOfAKind();
    isStraightFlush();

}

int PokerHand::compareHand(const PokerHand &otherHand) const
{
    // compare the hand to another hand
    // grab both kinds
    int thisKindPoints = (int)hand_rank.kind;
    int otherKindPoints = (int)otherHand.getRank().kind;
    // grab both points
    int thisPoints = hand_rank.point;
    int otherPoints = otherHand.getRank().point;
    if (thisKindPoints < otherKindPoints)
    {
        // the current hand is lower ranked than the other
        return -1;
    }
    else if (thisKindPoints > otherKindPoints)
    {
        // the current hand is higher than the other
        return 1;
    }
    else if (thisKindPoints == otherKindPoints)
    {
        // the hands TIED, but now check whether the points are different
        if (thisPoints < otherPoints)
        {
            return -1;
        } 
        else if (thisPoints > otherPoints)
        {
            return 1;
        }
        else if (thisPoints == otherPoints)
        {
            return 0;
        }
    }
}

void PokerHand::print() const
{
    // print the cards in the hand as well as the rank
    for (int i=0;i<HANDS;i++)
    {
        cards[i].print();
        cout << '\t';
        //cout << endl; this line is strange, the examples show them on the same line
        // but we are told to print per line, bring up to prof/ta
    }
    cout << "\nThis hand's rank is: ";
    hand_rank.print();
}

Rank PokerHand::getRank() const
{
    // return the hands rank
    return this->hand_rank;
}

bool PokerHand::isStraightFlush()
{
    bool AllSameSuit = isAllOneSuit();
    bool isASequence = isSequence();
    bool Trueness = false;
    if (AllSameSuit == true && isASequence == true)
    {
        Card::cPoints highestPoint = cards[0].point;
        Trueness = true;
        Rank tmp(Rank::hRanks::StraightFlush,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}

bool PokerHand::isFourOfAKind()
{
    Card::cPoints card0Point = cards[0].point;
    Card::cPoints card1Point = cards[1].point;
    Card::cPoints card2Point = cards[2].point;
    Card::cPoints card3Point = cards[3].point;
    Card::cPoints card4Point = cards[4].point;
    bool Trueness = false;

    // check whether the first four cards match
    if (card0Point == card1Point && card1Point == card2Point && card2Point == card3Point) 
    {
        Card::cPoints highestPoint = cards[0].point;
        Trueness = true;
        Rank tmp(Rank::hRanks::FourOfAKind,highestPoint);
        hand_rank = tmp;
    }
    // check whether the last four cards match
    if (card1Point == card2Point && card2Point == card3Point && card3Point == card4Point) 
    {
        Card::cPoints highestPoint = cards[1].point;
        Trueness = true;
        Rank tmp(Rank::hRanks::FourOfAKind,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}

bool PokerHand::isFullHouse()
{
    Card::cPoints card0Point = cards[0].point;
    Card::cPoints card1Point = cards[1].point;
    Card::cPoints card2Point = cards[2].point;
    Card::cPoints card3Point = cards[3].point;
    Card::cPoints card4Point = cards[4].point;
    bool Trueness = false;
    // three of one and two of another
    // check to see if the first three cards are matching
    if ((card0Point == card1Point && card1Point == card2Point) && (card3Point == card4Point))
    {
        Card::cPoints highestPoint = cards[0].point;
        Trueness = true;
        Rank tmp(Rank::hRanks::FullHouse,highestPoint);
        hand_rank = tmp;
    } else if ((card0Point == card1Point) && (card2Point == card3Point && card3Point == card4Point)) {
        Card::cPoints highestPoint = cards[2].point;
        Trueness = true;
        Rank tmp(Rank::hRanks::FullHouse,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}

bool PokerHand::isFlush()
{
    Card::cPoints highestPoint = cards[0].point;
    bool AllSameSuit = isAllOneSuit();
    bool isASequence = isSequence();
    bool Trueness = false;
    if (AllSameSuit == true && isASequence == false)
    {
        Trueness = true;
        Rank tmp(Rank::hRanks::Flush,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}

bool PokerHand::isStraight()
{
    bool AllSameSuit = isAllOneSuit();
    bool isASequence = isSequence();
    bool Trueness = false;
    if (isASequence == true)
    {
        Trueness = true;
        Card::cPoints highestPoint = cards[0].point;
        Rank tmp(Rank::hRanks::Straight,highestPoint);
        hand_rank = tmp;
    }  
    return Trueness;
}

bool PokerHand::isThreeOfAKind()
{
    Card::cPoints highestPoint;
    Card::cPoints card0Point = cards[0].point;
    Card::cPoints card1Point = cards[1].point;
    Card::cPoints card2Point = cards[2].point;
    Card::cPoints card3Point = cards[3].point;
    Card::cPoints card4Point = cards[4].point;
    bool AllSameSuit = isAllOneSuit();
    bool Trueness = false;
    if (card0Point == card1Point && card1Point == card2Point) {
        highestPoint = cards[0].point;
        Trueness = true;
    }
    else if (card1Point == card2Point && card2Point == card3Point) {
        highestPoint = cards[1].point;
        Trueness = true;
    }
    else if (card2Point == card3Point && card3Point == card4Point) {
        highestPoint = cards[2].point;
        Trueness = true;
    }
    if (Trueness)
    {
        Rank tmp(Rank::hRanks::ThreeOfAKind,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}

bool PokerHand::isPair()
{
    Card::cPoints highestPoint = cards[0].point;
    bool AllSameSuit = isAllOneSuit();
    bool Trueness = false;
    Card::cPoints card0 = cards[0].point;
    Card::cPoints card1 = cards[1].point;
    Card::cPoints card2 = cards[2].point;
    Card::cPoints card3 = cards[3].point;
    Card::cPoints card4 = cards[4].point;
    if (card0 == card1)
    {
        Trueness = true;
        highestPoint = card0;
    } else if (card1 == card2)
    {
        Trueness = true;
        highestPoint = card1;
    } else if (card2 == card3)
    {
        Trueness = true;
        highestPoint = card2;
    } else if (card3 == card4)
    {
        Trueness = true;
        highestPoint = card3;
    }
    if (Trueness)
    {
        Rank tmp(Rank::hRanks::Pair,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}
bool PokerHand::isHighCard()
{
    bool AllSameSuit = isAllOneSuit();
    bool Trueness = false;
    Card::cPoints highestPoint = cards[0].point;
    Card::cPoints card0 = cards[0].point;
    Card::cPoints card1 = cards[1].point;
    Card::cPoints card2 = cards[2].point;
    Card::cPoints card3 = cards[3].point;
    Card::cPoints card4 = cards[4].point;
    if (((card0 != card1) && (card1 != card2) && (card2 != card3) && (card3 != card4)) && AllSameSuit == false)
    {
        Trueness = true;
        Rank tmp(Rank::hRanks::HighCard,highestPoint);
        hand_rank = tmp;
    }
    return Trueness;
}
