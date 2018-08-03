//
//  Player.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;


//initialize players with specified index
Player::Player(int player_index){
    this->playerIndex = player_index;
    this->score = 0;
}

//copy constructor,for ragequit
Player:: Player( const Player& human_player){
    this->playerIndex = human_player.getPlayerIndex();
    this->score = human_player.getScore();
   
    this->handCards = human_player.handCards;
    this->discardedCards = human_player.discardedCards;
}

Player::~Player(){
    this->score = 0;
    
    this->handCards.clear();
    this->discardedCards.clear();
}

//reset all the cards that user have at the start of a new round
void Player::resetCards(const std::vector<Card>& new_cards){
    this->handCards.clear();
    this->discardedCards.clear();
    
    this->handCards = new_cards;
}

//perform a command action, either discard or play
void Player::act(Command command, Table& table){
    if(command.type == DISCARD){
        discardCard(command.card);
    }
    if(command.type == PLAY){
        playCard(command.card,table);
    }
    cout << "playerer acted, updatedtable: " << endl;
    table.printTable();
}

//return the index of the player
int Player::getPlayerIndex()const{
    return this->playerIndex;
    
}

//return the score of the player
int Player::getScore() const{
    return this->score;
}

int Player::getUpdatedScore() const{
    int score_thisround = 0;
    
    for( int i = 0; i <discardedCards.size() ; ++i){
        score_thisround += discardedCards[i].getRank() +1;
    }
    
    return this->score + score_thisround;
}

//at the end of each round, display all the cards that the player has discarded and update the score
void Player::concludeRound(){
    //print out discarded cards
    cout<< "Player "<< this->playerIndex+1<< "'s discards:";
    int score_thisround = 0;
    
    for( int i = 0; i <discardedCards.size() ; ++i){
        score_thisround += discardedCards[i].getRank() +1;
        cout << " " << discardedCards[i];
    }
    
    //print out change of scores
    int new_score = this->score + score_thisround;
    cout << endl << "Player "<<this->playerIndex+1<<"'s score: " << this->score << " + "<< score_thisround <<" = " << new_score << endl;
    
    //update player score
    this->score = new_score;
}


/**************helper private functions***************/
//play a card by removing it from hand cards and add it to the table
void Player::playCard(Card card, Table& table){
    table.addCard(card);
    removeFromHandcards(card);
    cout << "Player " << playerIndex + 1 << " plays " << card << "." << endl;
}

//discard a card by removing it from hand cards and add it to the discard cards
void Player::discardCard(Card card){
    bool inhand = false;

    for(int m = 0; m < handCards.size() ; ++m){
        if(handCards[m] == card){
            inhand = true;
        }
    }
    //only record discarded cards that were in hand
    if (inhand){
        discardedCards.push_back(card);
    }
    removeFromHandcards(card);
    cout << "Player " << playerIndex + 1 << " discards " << card << "." << endl;
}

//remove a handcard
void Player::removeFromHandcards(Card card){
    for(int m = 0; m < handCards.size() ; ++m){
        if(handCards[m] == card){
            handCards.erase(handCards.begin()+m);
        }
    }
}

//find legalplays by union of available cards and hand cards
std::vector<Card> Player::getLegalPlay(const Table& table) const{
    vector<Card> availbleCards = table.getAvailableCards();
    vector<Card> legalPlay;
    for(int j = 0; j < handCards.size(); ++j){
        for( int k =0; k < availbleCards.size(); ++k){
            if( handCards[j] == availbleCards[k]){
                legalPlay.push_back(availbleCards[k]);
            }
        }
    }
    
    return legalPlay;
}

std::vector<Card> Player::getHandCards() const{
    return handCards;
}
std::vector<Card> Player::getDiscardedCards() const{
    return discardedCards;
}