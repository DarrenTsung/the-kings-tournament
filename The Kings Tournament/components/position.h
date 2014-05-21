//
//  position.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__position__
#define __The_Kings_Tournament__position__

#include <entityx/entityx.h>

struct Position : entityx::Component<Position> {
    Position(float x, float y) : x(x), y(y) {}
    
    float distance(Position other) {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }
    
    float x, y;
};

#endif /* defined(__The_Kings_Tournament__position__) */
