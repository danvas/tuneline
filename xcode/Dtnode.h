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
    Dtnode(ci::Vec2f, float);
    void update(ci::Color );
    void draw();
    Dtnode thisNode();
    
    void addTrack( Track );
    ci::Vec2i getPosition();
    bool isInsideNode(ci::Vec2i);
    
    float mSize;
    ci::Color mColor;
    
private:
    std::vector<Track> tracks;
    ci::Vec2f mPos;
    
    
};