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

struct Fighter_look : Appearance {
    SDL_Surface* render(float dt);
    
    float get_width();
    float get_height();
    
private:
    SDL_Surface* bmp();
    SDL_Surface* _bmp;
};

#endif /* defined(__The_Kings_Tournament__fighter_look__) */
