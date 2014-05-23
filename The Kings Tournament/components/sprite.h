//
//  sprite.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/22/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__sprite__
#define __The_Kings_Tournament__sprite__

#include <iostream>
#include <SDL2/SDL.h>

/**
 Sprite is a single sprite animation, it loads in a single stripe of frames 
 and returns the right srcRect for each frame.

  -------------------------------
 |   0   |   1   |   2   |   3   |
  -------------------------------
 Input bmp file ^
 
 */
class Sprite {
public:
    // constructor
    Sprite(std::string filename, SDL_Renderer *renderer, unsigned frameCount, unsigned frameWidth, float delay);
    
    /**
     @return the current frame
     */
    unsigned currentFrame();
    
    /**
     @return the rectangle that corresponds to the current frame on the texture
     */
    SDL_Rect currentFrameRect();
    
    /**
     updates the Sprite with the time passed
     */
    void update(double dt);
    
    /**
     resets the current state of the animation, ie sets current frame to 0 and frame timer to 0
     */
    void reset();
    
    
    SDL_Texture *animationTexture;
    unsigned frameHeight, frameWidth;
    
private:
    unsigned _frameCount, _currFrame;
    float _delay, _frameTimer;
};

#endif /* defined(__The_Kings_Tournament__sprite__) */
