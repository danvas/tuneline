//
//  DtnodeLine.h
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-08.
//
//

#include "Dtnode.h"
#include "cinder/Color.h"
#include <iostream>
#include <list>

class DtnodeLine {
public:
    DtnodeLine();
    DtnodeLine( int );
    
    void update(ci::Color);
    
    void draw();
    void addDtnode( int, int, int );
    
    std::list<Dtnode> mDtnodes;
    
    int mXRes, mYRes;
    
};

