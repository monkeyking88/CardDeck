//
//  Popups.h
//  CS247
//
//  Created by Mengqi Liu on 2013-07-21.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef Popups_H
#define Popups_H
#include <gtkmm.h>
#include "Player.h"

class Player;

class Popups:Public Gtk::Dialog{
public:
    Popups(vector<Player*>);
    void ShowWinner();

    Popups(vector<Player*>,std::string);
}

#endif /* defined(__CS247__Popups__) */
