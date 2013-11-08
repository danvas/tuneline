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


using namespace ci;

Dtnode::Dtnode(Vec2f pos)
{
    mPos = pos;
    mSize = 10.0f;
    
    
}

void Dtnode::update(Color color)
{
    mColor = color;
}

void Dtnode::draw()
{
    //gl::drawStrokedCube(mPos, mSize);
    gl::color( mColor);
    gl::drawStrokedCircle(mPos, mSize);
    
}


