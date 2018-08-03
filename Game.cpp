//
//  Game.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>
#include <stdlib.h>
#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

Game::Game(std::vector<bool> humanList){
    //initialize 4 players, whose types are determined by human list
    for (int i = 0; i < PLAYER_COUNT; i++){
        Player* player;
        if (humanList[i]){
            player = new HumanPlayer(i);
        }
        else {
            player = new ComputerPlayer(i);
        }
        players.push_back(player);
    }
    //initialize 52 cards
    for (int i = 0; i < CARD_COUNT; i++) {
        Card* card = new Card(static_cast<Suit>(floor(i/(CARD_COUNT/PLAYER_COUNT))), static_cast<Rank>(i%(CARD_COUNT/PLAYER_COUNT)));
        cards_[i] = card;
    }
    //shuffle the cards
    
    table = NULL;
    activePlayerIndex = 0;
    stepCount = 0;
    roundStepCount = 0;
}
Game::~Game(){
    //destroy all the players
    for (int i = 0; i < PLAYER_COUNT; i++){
        delete players.at(i);
    }
    //destroy all the cards
    for (int i = 0; i < CARD_COUNT; i++){
        delete cards_[i];
    }
    delete table;
}


void Game::newRound(){
    //shuffule the 52 cards
    shuffle();
    
    //determine which player gets the 7S and should therefore start first
    int startIndex = -1;
    for (int i = 0; i < CARD_COUNT && startIndex < 0; i++){
        if (cards_[i] -> getRank() == SEVEN && cards_[i] -> getSuit() == SPADE){
            startIndex = floor(i/13);
        }
    }
    std::cout << "A new round begins. It's player " << startIndex + 1 << "'s turn to play." << std::endl;
    
    //initiaze a new table for the current round
    //table holds the original 52 cards and the cards players have played
    int cardsPerPlayer = CARD_COUNT/PLAYER_COUNT;
    std::vector<Card> temp;
    for (int i = 0; i < CARD_COUNT; i++){
        temp.push_back(*cards_[i]);
    }
    table = new Table(temp);

    
    //give out the cards to the players
    for (int i = 0; i < PLAYER_COUNT; i++){
        std::vector<Card> newCards;
        for (int j = 0; j < cardsPerPlayer; j++){
            newCards.push_back(*cards_[i * cardsPerPlayer + j]);
        }
        players[i] -> resetCards(newCards);
    }
    
    activePlayerIndex = startIndex;
    stepCount = 0;
    roundStepCount = 0;
}
    

void Game::act(Command cmd){
    if (isEndOfRound()){
        return;
    }
    if (cmd.type == RAGEQUIT){
        rageQuit(activePlayerIndex);
        cmd = players[activePlayerIndex] -> getAction(*table);
    }
    
    players[activePlayerIndex] -> act(cmd, *table);
    
    activePlayerIndex = activePlayerIndex+1 == PLAYER_COUNT ? 0 : activePlayerIndex+1;
    stepCount++;
    if (stepCount == PLAYER_COUNT){
        stepCount = 0;
        roundStepCount++;
    }

}

std::vector<Card> Game::getActiveLegalPlay() const{
    return players[activePlayerIndex] -> getLegalPlay(*table);
}

bool Game::shouldAutoAct() const{
    return players[activePlayerIndex] -> shouldAutoAct();
}

Command Game::getAction() const{
    return players[activePlayerIndex] -> getAction(*table);
}
    
    
//find all the indexes of winner players
std::vector<Player*> Game::findWinner() const{
    for (int i = 0; i < PLAYER_COUNT; i++){
        players[i] -> concludeRound();
    }
    //at the start, assume player 0 is the winner
    int score = players[0] -> getScore();
    
    std::vector<Player*> winners;
    winners.push_back(players[0]);
    bool nextRound = true;
    
    for (int i = 0; i < PLAYER_COUNT; i++){
        //if players with same winning score, add its index
        if (players[i] -> getScore() == score && i != 0){
            winners.push_back(players[i]);
        }
        //if found players with lower scores, clear the previous indexes, record the current one
        if (players[i] -> getScore() < score){
            score = players[i] -> getScore();
            winners.clear();
            winners.push_back(players[i]);
        }
        //if any player has a score >= 80, do not proceed to the next round
        if (players[i] -> getScore() >= SCORE_MAX){
            nextRound = false;
        }
    }
    //if should proceed to the next round, then there are no winners, clear the winner indexes
    if (nextRound == true){
        winners.clear();
    }
    return winners;
}

bool Game::isEndOfRound() const{
    return roundStepCount >= ROUNDSTEP_END;
}

//the given function for shuffling cards
void Game::shuffle(){
	int n = CARD_COUNT;
    
	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

//if a player rage quits, replace it with a computer player
void Game::rageQuit(int ragePlayerIndex){
    std::cout << "Player " << ragePlayerIndex+1 << " ragequits. A computer will now take over." << std::endl;
    Player* replacePlayer = new ComputerPlayer(*players[ragePlayerIndex]);
    delete players[ragePlayerIndex];
    players[ragePlayerIndex] = replacePlayer;
}


std::vector< std::vector<Card> > Game::getPlayedCards() const{
    return table -> getTableCards();
}

Player* Game::getPlayerByIndex(int index) const{
    return players[index];
}


std::vector<Player*> Game::getPlayers() const{
    return players;
}

int Game::getActivePlayerIndex() const{
    return activePlayerIndex;
}