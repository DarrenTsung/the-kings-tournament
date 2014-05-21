//
//  helper.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/20/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__helper__
#define __The_Kings_Tournament__helper__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

namespace helper {

    inline SDL_Surface* SurfaceForString(std::string fontPath, std::string string, int fontSize, SDL_Color fontColor) {
        TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if(!font) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            // handle error
        }
        return TTF_RenderText_Solid(font, string.c_str(), fontColor);
    }

}

#endif /* defined(__The_Kings_Tournament__helper__) */
