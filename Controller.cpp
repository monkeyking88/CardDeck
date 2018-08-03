//
//  Controller.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-07-19.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "Controller.h"
#include "Model.h"
#include <iostream>

//controller implementations, calls the model to update its game state
Controller::Controller(Facade *m) : model(m) {}

void Controller::gameStartBtnClicked(int seed, std::vector<bool> humanList){
    model -> newGame(seed, humanList);
}

void Controller::gameEndBtnClicked(){
    std::cout << "Controller::calling endGame()" << std::endl;
    model -> endGame();
}

void Controller::handCardBtnClicked(int handCardIndex, View* v){
    //try the player's action, if the play is not legal, an exception will be thrown, and user will be warned
    try {
        model -> play(handCardIndex);
    } catch (std::string* e) {
        v -> warnNotLegal(handCardIndex, model -> getActivePlayerHandCards()[handCardIndex], model -> getActivePlayerLegalPlay(), model -> getActivePlayerHandCards());
    }
}

void Controller::rageBtnClicked(){
    model -> rage();
}

void Controller::dialogue_startNewRoundBtnClicked(){
    model -> newRound();
}

void Controller::dialogue_winnerBtnClicked(){
    model -> endGame();
}



//for user-interaction-free automatic testing with mock view
void Controller::handCardBtnClicked(int handCardIndex, MockView* v){
    try {
        model -> play(handCardIndex);
    } catch (std::string* e) {
        v -> warnNotLegal(handCardIndex, model -> getActivePlayerHandCards()[handCardIndex], model -> getActivePlayerLegalPlay(), model -> getActivePlayerHandCards());
    }
}