//
//  Time.h
//  HelloSDL
//
//  Created by Alexander Zubko on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// Code dealing with timing in a game

#ifndef HelloSDL_Time_h
#define HelloSDL_Time_h

class Time {

public:
    float delta_;
    float elapsed_; // use for animation only
    
    Time();
    bool Init();
    void Tick();

private:
    uint64_t oldCounter_;
};

#endif
