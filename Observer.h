//
//  Observer.h
//  CS247
//
//  Created by Matthew Yang on 2013-07-16.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef Observer_H
#define Observer_H

class Subject;

//pure virtual function in class will be overriden in view
//this is for obsever patten
class Observer {
public:
	virtual void update () = 0;
};


#endif
