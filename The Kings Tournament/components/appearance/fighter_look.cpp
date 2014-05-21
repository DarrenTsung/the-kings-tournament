//
//  fighter_look.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "fighter_look.h"

SDL_Surface* Fighter_look::render(float dt) {
    return bmp();
}

float Fighter_look::get_height() {
    return bmp()->h;
}

float Fighter_look::get_width() {
    return bmp()->w;
}

SDL_Surface* Fighter_look::bmp() {
    if (!_bmp) {
        _bmp = SDL_LoadBMP("bear_man.bmp");
        if (_bmp == nullptr){
            std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }
    }
    return _bmp;
}