//
//  velocity.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef The_Kings_Tournament_velocity_h
#define The_Kings_Tournament_velocity_h

#include <entityx/entityx.h>

struct Velocity : entityx::Component<Velocity> {
    Velocity(float x, float y) : x(x), y(y) {}
    
    float x, y;
};

#endif
