//
//  Player.h
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//
#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

#ifndef Player_H
#define Player_H

//base class for all the 
class Player{
public:
    Player(int);
    Player( const Player& );    //copy constructor used to copy human player to computer player
    virtual ~Player();
    
    void resetCards(const std::vector<Card>&);
    
    virtual Command getAction(const Table&) const = 0;  //pure virtual function waiting for children classes to override
    virtual bool shouldAutoAct() const = 0;
    void act(Command, Table&);
    
    int getPlayerIndex() const;
    int getScore() const;
    int getUpdatedScore() const;
    void concludeRound();
    
    std::vector<Card> getLegalPlay(const Table&) const;
    std::vector<Card> getHandCards() const;
    std::vector<Card> getDiscardedCards() const;
    
protected:
    int playerIndex;    //index of the player, starting from 0
    int score;          //score of the player
    std::vector<Card> handCards;    //hand cards the player has
    std::vector<Card> discardedCards;   //legal discards

//private helper functions
private:
    void playCard(Card,Table&);
    void discardCard(Card);
    void removeFromHandcards(Card);
    
};

#endif
