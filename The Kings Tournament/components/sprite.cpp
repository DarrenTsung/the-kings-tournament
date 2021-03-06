//
//  sprite.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/22/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "sprite.h"

Sprite::Sprite(std::string filename, SDL_Renderer *renderer, unsigned frameCount, unsigned frameWidth, float delay) :
    _frameCount(frameCount),
    frameWidth(frameWidth),
    _delay(delay),
    _currFrame(0),
    _frameTimer(0.0),
    _delegate(nullptr),
    _myCallback(nullptr)
{
    // create the texture from the file
    SDL_Surface *_bmp = SDL_LoadBMP(filename.c_str());
    if (_bmp == nullptr){
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    }
    // set color for transparency
    SDL_SetColorKey(_bmp, SDL_TRUE, SDL_MapRGB(_bmp->format, 255, 14, 247));
    
    animationTexture = SDL_CreateTextureFromSurface(renderer, _bmp);
    if (animationTexture == nullptr){
        std::cout << "SDL_CreateTextureFromSurface Error: "
        << SDL_GetError() << std::endl;
    }
    frameHeight = _bmp->h;
    SDL_FreeSurface(_bmp);
}

void Sprite::reset() {
    _currFrame = 0;
    _frameTimer = 0;
}

unsigned Sprite::currentFrame() {
    return _currFrame;
}

void Sprite::set_callback(CallbackType callback, Fighter* delegate) {
    _myCallback = callback;
    _delegate = delegate;
}

void Sprite::update_delegate(Fighter *newDelegate) {
    _delegate = newDelegate;
}

SDL_Rect Sprite::currentFrameRect() {
    SDL_Rect target;
    target.w = frameWidth;
    target.h = frameHeight;
    target.x = frameWidth * _currFrame;
    target.y = 0;
    return target;
}

void Sprite::update(double dt) {
    _frameTimer += dt;
    while (_frameTimer > _delay) {
        _frameTimer -= _delay;
        _currFrame += 1;
        // if we've reached past the last frame, callback or go back to the first frame
        if (_currFrame >= _frameCount) {
            if (_myCallback) {
                (_delegate->*_myCallback)();
                _currFrame = 0;
            } else {
                _currFrame = 0;
            }
        }
    }
}