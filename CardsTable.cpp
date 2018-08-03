#include "CardsTable.h"
#include <cstdlib>

using namespace std;

//set the horizontal box to have homogenous spacing = 10px
CardsTable::CardsTable(View* v) : hbox_spades(true, 10 ), hbox_diamond(true, 10 ),hbox_clube(true, 10 ), hbox_heart(true, 10 ),vbox(true , 10),v(v){
    
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	
	
	// Sets the border width of the window.
	set_border_width( 10 );
    
    // Set the look of the frame.
	frame.set_label( "Cards on the table:" );
	frame.set_label_align( Gtk::ALIGN_TOP );
	frame.set_shadow_type( Gtk::SHADOW_NONE );
    
    // Add the frame to the window. Windows can only hold one widget, same for frames.
	add( frame );
    // four vertical boxes for each of card style
    frame.add( vbox);
    vbox.add( hbox_spades );
    vbox.add( hbox_clube );
    vbox.add( hbox_heart );
    vbox.add( hbox_diamond );
	
	// Initialize 13 empty cards and place them in the box.
    
    int i = 0;
	for (; i < 13; i++ ) {
		card_spades[i] = new Gtk::Image( nullCardPixbuf );
		hbox_spades.add( *card_spades[i] );
	}
    
    for (i = 0; i < 13; i++ ) {
		card_heart[i] = new Gtk::Image( nullCardPixbuf );
		hbox_heart.add( *card_heart[i] );
	}
    
    for (i = 0; i < 13; i++ ) {
		card_diamond[i] = new Gtk::Image( nullCardPixbuf );
		hbox_diamond.add( *card_diamond[i] );
	}
    
    
    for (i = 0; i < 13; i++ ) {
		card_clube[i] = new Gtk::Image( nullCardPixbuf );
		hbox_clube.add( *card_clube[i] );
	}
}

void CardsTable::setNullAll(){
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();

    int i = 0;
	
	for (i = 0; i < 13; i++ ) {
		card_spades[i]->set( nullCardPixbuf );
	}
    
    for (i = 0; i < 13; i++ ) {
		card_heart[i]->set( nullCardPixbuf );
	}
    
    for (i = 0; i < 13; i++ ) {
		card_diamond[i]->set( nullCardPixbuf );
	}
    
    for (i = 0; i < 13; i++ ) {
		card_clube[i]->set( nullCardPixbuf );
	}
}

void CardsTable::displayCards(vector<Card> clubs, vector<Card> diamonds, vector<Card> heart, vector<Card> spades){
    const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
    //first set all cards to have nothing background
    //the only update the view for those postions that a card image is needed
    setNullAll();
    
    int m;
    int rank;
    for( m = 0; m < spades.size();m++){
        rank = spades[m].getRank();
        card_spades[rank]->set(deck.getCardImage(static_cast<Rank>(rank) , SPADE ));
    }

    for( m = 0; m < heart.size();m++){
        rank = heart[m].getRank();
        card_heart[rank]->set(deck.getCardImage(static_cast<Rank>(rank) , HEART ));
    }

    
    for( m = 0; m < diamonds.size();m++){
        rank = diamonds[m].getRank();
        card_diamond[rank]->set(deck.getCardImage(static_cast<Rank>(rank) , DIAMOND ));
    }


    for( m = 0; m < clubs.size();m++){
        rank = clubs[m].getRank();
        card_clube[rank]->set(deck.getCardImage(static_cast<Rank>(rank) , CLUB ));
    }

}

CardsTable::~CardsTable(){
	//for (int i = 0; i < 12; i++ ) delete card[i];
}
