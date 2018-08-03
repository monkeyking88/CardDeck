//
//  PlayerMenu.h
//  CS247
//
//  Created by Mengqi Liu on 2013-07-19.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef PlayerMenu_H
#define PlayerMenu_H

#include <gtkmm.h>
#include "View.h"
#include "Player.h"

class  View;
class Player;


//to create a view for player to choose Human/computer Player and set rage quit
class PlayerBlock : public Gtk::Frame
{
public:
    PlayerBlock( View* , int );
	virtual ~PlayerBlock();
    
    //acessors and setters
    std::string getButtonText() const;
    void setPoint( int );
    void setDiscard( int );
    void restPlayer();
    int getPlayerIndex() const;
    void setPlayerLabel( std::string );
    void setSensetive( bool );
    //change according to view
    void updateData( std::vector<Player*> );
    void player_Change();
protected:
    Gtk::Button m_button;
    Gtk::Button button_rage;
    
private:
    View* v;    
	//Child widgets:
	Gtk::VBox                      m_Box;
    Gtk::Frame                     frame;            // Create a nice framed border for the box.
    Gtk::Label                     points;
    Gtk::Label                     discards;
    //private memeber data
    int point;
    int discard;
    int player_index;
};

#endif 
