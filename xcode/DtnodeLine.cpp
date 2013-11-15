//
//  DtnodeLine.cpp
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-08.
//
//

#include "DtnodeLine.h"
#include "cinder/app/AppBasic.h"



using namespace ci;
using namespace std;

DtnodeLine::DtnodeLine(){}

DtnodeLine::DtnodeLine( int res )
{
    mXRes = app::getWindowWidth()/2.0f;
    cout << "mXRes = " << mXRes << endl;
	mYRes = app::getWindowHeight()/res;
	cout << "mYRes = " << mYRes << endl;
    
    sizeOffset = 0.5f;
    
	for( int y=0; y<mYRes; y++ )
    {
        addDtnode( mXRes, y, res );
	}
}

void DtnodeLine::update(Color color)
{    
    for(int i = 0; i < mDtnodes.size(); i++)
    {
        mDtnodes[i].update(color);
    }
}

void DtnodeLine::draw()
{
    
    for(int i = 0; i < mDtnodes.size(); i++)
    {
        mDtnodes[i].draw();
    }
    
}

void DtnodeLine::addDtnode( int xi, int yi, int res )
{
    float size = res/2.0f * sizeOffset;
	float y = ( yi + 0.5f ) * (float)res;
	mDtnodes.push_back( Dtnode( Vec2f( xi, y ), size ) );
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

void DtnodeLine::expandDtnode (Dtnode dtnode)
{
    
}

