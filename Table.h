//
//  Table.h
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//
#ifndef Table_H
#define Table_H

#include <vector>
#include "Card.h"

class Table{

public:
    Table(const std::vector<Card>&);    //take the origianl cards, create new table
    ~Table();
    void addCard(Card);     //add a card to played cards
    void printCards() const;    //print out origianl cards
    void printTable() const;    //print out table conditions
    std::vector<Card> getAvailableCards() const;    //determine possible cards that can be played
    
    std::vector< std::vector<Card> > getTableCards() const;

private:
    std::vector<Card> cards;    //record of original cards
    std::vector< std::vector<Card> > playedCards;   //record of played cards
    
};

#endif
