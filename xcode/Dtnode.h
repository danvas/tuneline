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
    Dtnode();
    
    ci::Vec2f mLoc;
    float mRadius;
    ci::Color mColor;
    
};