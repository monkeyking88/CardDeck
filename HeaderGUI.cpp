//
//  HearGUI.cpp
//  CS247
//
//  Created by Mengqi Liu on 2013-07-21.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "HeaderGUI.h"
#include <iostream>
#include <string>
#include "View.h"
#include <gtkmm.h>

using namespace std;
// to construct a header with two buttons
//statr button and end game button
HeaderGUI::HeaderGUI(View* v):v(v),start_button( "Start new game with seed:" ), end_button( "End current game" ),hbox(true, 10){
    
    add(hbox);
    
	hbox.add( start_button );
    hbox.add( end_button );
    
    start_button.signal_clicked().connect( sigc::mem_fun( *this, &HeaderGUI::newGameClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &HeaderGUI::endGameClicked ) );
}

string HeaderGUI::getEntryText() const{
       return this->name;
}

//once the start game button is clicked,
//the game will ask for a random seed number to shuffle cards
void HeaderGUI::popupDialog(){
    
Gtk::Dialog dialog( "Random Seed");

Gtk::Entry   nameField;
Gtk::Label   nameLabel( "Please enter a random number to shuffle:" );

Gtk::VBox* contentArea = dialog.get_vbox();
contentArea->pack_start( nameLabel, true, false );
contentArea->pack_start( nameField, true, false );

nameField.set_text( "" );
nameLabel.show();
nameField.show();

Gtk::Button * okButton = dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
Gtk::Button * cancelButton = dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

int result = dialog.run();

switch (result) {
    case Gtk::RESPONSE_OK:
    case Gtk::RESPONSE_ACCEPT:
        this->name = nameField.get_text();
        v->newGameClicked();
        break;
    case Gtk::RESPONSE_CANCEL:
        break;
           }
}

void HeaderGUI::newGameClicked(){
    this->popupDialog();
}

void HeaderGUI::endGameClicked(){
    v->gameEndBtnClicked();
}

//once game started, the start game button will be disabled
// if the game has started yet, the the end game button will be disabled
void HeaderGUI::changeButtonState(bool ongoing_state){
    start_button.set_sensitive(!ongoing_state);
    end_button.set_sensitive(ongoing_state);
}

HeaderGUI::~HeaderGUI(){}


