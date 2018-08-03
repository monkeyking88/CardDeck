//
//  DeckGUI.cpp
//  CS247
//
//  Created by Mengqi Liu on 2013-07-16.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

const char * image_names[] = {
    // Set up CLUB
	"img/0_0.png", "img/0_1.png", "img/0_2.png", "img/0_3.png", "img/0_4.png", "img/0_5.png", "img/0_6.png", "img/0_7.png", "img/0_8.png", "img/0_9.png", "img/0_j.png", "img/0_q.png", "img/0_k.png",
    
	// Set up DIAMOND
	"img/1_0.png", "img/1_1.png", "img/1_2.png", "img/1_3.png", "img/1_4.png", "img/1_5.png", "img/1_6.png", "img/1_7.png", "img/1_8.png", "img/1_9.png", "img/1_j.png",  "img/1_q.png","img/1_k.png",
	
	// Set up HEART
	"img/2_0.png", "img/2_1.png", "img/2_2.png", "img/2_3.png", "img/2_4.png", "img/2_5.png", "img/2_6.png", "img/2_7.png", "img/2_8.png", "img/2_9.png", "img/2_j.png",  "img/2_q.png","img/2_k.png",
    
    // Set up SPADE
	"img/3_0.png", "img/3_1.png", "img/3_2.png", "img/3_3.png", "img/3_4.png", "img/3_5.png", "img/3_6.png", "img/3_7.png", "img/3_8.png", "img/3_9.png", "img/3_j.png",  "img/3_q.png","img/3_k.png",
    
	// Set up the back of a card for a place holder/null card
	"img/nothing.png"
};

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf

DeckGUI::DeckGUI()  {
		transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)],
              std::back_inserter(deck), &createPixbuf );
} // DeckGUI::DeckGUI

DeckGUI::~DeckGUI() {
} // DeckGUI::~DeckGUI

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage( Rank k, Suit s ) {
	int index = ((int) s)*13 + ((int) k );
	return deck[ index ];
} // DeckGUI::getCardImage

// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() {
	int size = deck.size();
	return deck[ size-1 ];
} // DeckGUI::getNullCardImage, last element stored is placeholder for nothing
