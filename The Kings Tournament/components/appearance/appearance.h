//
//  appearance.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef The_Kings_Tournament_appearance_h
#define The_Kings_Tournament_appearance_h

#include <entityx/entityx.h>
#include <SDL2/SDL.h>
#include "sprite.h"

struct Appearance : entityx::Component<Appearance> {
    virtual SDL_Texture* texture() { return nullptr; }
    virtual SDL_Rect rect() {SDL_Rect t; return t;}
    
    virtual void update(double dt) {}
};

#endif
