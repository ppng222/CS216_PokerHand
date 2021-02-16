/* File: card.cpp
 * Course: CS216-006
 * Project: Lab 8 (as part of Project 2)
 * Purpose: the implementation of member functions for the Card class.
 */
#include "card.h"
#include <iomanip>

// Default constructor marks card as invalid
Card::Card() {
	suit = cSuits::Invalid;
	point = 0;
}

// Alternate constructor
Card::Card(cSuits s, cPoints p) 
{
	suit = s;
	point = p;
}

// access the card point value
Card::cPoints Card::getPoint() const
{
	return this->point;
}

// access the card suit value
Card::cSuits Card::getSuit() const
{
	return this->suit;
}

// compare with another Card object passed in as parameter: other
// if the object your are working on has higher point than other, return 1;
// if the object your are working on has lower point than other, return -1;
// otherwise, return 0
int Card::compareTo(Card other) const
{
	if (this->point < other.point)
        return -1;
    if (this->point > other.point)
        return 1;
    return 0;
}

// Display a description of the Card object to standard output
// The output should look like:
//   the sign of suit, followed by the point, then followed by the sign of suit again   
void Card::print() const
{
	int suitValue = int(this->suit);
	string pointChar;
	switch (this->point)
	{
		// this switch case handle 
		case 1:
			pointChar = "1";
			break;
		case 2:
			pointChar = "2";
			break;
		case 3:
			pointChar = "3";
			break;
		case 4:
			pointChar = "4";
			break;
		case 5:
			pointChar = "5";
			break;
		case 6:
			pointChar = "6";
			break;
		case 7:
			pointChar = "7";
			break;
		case 8:
			pointChar = "8";
			break;
		case 9:
			pointChar = "9";
			break;
		case 10:
			pointChar = "10";
			break;
		case 11:
			pointChar = "J";
			break;
		case 12:
			pointChar = "Q";
			break;
		case 13:
			pointChar = "K";
			break;
		case 14:
			pointChar = "A";
			break;
	}
	switch(suitValue)
	{
		case 1:
			cout << SPADE << setw(2) << pointChar << SPADE;
			break;
		case 2:
			cout << CLUB << setw(2) << pointChar << CLUB;
			break;
		case 3:
			cout << HEART << setw(2) << pointChar << HEART;
			break;
		case 4:
			cout << DIAMOND << setw(2) << pointChar << DIAMOND;
			break;
	}
}
