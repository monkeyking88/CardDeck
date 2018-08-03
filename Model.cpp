//
//  Model.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-07-18.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "Model.h"
#include <iostream>

Model::Model(){
    game = NULL;
    onGoing = false;
    roundJustStared = false;
    roundCount = 0;
    
    std::cout << "Model::onGoing::" << onGoing  << std::endl;
}

//initialize a new game, initialize the random sequence, and automatically start a new game round
void Model::newGame(int seed, vector<bool> humanList){
    std::cout << "Model::new game starting" << std::endl;
    
    //if the game is going on, do nothing
    if ( onGoing ){
        return;
    }
    
    srand48(seed);
    if (humanList.size() != PLAYER_COUNT){
        cout << "Model::newGame:: throwing exception" << endl;
        throw "Model::newGame:: humanList invalid size";
    }
    this -> game = new Game(humanList);
    onGoing = true;
    
    newRound();
}

//start a new round of a game, give player cards
void Model::newRound(){
    std::cout << "Model::new round starting" << std::endl;
    if (!onGoing){
        return;
    }
    game -> newRound();
    roundJustStared = true;
    roundCount++;
    notify();
    if (!isEndOfRound() && game -> shouldAutoAct()){
        act(game -> getAction());
    }
}

//used to end a game instaneously
void Model::endGame(){
    std::cout << "Model::ending game with onGoing:" << onGoing  << " and round count: " << roundCount <<  std::endl;
    if (onGoing){
        std::cout << "game onGoing, deleting game" << std::endl;
        delete game;
        game = NULL;
        onGoing = false;
        roundCount = 0;
    }
    notify();
}

//make a play in a game to act
void Model::act(Command cmd){
    //if a game is not taking place, just do nothing
    if (!onGoing){
        return;
    }
    std::cout << "Model::act player: " << getActivePlayerIndex()+1 << " acting with command: " << cmd.type << cmd.card << std::endl;
    //if the round has not ended, act accordingly
    if (!isEndOfRound()){
        game -> act(cmd);
        roundJustStared = false;
    }
    else{
        cout << "Model::act:: throwing exception" << endl;
        throw "Model::act player action detected after roundStep max reached";
    }
    //tell the view to update after a player has perfomed action
    notify();
    //check if the next player should automatically play (a computer player)
    //because of the event loop, anything called after notify must be tripally checked
    if (onGoing && !isEndOfRound() && game -> shouldAutoAct()){
        act(game -> getAction());
    }
}

//return all the played cards on the table in the current round
std::vector< std::vector<Card> > Model::getPlayedCards() const{
    std::vector< std::vector<Card> > empty;
    for (int i = 0; i < SUIT_COUNT; i++){
        std::vector<Card> suitCard;
        empty.push_back(suitCard);
    }
    return onGoing ? game -> getPlayedCards(): empty;
}

//return the index of the play who is currenly playing
int Model::getActivePlayerIndex() const{
    return onGoing ? game -> getActivePlayerIndex(): throw "no Game yet";
}

bool Model::isGameOnGoing() const{
    return onGoing;
}

bool Model::isRoundJustStarted() const{
    return roundJustStared;
}

//get the hand cards of the play who is currently playing
std::vector<Card> Model::getActivePlayerHandCards() const{
    if (onGoing){
        Player* player = getPlayerByIndex(getActivePlayerIndex());
        return player -> getHandCards();
    }
    std::vector<Card> cards;
    return cards;
}

//get the discarded cards of the player who is currently playing
std::vector<Card> Model::getActivePlayerDiscardedCards() const{
    if (onGoing){
        Player* player = getPlayerByIndex(getActivePlayerIndex());
        return player -> getDiscardedCards();
    }
    std::vector<Card> cards;
    return cards;
}

//used to determine whether a discard or a play is intended
std::vector<Card> Model::getActivePlayerLegalPlay() const{
    if (onGoing){
        return game -> getActiveLegalPlay();
    }
    std::vector<Card> cards;
    return cards;
}

//get the up-to-time socre of the play who is currently playing
int Model::getActivePlayerScore() const{
    Player* player = getPlayerByIndex(getActivePlayerIndex());
    return onGoing ? player -> getUpdatedScore(): throw "no Game yet";
}

//must be called upon end of round to conclude that round
std::vector<Player*> Model::getWinners() const{
    return onGoing ? game -> findWinner(): throw "no Game yet";
}

//must be checked inside update() so that is there is a endOfRound, a dialogues notifies users about the round summary
bool Model::isEndOfRound() const{
    return onGoing ? game -> isEndOfRound(): throw "no Game yet";
}

//gets a player by its index
Player* Model::getPlayerByIndex(int index) const{
    if (index < 0 || index >= PLAYER_COUNT){
        throw "Model::getPlayerByIndex:: player index out of bounds";
    }
    return onGoing ? game -> getPlayerByIndex(index): throw "no Game yet";
}

//return all the players in the current game
std::vector<Player*> Model::getPlayers() const{
    cout << "Model called getPlayers with onGoing: " << onGoing << " and roundCount" << roundCount << endl;
    return onGoing ? game -> getPlayers() : throw "no Game yet";
}

int Model::getRoundCount() const{
    return roundCount;
}
