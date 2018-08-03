//
//  View.cpp
//  CS247
//
//  Created by Mengqi Liu on 2013-07-18.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "View.h"
#include "CardsPlayer.h"
#include "CardsTable.h"
#include "PlayerBlock.h"
#include "HeaderGUI.h"
#include "Card.h"
#include "HeaderGUI.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

View::View(Controller *c, Facade *m) : facade_(m), controller_(c){
    
    set_title( "Straights UI" );
	set_border_width( 10 );
    
    //start to pack all subviews together
    add(table_straights);
    header = new HeaderGUI(this);

    table_straights.pack_start(*Gtk::manage(header),Gtk::PACK_SHRINK, 0);
    cardstable = new CardsTable(this);
    table_straights.pack_start(*Gtk::manage(cardstable),Gtk::PACK_SHRINK, 0);
    
    player1 = new PlayerBlock(this,1);
    player2 = new PlayerBlock(this,2);
    player3 = new PlayerBlock(this,3);
    player4 = new PlayerBlock(this,4);
    
    block_row.pack_start(*Gtk::manage(player1),true,true, 0);
    block_row.pack_start(*Gtk::manage(player2),true,true, 0);
    block_row.pack_start(*Gtk::manage(player3),true,true, 0);
    block_row.pack_start(*Gtk::manage(player4),true,true, 0);
    playercards = new CardsPlayer(this);
    
    table_straights.pack_start(block_row,Gtk::PACK_SHRINK, 0);
    
    table_straights.pack_start(*Gtk::manage(playercards),Gtk::PACK_SHRINK, 0);
	
    show_all_children();
	// Register view as observer of facade
    facade_->subscribe(this);
    
    update();
}

View::~View() {}

void View::update(){
    //cout << "update called" << endl;
    
    vector< vector<Card> > tableCards = facade_ -> getPlayedCards();
    vector< Card> handCards = facade_ -> getActivePlayerHandCards();
    cardstable->displayCards(tableCards[0], tableCards[1], tableCards[2], tableCards[3]);
    playercards->displayCards(handCards);
    
    //cout << "still no exception" << endl;
    
   if (facade_ -> isGameOnGoing()){
        
        if (facade_ -> isEndOfRound()){
            vector<Player*> winners = facade_ -> getWinners();
            if (winners.size() > 0){
                cout << "***************************************" << endl;
                cout << "winners are: " << endl;
                for (int i = 0; i < winners.size(); i++){
                    cout << winners[i] -> getPlayerIndex()+1 << endl;
                }
                //
                updatePlayerBlock(facade_->getPlayers());
                showWinnersDialogue(winners);
            }
            else{
                //tell user if there are no winners and tell them their scores
                //note passed here is const vector<Player*>
                updatePlayerBlock(facade_->getPlayers());
                showStartNewRoundDialogue(facade_ -> getPlayers());
            }
        }
        else if ( facade_ -> isRoundJustStarted()){
            int activePlayer_index = facade_-> getActivePlayerIndex();
            //eg: It's Player X's term to play, remember to +1
            showFirstPlayerDialogue(activePlayer_index);
        }
       if (facade_ -> isGameOnGoing()){
           updatePlayerBlock(facade_->getPlayers());
       }
    }else{
        resetPlayerBlock();
    }
    header -> changeButtonState(facade_ -> isGameOnGoing());
    //cout << "updated" << endl;
}

void View::gameStartBtnClicked(int seed, std::vector<bool> humanList){
    cout << "Some one clicked game start button" << endl;
    controller_ -> gameStartBtnClicked(seed, humanList);
}

void View::gameEndBtnClicked(){
    cout << "Some one clicked game end button" << endl;
    controller_ -> gameEndBtnClicked();
}
 
void View::handCardBtnClicked(int handCardIndex){
    controller_ -> handCardBtnClicked(handCardIndex, this);
}

void View::rageBtnClicked(){
    controller_ -> rageBtnClicked();
}
 
void View::dialogue_startNewRoundBtnClicked(){
    controller_ -> dialogue_startNewRoundBtnClicked();
}
 
void View::dialogue_winnerBtnClicked(){
    controller_ -> dialogue_winnerBtnClicked();
}


void View::newGameClicked(){
    int seed_int;

    string seed_text = header->getEntryText();
    
    if( seed_text == ""){
        seed_int = 0;
    }else{
    
    istringstream ss(seed_text);
    ss >> seed_int;
    }
    player_mode.resize(4);
    
    player_mode[0] = player1->getButtonText();
    player_mode[1] = player2->getButtonText();
    player_mode[2] = player3->getButtonText();
    player_mode[3] = player4->getButtonText();
    
    vector<bool> humanList;
    humanList.resize(4);
    int index = 0;
    while (index < 4) {
        if(player_mode[index] == "Human"){
            humanList[index] = true;
        }else{
            humanList[index] = false;
        }
        index ++;
    }
    controller_->gameStartBtnClicked(seed_int, humanList);
}

void View::endGameClicked(){
    controller_->gameEndBtnClicked();
}

void View::updatePlayerBlock(vector<Player*> players){
     if (facade_ -> isGameOnGoing()){
         int player_ongoing = facade_->getActivePlayerIndex();
         player1->setPlayerLabel("Rage");
         player1->setSensetive(false);
         player2->setPlayerLabel("Rage");
         player2->setSensetive(false);
         player3->setPlayerLabel("Rage");
         player3->setSensetive(false);
         player4->setPlayerLabel("Rage");
         player4->setSensetive(false);

         for(int i =0; i<players.size() ; i++){
             if( i == player_ongoing && players[i]->shouldAutoAct() != true){
                 if(i == 0){
                     player1->setSensetive(true);
                 }else if (i == 1){
                     player2->setSensetive(true);
                 }else if( i == 2){
                     player3->setSensetive(true);
                 }else if( i == 3){
                     player4->setSensetive(true);
                 }
             }
         }
            player1->setPoint(players[0]->getScore());
         vector<Card> getDiscardedCards1 = players[0]->getDiscardedCards();
         cout << getDiscardedCards1.size() << endl;
         player1->setDiscard(getDiscardedCards1.size());
            player2->setPoint(players[1]->getScore());
         vector<Card> getDiscardedCards2 = players[1]->getDiscardedCards();
         cout << getDiscardedCards2.size() << endl;
         player2->setDiscard(getDiscardedCards2.size());
            player3->setPoint(players[2]->getScore());
         vector<Card> getDiscardedCards3 = players[2]->getDiscardedCards();
         cout << getDiscardedCards3.size() << endl;
         player3->setDiscard(getDiscardedCards3.size());
            player4->setPoint(players[3]->getScore());
         vector<Card> getDiscardedCards4 = players[3]->getDiscardedCards();
         cout << getDiscardedCards4.size() << endl;
         player4->setDiscard(getDiscardedCards4.size());
     }
}
void View::resetPlayerBlock(){
    
    player1->setPlayerLabel("Human");
    player1->setPoint(0);
    player1->setDiscard(0);
    player1->setSensetive(true);
    player2->setPlayerLabel("Human");
    player2->setPoint(0);
    player2->setDiscard(0);
    player2->setSensetive(true);
    player3->setPlayerLabel("Human");
    player3->setPoint(0);
    player3->setDiscard(0);
    player3->setSensetive(true);
    player4->setPlayerLabel("Human");
    player4->setPoint(0);
    player4->setDiscard(0);
    player4->setSensetive(true);
}

void View::warnNotLegal(int cardIndex, Card card, std::vector<Card> legalPlay, std::vector<Card> handCards){

    string suits[SUIT_COUNT] = {"Clubs:", "Diamonds:", "Hearts:", "Spades:"};
    string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "10", "J", "Q", "K"};
    
    string titleText = "Warning: illegal move, you have chosen to play:";
    Gtk::Dialog dialog_illegal( "Illegal Play");
    Gtk::VBox* contentArea = dialog_illegal.get_vbox();
    
    Gtk::Label  titleLabel( titleText);
    contentArea->pack_start( titleLabel, true, false );
    titleLabel.show();
    
    Gtk::Label  cardLabel( "Card No." + toStr(cardIndex+1) + ", Card:" + ranks[card.getRank()] + suits[card.getSuit()]);
    contentArea->pack_start( cardLabel, true, false );
    cardLabel.show();
    
    Gtk::Label  legalLabel( "Legal plays are: " );
    contentArea->pack_start( legalLabel, true, false );
    legalLabel.show();
    
    Gtk::Label *childrenLabels[legalPlay.size()];
    for (int i = 0; i < legalPlay.size(); i++){
        childrenLabels[i] = new Gtk::Label(ranks[legalPlay[i].getRank()] + suits[legalPlay[i].getSuit()]);
        
        contentArea->pack_start( *childrenLabels[i], true, false );
    }
    for (int i = 0; i < legalPlay.size(); i++){
        childrenLabels[i] -> show();
    }
    
    Gtk::Button * okButton = dialog_illegal.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    int result = dialog_illegal.run();
    
    for (int i = 0; i < legalPlay.size(); i++){
        delete childrenLabels[i];
    }

}

void View::showFirstPlayerDialogue(int activePlayer_index){

    string text = "Round" + toStr(facade_ -> getRoundCount()) + " starting, it's player" + toStr(activePlayer_index+1) + "'s turn to play";
    Gtk::Dialog dialog_firstPlayer( "New Round!");
    Gtk::Label  nameLabel( text );
    Gtk::VBox* contentArea = dialog_firstPlayer.get_vbox();
    contentArea->pack_start( nameLabel, true, false );
    nameLabel.show();
    Gtk::Button * okButton = dialog_firstPlayer.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    
    int result = dialog_firstPlayer.run();

    
}
void View::showStartNewRoundDialogue(std::vector<Player*> players){
    string titleText = "Round" + toStr(facade_ -> getRoundCount()) + " finishied, scores are:";
    Gtk::Dialog dialog_newRound( "Round Finish!");
    Gtk::VBox* contentArea = dialog_newRound.get_vbox();
    
    Gtk::Label  titleLabel( titleText);
    contentArea->pack_start( titleLabel, true, false );
    titleLabel.show();
    
    Gtk::Label *childrenLabels[players.size()];
    for (int i = 0; i < players.size(); i++){
        childrenLabels[i] = new Gtk::Label("player" + toStr((i+1)) + ": " + toStr(players[i] -> getScore()));
        
        contentArea->pack_start( *childrenLabels[i], true, false );
        //childrenLabels.push_back(nameLabel);
    }
    for (int i = 0; i < players.size(); i++){
        childrenLabels[i]->show();
    }
    
    Gtk::Button * okButton = dialog_newRound.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    int result = dialog_newRound.run();

    controller_ -> dialogue_startNewRoundBtnClicked();
    for (int i = 0; i < players.size(); i++){
        delete childrenLabels[i];
    }
}
    
void View::showWinnersDialogue(std::vector<Player*> winners){
    string titleText = "Round" + toStr(facade_ -> getRoundCount()) + " finishied, scores are:";
    Gtk::Dialog dialog_winners( "Round Finish!");
    Gtk::VBox* contentArea = dialog_winners.get_vbox();
    
    Gtk::Label  titleLabel( titleText);
    contentArea->pack_start( titleLabel, true, false );
    titleLabel.show();
    
    std::vector<Player*> players = facade_ -> getPlayers();
    
    Gtk::Label *childrenLabels[winners.size() + players.size()];
    int counter = 0;
    for (int i = 0; i < players.size(); i++){
        childrenLabels[counter] = new Gtk::Label("player" + toStr((i+1)) + ": " + toStr(players[i] -> getScore()));
        
        contentArea->pack_start( *childrenLabels[counter], true, false );
        //childrenLabels.push_back(nameLabel);
        counter++;
    }
    
    string winnerTitle = winners.size() > 1 ? "Winners are" : "Winner is";
    Gtk::Label  winnerLabel( winnerTitle );
    contentArea->pack_start( winnerLabel, true, false );
    winnerLabel.show();
    for (int i = 0; i < winners.size(); i++){
        childrenLabels[counter] = new Gtk::Label( "player" + toStr((winners[i]->getPlayerIndex() +1)) + " with socre " + toStr(winners[i] -> getScore()));
        
        contentArea->pack_start( *childrenLabels[counter], true, false );
        counter++;
    }
    
    for (int i = 0; i < winners.size() + players.size(); i++){
        childrenLabels[i]->show();
    }
    
    
    Gtk::Button * okButton = dialog_winners.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    int result = dialog_winners.run();
    controller_ -> dialogue_winnerBtnClicked();
    cout << "winner dialogue btn clicked" << endl;
    for (int i = 0; i < winners.size() + players.size(); i++){
        delete childrenLabels[i];
    }
}

string View::toStr(int str){
    stringstream ss2;
    ss2 << str;
    return ss2.str();
}
