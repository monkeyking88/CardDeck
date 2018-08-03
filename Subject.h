//
//  Subject.h
//  CS247
//
//  Created by Matthew Yang on 2013-07-16.
//  Copyright (c) 2013 Matthew Yang. All rights reserved.
//

#ifndef Subject_H
#define Subject_H
#include <set>

class Observer;

class Subject {
public:
    void subscribe( Observer* );
    void unsubscribe( Observer* );
    
protected:
    void notify();
    
private:
    typedef std::set< Observer* > Observers;
    Observers observers_;
}; // Subject


#endif
