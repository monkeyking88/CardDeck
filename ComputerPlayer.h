//
//  ComputerPlayer.h
//  CS247
//
//  Created by Matthew Yang on 2013-06-22.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "Player.h"

#ifndef ComputerPlayer_H
#define ComputerPlayer_H

class ComputerPlayer : public Player{
    
public:
    ComputerPlayer(int player_index);
    ComputerPlayer(Player& player);     //copy constructor use to copy a human player
    virtual Command getAction(const Table&) const;  //implement parent getAction
    virtual bool shouldAutoAct() const;
};


#endif
