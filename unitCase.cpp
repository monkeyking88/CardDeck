//
//  unitTest.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-07-20.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Game.h"
#include "Model.h"
#include "Observer.h"
#include "Controller.h"
#include "Model.h"
#include <assert.h>
#include <vector>
#include "Card.h"
#include "MockView.h"


using namespace std;

//the main test file that runs automatic tests with different seeds and player arrangements to brute test the logical components
int main(int argc, char * argv[]){
 
    
    Model model;                          // Create model
    Facade facade(&model);
    Controller controller( &facade );  // Create controller
	MockView view( &controller, &facade );
    
    bool p1 = false;
    bool p2 = false;
    bool p3 = false;
    bool p4 = false;
    bool toggle = false;
    
    for (int seed = 0; seed < 1000000; seed++){
        for (int a = 0; a < 2; a++){
            p1 = !p1;
            for (int b = 0; b < 2; b++){
                p2 = !p2;
                for (int c = 0; c < 2; c++){
                    p3 = !p3;
                    for (int d = 0; d < 2; d++){
                        p4 = !p4;
                        for (int e = 0; e < 2; e++){
                            toggle = !toggle;
                            vector<bool> humanList;
                            humanList.push_back(p1);
                            humanList.push_back(p2);
                            humanList.push_back(p3);
                            humanList.push_back(p4);
                            
                            view.gameEndBtnClicked();
                            
                            view.gameStartBtnClicked(0, humanList);
                            
                            //presenting that users are clicking the cards sequentially without any intellengence
                            for (int i = 0; i < 300; i++){
                                for (int j = 0; j < 13; j++){
                                    view.handCardBtnClicked(j);
                                    if (i % 10 == 0 && toggle){
                                        view.rageBtnClicked();
                                    }
                                }
                            }
                            assert(facade.getWinners().size() > 0);
                            view.dialogue_winnerBtnClicked();
                            view.gameEndBtnClicked();
                            view.gameStartBtnClicked(0, humanList);
                            view.gameEndBtnClicked();
                        }
                    }
                }
            }
        }
    }
    
    
    
    return 0;
}