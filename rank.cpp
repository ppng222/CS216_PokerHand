/* File: rank.cpp
 * Course: CS216-006
 * Project: Lab 9 (as part of Project 2)
 * Purpose: the implementation of member functions for the Rank class.
 * Name: Phong Nguyen
 */
#include <iostream>
#include <iomanip>
#include "rank.h"

using namespace std;

// Default constructor.
Rank::Rank()
{
	kind = hRanks::NoRank;
	point = 0;
}

// Alternate constructor.
// Create a Rank object with specified ranking name and points.
Rank::Rank(hRanks r, rPoints p)
{
	int rankValue = int(r);
	switch(rankValue) {
		// this checks whether the provided rank is valid or not
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			// there is a valid case and thus it should be assigned
			// the point value should be assumed to be valid as well
			kind = r;
			point = p;
			break;
		default:
			// no matched case was found, the card is invalid, set to defaults
			kind = hRanks::NoRank;
			point = 0;
			break;
	}
	
}

// access the hand ranking kind
Rank::hRanks Rank::getKind() const
{
	return this->kind;
}

// access the card point value of the corresponding ranking kind
Rank::rPoints Rank::getPoint() const
{
	return this->point;
}

// Display a description of the hand-ranking category to standard output.
// The output should look like:
//   FourOfAKind( 4)
//   FullHouse(10)
//   Flush( A)
//   ...
void Rank::print() const
{
	int RankIndex = int(kind); // convert the enum to the an integer so we can access the
							   // rank array later
	// convert the point amount so we can display certain points as a letter
	string PointString;
	if (this->point <= 10) {
		PointString = to_string(this->point);
	} else if (this->point == 11) {
		PointString = "J";
	} else if (this->point == 12) {
		PointString = "Q";
	} else if (this->point == 13) {
		PointString = "K";
	} else if (this->point == 14) {
		PointString = "A";
	}
	cout << RANK_NAMES[RankIndex] << "(" << setw(2) << PointString << ")\n"; // print the Rank Type
}

