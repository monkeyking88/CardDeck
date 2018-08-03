//
//  CardsPlayer.h
//  CS247
//
//  Created by Mengqi Liu on 2013-07-18.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef CardsPlayer_H
#define CardsPlayer_H

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include "Card.h"
#include "DeckGUI.h"
#include "View.h"

class View;

using std::vector;

class CardsPlayer: public Gtk::Frame{
public:
    CardsPlayer(View*);
    void setNUllPic();
    void displayCards(vector<Card>);
	virtual ~CardsPlayer();
//button click on handcard event handlers
//each button need one unique handler to tell corresponding card index
    void  handCardIndex0();
    void  handCardIndex1();
    void  handCardIndex2();
    void  handCardIndex3();
    void  handCardIndex4();
    void  handCardIndex5();
    void  handCardIndex6();
    void  handCardIndex7();
    void  handCardIndex8();
    void  handCardIndex9();
    void  handCardIndex10();
    void  handCardIndex11();
    void  handCardIndex12();
    
    int getCardIndex() const;
private:
	DeckGUI                         deck;
    View*                           v;
    
    int button_index;
	
    // Member widgets:
	Gtk::Image                    * card[13];          // Images to display.
	Gtk::Button                   button[13];           // Button that will hold an image.
	Gtk::HBox                       hbox;             // Horizontal box for aligning widgets in the window.
	Gtk::Frame                      frame;            // Create a nice framed border for the box.
};

#endif 