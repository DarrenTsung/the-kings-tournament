//
//  fighter_look.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__fighter_look__
#define __The_Kings_Tournament__fighter_look__

#include <iostream>
#include "appearance.h"
#include "fighter.h"

struct Fighter_look : Appearance {
    Fighter_look(Fighter *ft) : _fighter(ft) {}
    
    SDL_Texture* texture();
    SDL_Rect rect();
    
    void update(double dt);
    
private:
    Fighter* _fighter;
};

#endif /* defined(__The_Kings_Tournament__fighter_look__) */
