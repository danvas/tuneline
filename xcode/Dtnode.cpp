//
//  Dtnode.cpp
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-07.
//
//
#include "Dtnode.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "DateUtil.h"
#include "Track.h"


using namespace ci;
using namespace ci::app;
using namespace boost::gregorian;


Dtnode::Dtnode(){}

Dtnode::Dtnode(date aDate, Vec2f pos, float size)
{
    mDate = aDate;
    position = pos;
    mSize = size;
    mDirToPivot = Vec2f::zero();
    mColor = Color(0.8f, 0.2f, 0.3f);
}

void Dtnode::update(Color color, Vec2f pivot)
{
    
    mDirToPivot = pivot - position;
    //console() << "DirToPivot = " << mDirToPivot << std::endl;
    mDirToPivot.safeNormalize();
    mColor = color;
}

void Dtnode::draw()
{
    gl::color( mColor);
    gl::drawSolidEllipse(position, mSize, mSize);
    
}


void Dtnode::setPosition(Vec2f pos){
    position = pos;
}


bool Dtnode::isInsideNode(Vec2i pos)
{
    return pow((pos.x - position.x), 2.0) + pow((pos.y - position.y), 2.0) < pow(mSize, 2.0);
}





