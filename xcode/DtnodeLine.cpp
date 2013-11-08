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
	for( int y=0; y<mYRes; y++ )
    {
        
        addDtnode( mXRes, y, res );
	}
}

void DtnodeLine::update(Color color)
{
	for( list<Dtnode>::iterator p = mDtnodes.begin(); p != mDtnodes.end(); ++p ){
		p->update( color);
	}
}

void DtnodeLine::draw()
{
    for( list<Dtnode>::iterator p = mDtnodes.begin(); p != mDtnodes.end(); ++p ){
		p->draw();
	}
    
    
}

void DtnodeLine::addDtnode( int xi, int yi, int res )
{

	float y = ( yi + 0.5f ) * (float)res;
    //cout << "y= " << y << endl << endl;
	mDtnodes.push_back( Dtnode( Vec2f( xi, y ) ) );
}