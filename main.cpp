//
//  main.cpp
//  CS247
//
//  Created by Matthew Yang on 2013-06-13.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Game.h"
#include "Model.h"
#include "Facade.h"
#include "Controller.h"
#include "View.h"
#include "HeaderGUI.h"

int main(int argc, char * argv[]){
    //initialize the default value to be 0
    int providedArgument = 0;
    //if there are additional commandline parmeters, parse to int
    if (argc > 1){
        std::istringstream ss(argv[1]);
        ss >> providedArgument;
    }
    //initialize the pesudo random sequence
    srand48(providedArgument);
    //construct the game object, which controls the entire game
    
    
    Model model;                          // Create model
    Facade facade(&model);
    Controller controller( &facade );  // Create controller
    Gtk::Main  kit( argc, argv ); 
	View view( &controller, &facade );     // Create the view -- is passed handle to controller and model
	//View view;
    Gtk::Main::run( view );               // Show the window and return when it is closed.
	    
    
    return 0;
}

