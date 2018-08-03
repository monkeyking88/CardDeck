//
//  MockView.cpp
//  CS247
//
//  Created by Mengqi Liu on 2013-07-21.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include "MockView.h"


//implementations of the mock view interactions, used for testing of the logical parts
void MockView::update(){
    cout << "update called" << endl;
    
    vector< vector<Card> > tableCards;
    vector< Card> handCards;
    //updateTableCards(tableCards);
    //updateHandCards(handCards);
    
    
    if (m -> isGameOnGoing()){
        if (m -> isEndOfRound()){
            vector<Player*> winners = m -> getWinners();
            if (winners.size() > 0){
                cout << "***************************************" << endl;
                cout << "winners are: " << endl;
                for (int i = 0; i < winners.size(); i++){
                    cout << winners[i] -> getPlayerIndex()+1 << endl;
                }
                //
                //showWinnersDialogue(winners);
            }
            else{
                //tell user if there are no winners and tell them their scores
                //note passed here is const vector<Player*>
                //showStartNewRoundDialogue(m -> getPlayers());
            }
        }
        else if ( m -> isRoundJustStarted()){
            int activePlayer_index = m -> getActivePlayerIndex();
            //eg: It's Player X's term to play, remember to +1
            //showFirstPlayerDialogue(activePlayer_index);
        }
        //note passed here is const vector<Player*>
        //updatePlayerMenu(m -> getPlayers());
    }else{
        //resetPlayerMenu();
        //disableEndGameBtn();
    }
    
}

void MockView::gameStartBtnClicked(int seed, std::vector<bool> humanList){
    cout << "Some one clicked game start button" << endl;
    c -> gameStartBtnClicked(seed, humanList);
}
void MockView::gameEndBtnClicked(){
    cout << "Some one clicked game end button" << endl;
    c -> gameEndBtnClicked();
}

void MockView::handCardBtnClicked(int handCardIndex){
    cout << "Player: " << m -> getActivePlayerIndex()+1 << "hand card button with index: " << handCardIndex << " is end: " << ! (m -> isGameOnGoing() ) << endl;
    c -> handCardBtnClicked(handCardIndex, this);
}
void MockView::rageBtnClicked(){
    cout << "Player: " << m -> getActivePlayerIndex()+1 << "rage quit button" << endl;
    c -> rageBtnClicked();
}

void MockView::dialogue_startNewRoundBtnClicked(){
    c -> dialogue_startNewRoundBtnClicked();
}

void MockView::dialogue_winnerBtnClicked(){
    c -> dialogue_winnerBtnClicked();
}

void MockView::warnNotLegal(int index, Card& card, vector<Card> cards, vector<Card> handCards){
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "!!warining illegal::, you have legal cards, but your play is illegal" << endl;
    cout << "!!selected index: " << index << endl;
    cout << "!!selected card: " << card << endl;
    cout << "!!legal plays are: " << endl << "!!";
    for (int i = 0; i < cards.size(); i++){
        cout << cards[i] << " ";
    }
    cout << endl;
    cout << "!!hand cards are: " << endl << "!!";
    for (int i = 0; i < handCards.size(); i++){
        cout << "index: " << i << " " <<  handCards[i] << " | ";
    }
    cout << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}
