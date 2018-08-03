//
//  Facade.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-07-20.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "Facade.h"


Facade::Facade(Model* model){
    this -> model = model;
}

void Facade::newGame(int seed, vector<bool> humanList){
    model -> newGame(seed, humanList);
}
void Facade::newRound(){
    model -> newRound();
}

void Facade::endGame(){
    model -> endGame();
}

//provide a simpler play interface for the controller by leveraging Model's action method
void Facade::play(int handCardIndex){
    if (model -> isGameOnGoing()){
        if (model -> isEndOfRound()){
            return;
        }
        vector<Card> handCards = model -> getActivePlayerHandCards();
        
        //make sure the user clicks on a valid card, otherwise do nothing
        if (handCardIndex < handCards.size()){
            vector<Card> legalPlay = model -> getActivePlayerLegalPlay();
            Command cmd;
            cmd.type = legalPlay.size() == 0 ? DISCARD : PLAY;
            if (cmd.type == DISCARD){
                cmd.card = handCards[handCardIndex];
                model -> act(cmd);
            }
            else{
                bool legal = false;
                for (int i = 0; i < legalPlay.size() && !legal; i++){
                    if (handCards[handCardIndex] == legalPlay[i]){
                        legal = true;
                    }
                }
                if (legal){
                    cmd.card = handCards[handCardIndex];
                    model -> act(cmd);
                }
                else{
                    //if the play is illegal, throw a exception to controller which will in turns call view to warn user
                    cout << "throwing expection" << endl;
                    throw new std::string("invalid move");
                }
            }
        }
    }
}

//provide a simpler rage quit interface for the controller by leveraging Model's action method
void Facade::rage(){
    if (model -> isGameOnGoing()){
        if (model -> isEndOfRound()){
            return;
        }
        Command cmd;
        cmd.type = RAGEQUIT;
        cmd.card = Card(DIAMOND, ACE);
        model -> act(cmd);
    }
}

vector< vector<Card> > Facade::getPlayedCards() const{
    return model -> getPlayedCards();
}

int Facade::getActivePlayerIndex() const{
    return model -> getActivePlayerIndex();
}

bool Facade::isGameOnGoing() const{
    return model -> isGameOnGoing();
}

bool Facade::isRoundJustStarted() const{
    return model -> isRoundJustStarted();
}

vector<Card> Facade::getActivePlayerHandCards() const{
    return model -> getActivePlayerHandCards();
}

vector<Card> Facade::getActivePlayerLegalPlay() const{
    return model -> getActivePlayerLegalPlay();
}

//helper methods, real functionalities captured by getPlayers
vector<Card> Facade::getActivePlayerDiscardedCards() const{
    return model -> getActivePlayerDiscardedCards();
}

int Facade::getActivePlayerScore() const{
    return model -> getActivePlayerScore();
}

vector<Player*> Facade::getWinners() const{
    return model -> getWinners();
}
bool Facade::isEndOfRound() const{
    return model -> isEndOfRound();
}
Player* Facade::getPlayerByIndex(int index) const{
    return model -> getPlayerByIndex(index);
}
vector<Player*> Facade::getPlayers() const{
    return model -> getPlayers();
}

int Facade::getRoundCount() const{
    return model -> getRoundCount();
}

void Facade::subscribe( Observer* o){
    model -> subscribe(o);
}
void Facade::unsubscribe( Observer* o){
    model -> unsubscribe(o);
}