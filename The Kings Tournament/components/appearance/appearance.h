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

struct Appearance : entityx::Component<Appearance> {
    virtual SDL_Surface* render(float dt) { SDL_Surface m; return &m; }
    virtual void render(entityx::Entity entity, float dt) { render(dt); }
};

#endif
