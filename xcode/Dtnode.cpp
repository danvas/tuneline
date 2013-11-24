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

Dtnode::Dtnode(unsigned int level, Vec2f pos, float size)
{
    mLevel = level;
    mPos = pos;
    mSize = size;
}

void Dtnode::update(Color color, Vec2f translate)
{
    mColor = color;
    if( isInsideNode(translate) )
    {
        mPos = translate;
    }
    
}

void Dtnode::draw()
{
    gl::color( mColor);
    gl::drawSolidEllipse(mPos, mSize, mSize);
    
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



