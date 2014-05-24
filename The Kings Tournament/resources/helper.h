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

    inline SDL_Surface* SurfaceForFontAndString(TTF_Font *font, std::string string, SDL_Color fontColor) {
        return TTF_RenderText_Solid(font, string.c_str(), fontColor);
    }

}

#endif /* defined(__The_Kings_Tournament__helper__) */
