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
#include <vector>

class DtnodeLine {
public:
    DtnodeLine();
    DtnodeLine( int );
    
    void update(ci::Color);
    
    void draw();
    void addDtnode( int, int, int );
    void expandDtnode (Dtnode);

    Dtnode getNodeAtPosition(ci::Vec2i);
    
    std::vector<Dtnode> mDtnodes;
    //std::list<Dtnode> mDtnodes;
    
    int mXRes, mYRes;
private:
    float sizeOffset;
    
};

