//
//  DtnodeLine.cpp
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-08.
//
//

#include "DtnodeLine.h"
#include "cinder/app/AppBasic.h"
#include "DateUtil.h"
#include "cinder/Rand.h"
#include "cinder/Easing.h"

#define CIRCLE_RADIUS 15.0f

using namespace ci;
using namespace cinder::app;
using namespace std;
using namespace boost::gregorian;

DtnodeLine::DtnodeLine(){}

DtnodeLine::DtnodeLine( string bdate, unsigned int level, Vec2f pivot )
{
    mToday = day_clock::local_day();
    mBirthdate = from_simple_string(bdate);
    mLevel = level;
    setLineResolution(level);
	mSpacing = getWindowWidth() / mResolution;
    mPivot = pivot;

    // set up start and target positions
    float offsetX = mSpacing/2.0f;
    Vec2f currentPosition = (!level)? Vec2f(pivot.x + offsetX, pivot.y) : Vec2f(pivot.x, pivot.y);
    for(int i = 0; i<mResolution; i++)
    {
        mDtnodes.push_back( Dtnode( i, mBirthdate, currentPosition, CIRCLE_RADIUS ) );
        
        targetPosition[i].x = (i * mSpacing) + offsetX;
        targetPosition[i].y = pivot.y;
//        console() << "current: " << mDtnodes[i].position.y << endl;
//        console() << "target: " << targetPosition[i].y << endl << endl;
    }
    elapsedLevelTime = getElapsedSeconds();
}

void DtnodeLine::update()
{
    if (mLevel){
        expandNodeUpdate();
    }
    
}

void DtnodeLine::draw()
{
    gl::color( Color(0.8f, 0.2f, 0.3f));
    for(int i = 0; i < mResolution; i++)
    {
        mDtnodes[i].draw();
    }
    
}


Dtnode DtnodeLine::getNodeAtPosition(Vec2f position, bool* onNode)
{
    
    Dtnode node;
    int i;
    for(i = 0; i < mDtnodes.size(); i++)
    {
        node = mDtnodes[i];
        if ( node.isInsideNode(position) )
        {
            *onNode = true;
            break;
        }
        *onNode = false;
    }
    
    return node;
}

int DtnodeLine::getNodeIndexAtPosition(Vec2f position, bool* onNode)
{
    
    Dtnode node;
    int i;
    for(i = 0; i < mDtnodes.size(); i++)
    {
        node = mDtnodes[i];
        if ( node.isInsideNode(position) )
        {
            *onNode = true;
            break;
        }
        *onNode = false;
    }
    
    return i;
}
void DtnodeLine::setLineResolution(int level)
{
    mResolution = 1;
    switch (level) {
        case 0:// life
            
            break;
        case 1:// decades
            mResolution = (int)ceil( DateUtil::getYearspan(mBirthdate, mToday)/10.0f );
            break;
        case 2:// years
            mResolution = 10;//DateUtil::getYearspan(mBirthdate, mToday);
            break;
        case 3:// months
            mResolution = DateUtil::getMonthspan( greg_year(2013) );
            break;
        case 4:// days
            greg_year someYear = greg_year(2013);
            greg_month someMonth = greg_month(Dec);
            mResolution = DateUtil::getDayspan(someYear, someMonth);
            break;
    }
}


void DtnodeLine::expandNodeUpdate(){
    //cout << "node.y 1: " << mDtnodes[0].position.y << endl;
    Vec2f currentPosition = Vec2f::zero();
    for (int i=0; i<mResolution; i++) {
        currentPosition = easeOutExpo((getElapsedSeconds() - elapsedLevelTime) * TWEEN_SPEED)
                            * (targetPosition[i] - mPivot)
                            + mPivot;
        
        mDtnodes[i].position = currentPosition;
    }
}

