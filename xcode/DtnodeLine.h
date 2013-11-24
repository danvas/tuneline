//
//  DtnodeLine.h
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-08.
//
//

#include "Dtnode.h"
#include "cinder/Color.h"
#include "DateUtil.h"
#include "boost/date_time/gregorian/gregorian.hpp"

#include <iostream>
#include <list>
#include <vector>

class DtnodeLine {
public:
    DtnodeLine();
    DtnodeLine( std::string, unsigned int, ci::Vec2f);
    
    void update(ci::Color, ci::Vec2f);
    
    void draw();
    void addDtnode( unsigned int, int, int, int );
    void setLineResolution(int);
    Dtnode getNodeAtPosition(ci::Vec2i);
    int getLineResolution(int);
    std::vector<Dtnode> mDtnodes;
    
    int mXRes, mYSpacing;
private:
    float sizeOffset;
    boost::gregorian::date mToday;
    boost::gregorian::date mBirthdate;
    int mResolution;
};

