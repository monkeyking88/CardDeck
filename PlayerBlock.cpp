

#include "PlayerBlock.h"

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <sstream>
#include "View.h"

using namespace std;

PlayerBlock::PlayerBlock(View* v,int player_index):m_button("Human"),v(v),player_index(player_index) {
    
    //set player blcok frame to show player index for diffrent block
    add(frame);
    stringstream ss;
    ss << player_index;
    
    string frame_str = " Player " + ss.str();
    frame.set_label(frame_str );
	frame.set_label_align( Gtk::ALIGN_TOP );
	frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	
    frame.add(m_Box);
    
    m_Box.pack_start(m_button);

    m_button.signal_clicked().connect( sigc::mem_fun( *this, &PlayerBlock::player_Change));
   
    //set lable to show points for each player
    stringstream ss1;
    ss1 << this->point;
    
    string point_str = "Points: " + ss1.str();
    
    points.set_text( point_str);
    
    //set labels to show discard # of cards for each player
    stringstream ss2;
    ss2 << this->discard;
    
    string discard_str = "Discards: " + ss2.str();
    discards.set_text(discard_str);
    
    m_Box.pack_start(points);
    m_Box.pack_start(discards);
    
}

void PlayerBlock::setPlayerLabel(string state){
    (this->m_button).set_label(state);
}

void PlayerBlock::setSensetive(bool set){
    (this->m_button).set_sensitive(set);
}

string PlayerBlock::getButtonText() const{
    return (this->m_button).get_label();
}

void PlayerBlock::setPoint(int point){
    stringstream ss1;
    ss1 << point;
    string point_str = "Points: " + ss1.str();
    points.set_text( point_str);
}
void PlayerBlock::setDiscard(int discard){
    stringstream ss2;
    ss2 <<discard;
    string discard_str = "Discards: " + ss2.str();
    discards.set_text(discard_str);
}
PlayerBlock::~PlayerBlock() {}

//change button for setting a player to be a human player or computer player before the game start
//or change the button to be "Rage" when game is ongoing 
void PlayerBlock::player_Change() {
    if(m_button.get_label() == "Computer"){
        m_button.set_label( "Human" );
    }
    else if(m_button.get_label() == "Human"){
        m_button.set_label( "Computer" );
    }
    else if(m_button.get_label() == "Rage"){
        m_button.set_label( "Raged" );
        v -> rageBtnClicked();
    }
}

int PlayerBlock::getPlayerIndex() const{
    return this->player_index;
}



