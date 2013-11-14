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

#include "Track.h"


using namespace ci;
Dtnode::Dtnode(){}

Dtnode::Dtnode(Vec2f pos, float size)
{
    mPos = pos;
    mSize = size;
}

void Dtnode::update(Color color)
{
    mColor = color;
}

void Dtnode::draw()
{
    //gl::drawStrokedCube(mPos, mSize);
    gl::color( mColor);
    //gl::drawStrokedCircle(mPos, mSize);
    gl::drawSolidEllipse(mPos, mSize, mSize);
    
}

Dtnode Dtnode::thisNode()
{
    return *this;
}

void Dtnode::addTrack( Track track )
{
    
}

Vec2i Dtnode::getPosition()
{
    return mPos;
}

bool Dtnode::isInsideNode(Vec2i pos)
{
    return pow((pos.x - mPos.x), 2.0) + pow((pos.y - mPos.y), 2.0) < pow(mSize, 2.0);
}



