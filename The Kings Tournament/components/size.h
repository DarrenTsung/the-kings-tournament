//
//  size.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef The_Kings_Tournament_size_h
#define The_Kings_Tournament_size_h

#include <entityx/entityx.h>

struct Size : entityx::Component<Size> {
    Size(float w, float h) : width(w), height(h) {}
    
    float width, height;
};

#endif
