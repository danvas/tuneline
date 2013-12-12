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

#include "DateUtil.h"
#include "Track.h"

#include <vector>
#include <iostream>


class Dtnode {
public:
    Dtnode();
    Dtnode(int, boost::gregorian::date, ci::Vec2f, float);
    void update(ci::Color, ci::Vec2f);
    void draw();

    void move( ci::Vec2f );
    void setPosition(ci::Vec2f);
    bool isInsideNode(ci::Vec2i);

    int index;
    boost::gregorian::date mDate;
    ci::Vec2f position;
    ci::Vec2f mDirToPivot;
    float mSize;
    ci::Color mColor;
    
};