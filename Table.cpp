//
//  Table.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//
#include <iostream>
#include <string>
#include "Table.h"

using namespace std;

Table::Table(const std::vector<Card> &cards){
    //records the sequence of cards, these are the cards will each player will have to put on the table
    this -> cards = cards;
    
    //initialize the 2-dimansional vector with each suit
    for (int i = 0; i < SUIT_COUNT; i++){
        std::vector<Card> suitCard;
        playedCards.push_back(suitCard);
    }
}

Table::~Table(){
    cards.clear();
    playedCards.clear();
}

//if player plays a card, that card is passed here to add to the table
void Table::addCard(Card newCard){
    //insert the new card to its corresponding suit
    int offset = 0;
    while (offset < playedCards.at(newCard.getSuit()).size() && playedCards.at(newCard.getSuit()).at(offset).getRank() < newCard.getRank()) {
        offset++;
    } 
    playedCards.at(newCard.getSuit()).insert(playedCards.at(newCard.getSuit()).begin() + offset, newCard);
}

//if play calls "DECK" command, players calls table to print out the original 52 cards that were on the table
void Table::printCards() const{
    for (int i = 0; i < cards.size(); i++){
        cout << cards[i];
        if ((i+1) % 13 == 0){
            cout << endl;
        }
        else{
            cout << " ";
        }
    }
}

//before a human player acts, this is called to print all the cards on the table so that player knows what cards have been played
void Table::printTable() const{
    string suits[SUIT_COUNT] = {"Clubs:", "Diamonds:", "Hearts:", "Spades:"};
    string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    cout << "################################################" << endl;
    cout << "##------------------------------------------------" << endl;
    cout << "##Cards on the table:" << endl;
    for (int i = 0; i < SUIT_COUNT; i++){
        cout << "##" << suits[i];
        for (int j = 0; j < playedCards.at(i).size(); j++) {
            cout << " " << ranks[playedCards.at(i).at(j).getRank()];
        }
        cout << endl;
    }
    cout << "##------------------------------------------------" << endl;
    cout << "################################################" << endl;

}

//determine and returns all the cards that can be possibly played from the current table condition
std::vector<Card> Table::getAvailableCards() const{
    vector<Card> availableCards;
    bool firstStep = true;
    for (int i = 0; i < SUIT_COUNT; i++){
        //if a new suit a empty, then 7 of that new suit is available
        if (playedCards.at(i).size() == 0){
            Card newCard(static_cast<Suit>(i), SEVEN);
            availableCards.push_back(newCard);
        }
        else{
            firstStep = false;
            //if the first card is not ACE, then a card before SEVEN is available
            if (playedCards.at(i).at(0).getRank() != ACE){
                Card newCard(playedCards.at(i).at(0).getSuit(), static_cast<Rank>(playedCards.at(i).at(0).getRank() - 1));
                availableCards.push_back(newCard);
            }
            //if the last card is not KING, then a card after SEVEN is available
            long endIndex = playedCards.at(i).size()-1;
            if (playedCards.at(i).at(endIndex).getRank() != KING){
                Card newCard(playedCards.at(i).at(endIndex).getSuit(), static_cast<Rank>(playedCards.at(i).at(endIndex).getRank() + 1));
                availableCards.push_back(newCard);
            }
        }
    }
    //if all suits are empty, then the only possible card is 7S
    if(firstStep){
        availableCards.clear();
        Card newCard(SPADE, SEVEN);
        availableCards.push_back(newCard);
    }
    
    return availableCards;
}


std::vector< std::vector<Card> > Table::getTableCards() const{
    return this->playedCards;
}
