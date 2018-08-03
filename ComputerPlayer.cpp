//
//  ComputerPlayer.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "ComputerPlayer.h"
#include <iostream>
#include <vector>

using namespace std;

ComputerPlayer::ComputerPlayer(int player_index) : Player(player_index){}

ComputerPlayer::ComputerPlayer(Player& human_player):Player(human_player){}

Command ComputerPlayer::getAction(const Table& table) const{
    Command ret;
        
    //find legalplays by union of available cards and hand cards
    vector<Card> legalPlay = getLegalPlay(table);
    //if there are legal plays, play the first legal play
    if(legalPlay.size() != 0){
        ret.type = PLAY;
        ret.card = legalPlay.front();
    }else{
        //if there are no legal plays, discard the first hand card
        ret.type = DISCARD;
        ret.card = handCards.front();
    }
    return ret;
}

bool ComputerPlayer::shouldAutoAct() const{
    return true;
}