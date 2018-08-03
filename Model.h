//
//  Model.h
//  CS247
//
//  Created by Matthew Yang on 2013-07-18.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef Model_H
#define Model_H

#include "Subject.h"
#include "Game.h"
#include <stdlib.h>

using namespace std;

//the model of the MVC pattern, it holds the states of games and provides interfaces for Contoller calls and accessors for view updates
class Model : public Subject {
public:
    Model();
    void newGame(int seed, vector<bool> humanList);
    void newRound();
    void endGame();
    void act(Command cmd);
    
    //constant accesses to allow view to learn about the game state and game date inside update
    vector< vector<Card> > getPlayedCards() const;
    int getActivePlayerIndex() const;
    bool isGameOnGoing() const;
    bool isRoundJustStarted() const;
    vector<Card> getActivePlayerHandCards() const;
    vector<Card> getActivePlayerLegalPlay() const;
    
    //helper methods, real functionalities captured by getPlayers
    vector<Card> getActivePlayerDiscardedCards() const;
    int getActivePlayerScore() const;
    
    vector<Player*> getWinners() const;
    bool isEndOfRound() const;
    Player* getPlayerByIndex(int) const;
    vector<Player*> getPlayers() const;
    int getRoundCount() const;
    
private:
    static const int PLAYER_COUNT = 4;  //number of players
    //the game itself
    Game* game;
    //state of the game: is a game currently taking place
    bool onGoing;
    //state of the game: did the game just started a new round
    bool roundJustStared;
    //state of the game: tracks how many rounds have been played
    int roundCount;
};


#endif
