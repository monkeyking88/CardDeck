//
//  CardsPlayer.cpp
//  CS247
//
//  Created by Mengqi Liu on 2013-07-18.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "CardsPlayer.h"
#include <vector>
#include "Card.h"
#include "View.h"

using namespace std;

CardsPlayer::CardsPlayer(View* v) : hbox( true, 10 ), v(v){
    
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	
	set_border_width( 10 );
    
	frame.set_label( " Your Cards:" );
	frame.set_label_align( Gtk::ALIGN_TOP );
	frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	
	add( frame );
	
	frame.add( hbox );
	
	// Initialize 13 empty cards with buttons and place them in the box.
	for (int i = 0; i < 13; i++ ) {
		card[i] = new Gtk::Image( nullCardPixbuf );
		hbox.add( *card[i] );
        button[i].set_image( *card[i] );
        hbox.add( button[i] );
	}
    
    //add different event handler to different button
    //one the specific button is clicked, the event function call will be fired
    button[0].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex0 ) );
    button[1].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex1 ) );
    button[2].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex2 ) );
    button[3].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex3 ) );
    button[4].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex4 ) );
    button[5].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex5 ) );
    button[6].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex6 ) );
    button[7].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex7 ) );
    button[8].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex8 ) );
    button[9].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex9 ) );
    button[10].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex10 ) );
    button[11].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex11 ) );
    button[12].signal_clicked().connect( sigc::mem_fun( *this, &CardsPlayer::handCardIndex12 ) );
}//end of CardsPlayer constructor


void CardsPlayer::setNUllPic(){
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
    for (int i = 0; i < 13; i++ ) {
		card[i]->set( nullCardPixbuf );
    }
}

void CardsPlayer::displayCards(vector<Card> onhand){
    setNUllPic();
    for (int i = 0; i<onhand.size(); ++i){
        Rank rank= onhand[i].getRank();
        Suit suit = onhand[i].getSuit();
        cout<<suit << " "<< rank <<endl;
        card[i]->set(deck.getCardImage(rank,suit));
    }
}

//whold banch of event handler, basically just return the index of card to view and Game
//for futhure logic and view update
void CardsPlayer::handCardIndex0(){
    this->button_index = 0;
    v->handCardBtnClicked(this->button_index);
}
void CardsPlayer::handCardIndex1(){
    this->button_index = 1;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex2(){
    this->button_index = 2;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex3(){
    this->button_index = 3;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex4(){
    this->button_index = 4;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex5(){
    this->button_index = 5;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex6(){
    this->button_index = 6;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex7(){
    this->button_index = 7;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex8(){
    this->button_index = 8;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex9(){
    this->button_index = 9;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex10(){
    this->button_index = 10;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex11(){
    this->button_index = 11;
    v->handCardBtnClicked(this->button_index);
}

void CardsPlayer::handCardIndex12(){
    this->button_index = 12;
    v->handCardBtnClicked(this->button_index);
}

int CardsPlayer::getCardIndex() const{
    return button_index;
}


CardsPlayer::~CardsPlayer(){
	for (int i = 0; i < 13; i++ ){
        delete card[i];
    }
}

