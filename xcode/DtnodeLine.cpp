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



using namespace ci;
using namespace std;
using namespace boost::gregorian;

DtnodeLine::DtnodeLine(){}

DtnodeLine::DtnodeLine( string bdate, unsigned int level, Vec2f pivot )
{
    mToday = day_clock::local_day();
    mBirthdate = from_simple_string(bdate);
    setLineResolution(level);
    mXRes = pivot.x;
	mYSpacing = pivot.y;
    printf("\nmYSpacing = %d", mYSpacing);

    sizeOffset = 0.5f;
    
	for( int y = 0; y < mResolution; y++ )
    {
        addDtnode( level, mXRes, y, mYSpacing );
	}
}

void DtnodeLine::update(Color color, Vec2f pivot)
{    
    for(int i = 0; i < mDtnodes.size(); i++)
    {
        mDtnodes[i].update(color, pivot);
    }
}

void DtnodeLine::draw()
{
    
    for(int i = 0; i < mDtnodes.size(); i++)
    {
        mDtnodes[i].draw();
    }
    
}

void DtnodeLine::addDtnode( unsigned int level, int xi, int yi, int spacing )
{
    float size = spacing/2.0f * sizeOffset;
    
	float y = ( yi * (float)spacing );
    //printf("\ny = %f", y);
	mDtnodes.push_back( Dtnode( level, Vec2f( xi, y ), size ) );
}

Dtnode DtnodeLine::getNodeAtPosition(Vec2i position)
{
    
    Dtnode node;
    for(int i = 0; i < mDtnodes.size(); i++)
    {
        node = mDtnodes[i];
        if ( node.isInsideNode(position) )
        {
            break;
        }
    }
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


