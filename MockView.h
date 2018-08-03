//
//  MockView.h
//  CS247
//
//  Created by Matthew Yang on 2013-07-20.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef MockView_H
#define MockView_H

#include "Game.h"
#include "Model.h"
#include "Game.h"
#include "Observer.h"
#include "Controller.h"
#include "Facade.h"
#include <iostream>

class Controller;

//the mock ui used to test the game logic without the user interface
class MockView: public Observer{
    
public:
    MockView(Controller* c , Facade* m){
        this -> c = c;
        this -> m = m;
        
        this -> m -> subscribe(this);
        std::cout << "MockView::contructor:: calling update" << std::endl;
        update();
    };
    virtual void update ();
    
    //mock user interactions with the view
    void gameStartBtnClicked(int seed, std::vector<bool> humanList);
    void gameEndBtnClicked();
    
    void handCardBtnClicked(int handCardIndex);
    void rageBtnClicked();
    
    void dialogue_startNewRoundBtnClicked();
    void dialogue_winnerBtnClicked();
    void warnNotLegal(int, Card&, vector<Card>, vector<Card>);
    
private:
    Controller* c;
    Facade* m;
    
};


#endif
