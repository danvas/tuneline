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
    setLineResolution(level);
    mLevel = level;
	mSpacing = getWindowHeight() / mResolution;
    
    float offsetY = pivot.y + mSpacing/2.0f;
    int chosenNode = 0;
    int enterNodeIndex = (chosenNode < mResolution? chosenNode : mResolution - 1);
    console() << "enter other index? " << (enterNodeIndex? "yes" : "no") << endl;
    
    Vec2f currentPosition;
    date incrDate;
    if (enterNodeIndex)
    {
        console() << "Starting at index " << enterNodeIndex << endl;
        offsetY = enterNodeIndex*mSpacing/2.0f;
        
        for(int i = 0; i<mResolution; i++)
        {
            currentPosition = Vec2f(pivot.x, pivot.y + offsetY);
            mDtnodes.push_back( Dtnode( incrDate, currentPosition, CIRCLE_RADIUS ) );
            
            targetPosition[i].x = pivot.x;
            targetPosition[i].y = (i - enterNodeIndex)*mSpacing + offsetY;
            
            startPosition[i].x = pivot.x;
            startPosition[i].y = pivot.y + offsetY;
            
            console() << "current: " << mDtnodes[i].position << endl;
            console() << "start: " << startPosition[i].y << endl;
            console() << "target: " << targetPosition[i].y << endl << endl;

            circleTimeBase[i] = 0;
            
            switch (level){
                case 0:
                    incrDate = mBirthdate;
                    break;
                case 1:
                    incrDate = date(mBirthdate.year() + 10, mBirthdate.month(), mBirthdate.day());
                    break;
                case 2:
                    incrDate = date(mBirthdate.year() + 1, mBirthdate.month(), mBirthdate.day());
                    break;
                case 3:
                    incrDate = date(mBirthdate.year(), mBirthdate.month() + 1, mBirthdate.day());
                    break;
                case 4:
                    incrDate = date(mBirthdate.year(), mBirthdate.month(), mBirthdate.day() + 1);
                    break;
            }
        }
    }
    else
    {
        for(int i = 0; i<mResolution; i++)
        {
            currentPosition = Vec2f(pivot.x, pivot.y + offsetY);
            mDtnodes.push_back( Dtnode( mBirthdate, currentPosition, CIRCLE_RADIUS ) );
            
            targetPosition[i].x = pivot.x;
            targetPosition[i].y = i * mSpacing + offsetY;
            
            startPosition[i].x = pivot.x;
            startPosition[i].y = pivot.y + offsetY;
            
            console() << "current: " << mDtnodes[i].position << endl;
            console() << "start: " << startPosition[i].y << endl;
            console() << "target: " << targetPosition[i].y << endl << endl;

            circleTimeBase[i] = 0;
            
            switch (level){
                case 0:
                    incrDate = mBirthdate;
                    break;
                case 1:
                    incrDate = date(mBirthdate.year() + 10, mBirthdate.month(), mBirthdate.day());
                    break;
                case 2:
                    incrDate = date(mBirthdate.year() + 1, mBirthdate.month(), mBirthdate.day());
                    break;
                case 3:
                    incrDate = date(mBirthdate.year(), mBirthdate.month() + 1, mBirthdate.day());
                    break;
                case 4:
                    incrDate = date(mBirthdate.year(), mBirthdate.month(), mBirthdate.day() + 1);
                    break;
            }
        }
    }
    

    
    
}

void DtnodeLine::update()
{
    
    Vec2f currentPosition;
    for (int i=0; i<mResolution; i++) {        
        currentPosition = easeOutExpo((getElapsedSeconds()-circleTimeBase[i]) * TWEEN_SPEED) * (targetPosition[i] - startPosition[i]) + startPosition[i];
        
        mDtnodes[i].setPosition(currentPosition);
        
        if ( mDtnodes[i].position.distance(targetPosition[i]) < 1.0f ){
            startPosition[i] = mDtnodes[i].position;
            circleTimeBase[i] = getElapsedSeconds();  
        }
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
    for(int i = 0; i < mDtnodes.size(); i++)
    {
        node = mDtnodes[i];
        if ( node.isInsideNode(position) )
        {
            *onNode = true;
            break;
        }
        *onNode = false;
    }
    cout << "*onNode = " << *onNode << endl;
    
    return node;
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
            mResolution = DateUtil::getYearspan(mBirthdate, mToday);
            break;
        case 3:// months
            mResolution = DateUtil::getMonthspan( greg_year(2013) );
            break;
        case 4:// days
            greg_year someYear = greg_year(2013);
            greg_month someMonth = greg_month(Nov);
            mResolution = DateUtil::getDayspan(someYear, someMonth);
            break;
    }
}



