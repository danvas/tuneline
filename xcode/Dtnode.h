//
//  Dtnode.h
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-07.
//
//
#pragma once
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include <iostream>


class Dtnode {
public:
    Dtnode(ci::Vec2f);
    void update(ci::Color );
    void draw();
    
    ci::Vec2f mPos;
    float mSize;
    ci::Color mColor;
    
};