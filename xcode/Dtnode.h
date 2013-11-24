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

#include "Track.h"

#include <vector>
#include <iostream>


class Dtnode {
public:
    Dtnode();
    Dtnode(unsigned int, ci::Vec2f, float);
    void update(ci::Color, ci::Vec2f);
    void draw();

    
    void addTrack( Track );
    ci::Vec2i getPosition();
    bool isInsideNode(ci::Vec2i);
    
    float mSize;
    ci::Color mColor;
    unsigned int mLevel;
    
private:
    std::vector<Track> tracks;
    ci::Vec2f mPos;
    
    
};