//
//  13CardsGUI.h
//  CS247
//
//  Created by Mengqi Liu on 2013-07-18.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef CardsTable_H
#define CardsTable_H

#include "DeckGUI.h"
#include "Card.h"       //need to use vector of card to create the image of 13 cards for both table and onhands
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>

using std::vector;

class View;

class CardsTable : public Gtk::Frame{
public:
    CardsTable( View* );
    void setNullAll();
    void displayCards( vector<Card>, vector<Card>, vector<Card>, vector<Card>);
    virtual ~CardsTable();
    
private:
    //in order to access null buffer and image card buffer which are defined in DeckGUI class
    DeckGUI         deck;
    View            * v;
    
    //images for cards,four types in total
    Gtk::Image      *card_spades[13];
    Gtk::Image      *card_heart[13];
    Gtk::Image      *card_diamond[13];
    Gtk::Image      *card_clube[13];
    //four horizontal boxes for each type
    Gtk::HBox       hbox_spades;
    Gtk::HBox       hbox_heart;
    Gtk::HBox       hbox_diamond;
    Gtk::HBox       hbox_clube;
    //one vertical box and frame to hold all cards on table
    Gtk::VBox       vbox;
    Gtk::Frame      frame;            // Create a nice framed border for the box.
};
#endif 