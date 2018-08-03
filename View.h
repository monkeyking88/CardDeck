//
//  View.h
//  CS247
//
//  Created by Matthew Yang on 2013-07-16.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef View_H
#define View_H


#include <gtkmm.h>
#include "Observer.h"
#include "DeckGUI.h"
#include "Facade.h"
#include "Controller.h"
#include "Card.h"
#include "PlayerBlock.h"
#include "CardsPlayer.h"

class Controller;
class Facade;
class PlayerBlock;
class HeaderGUI;
class CardsPlayer;
class CardsTable;

class View : public Gtk::Window, public Observer {
public:
    View( Controller*, Facade* );
	virtual ~View();
	virtual void update();	// Observer Pattern: concrete update() method
    
    // Signal handlers:
    void gameStartBtnClicked(int seed, std::vector<bool> humanList);
	void gameEndBtnClicked();
    void handCardBtnClicked(int);
    void rageBtnClicked();
    void dialogue_startNewRoundBtnClicked();
    void dialogue_winnerBtnClicked();
    void updatePlayerBlock(vector<Player*> players);
    void resetPlayerBlock();
    
    void newGameClicked();
    void endGameClicked();
    
    void warnNotLegal(int, Card, std::vector<Card>, std::vector<Card>);

    void showFirstPlayerDialogue(int activePlayer_index);
    void showStartNewRoundDialogue(std::vector<Player*>);
    void showWinnersDialogue(std::vector<Player*>);
    

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Facade *facade_;
	
	// Strategy Pattern member (plus signal handlers)
	Controller *controller_;
    
    Gtk::VBox table_straights;
    Gtk::HBox block_row;
    
	// Card Images
	DeckGUI deck;
       
    PlayerBlock *player1;
    PlayerBlock *player2;
    PlayerBlock *player3;
    PlayerBlock *player4;
    CardsPlayer *playercards;
    CardsTable* cardstable;
    
    HeaderGUI* header;
    
    std::vector<string> player_mode;
    
    static string toStr(int str);

}; 


#endif
