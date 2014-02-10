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

#define MAX_NODES 40
#define TWEEN_SPEED 0.2
class DtnodeLine {
public:
    DtnodeLine();
    DtnodeLine( std::string, unsigned int, ci::Vec2f);
    
    void update();
    
    void draw();
    void setLineResolution(int);
    void expandNodeUpdate();
    
    Dtnode getNodeAtPosition(ci::Vec2f, bool*);
    int getNodeIndexAtPosition(ci::Vec2f, bool*);
    int getLineResolution(int);
    std::vector<Dtnode> mDtnodes;
    
    int mSpacing;
    ci::Vec2f mPivot;
private:
    boost::gregorian::date mToday;
    boost::gregorian::date mBirthdate;
    int mLevel;
    int mResolution;
    ci::Vec2f mDirToPivot;
    
    ci::Vec2f targetPosition[MAX_NODES];
    double elapsedLevelTime;
};

