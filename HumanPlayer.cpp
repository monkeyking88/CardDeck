//
//  HumanPlayer.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "HumanPlayer.h"
#include <vector>
#include <iostream>
using namespace std;

//call the parent play constructor to initialze the human player
HumanPlayer::HumanPlayer(int player_index) : Player(player_index){}

//get the human player's desired action
Command HumanPlayer::getAction(const Table& table) const{
    Command ret;
    
    //display table condition
    table.printTable();
    
    //display hand cards
    cout<< "Your hand:";
    for(int i = 0; i < handCards.size(); ++i){
        cout << " " << handCards[i];
    }
    cout << endl;
    //print legal plays
    cout <<"Legal Plays:";
    vector<Card> availbleCards = table.getAvailableCards();
    vector<Card> legalPlay = getLegalPlay(table);
    
    for (int i = 0; i < legalPlay.size(); i++){
        cout << " " << legalPlay[i];
    }
    cout << endl << ">";
    
    //read the command until a valid command that is not DECK is inputed
    bool keepReading = true;
    while(keepReading){
        keepReading = false;
        cin >> ret;
        //if user command is DECK, print out deck and listen for another command
        if(ret.type == DECK){
            table.printCards();
            cout << ">";
            keepReading = true;
        }
        //if user command is DISCARD, alert and keep reading if there are legal plays
        if(ret.type == DISCARD){
            if(legalPlay.size() != 0){
                cout << "You have a legal play. You may not discard."<< endl << ">";
                keepReading = true;
            }
        }
        //if user command is PLAY, alert and keep reading if the card is not a legal play
        //since the given straights program only checks for available cards but not cards in hand, we decided to give up the redundancy and follow the given sample
        if(ret.type == PLAY){
            int z = 0;
            for(z = 0; z < availbleCards.size(); ++z){
                if(availbleCards[z] == ret.card)
                    break;
                
            }
            // if z reaches the very end, then it indicates that the card is not found in the legal plays
            if( z == availbleCards.size()){
                cout << "This is not a legal play."<< endl << ">";
                keepReading = true;
            }
            
        }
    }
    return ret;
}

bool HumanPlayer::shouldAutoAct() const{
    return false;
}
