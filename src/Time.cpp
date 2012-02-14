//
//  Time.cpp
//  HelloSDL
//
//  Created by Alexander Zubko on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "common.h"

#include "Time.h"

Time::Time()
    : delta_(0)
    , elapsed_(0)
{
}

bool Time::Init() {
    oldCounter_ = SDL_GetPerformanceCounter();
    return true;
}

void Time::Tick() {
    uint64_t now = SDL_GetPerformanceCounter();
    delta_ = (now - oldCounter_) / (float)SDL_GetPerformanceFrequency();
    oldCounter_ = now;
    
    if (delta_ > 0.1) 
        delta_ = 0.0016;
    
    elapsed_ += delta_;
}