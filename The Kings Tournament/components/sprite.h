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

class Fighter;

// typedef to make callbacks easier (no arguments + no return)
typedef void (Fighter::* CallbackType)();

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
     changes the type from looping (default) to callback at the end of the sprite animation
     */
    void set_callback(CallbackType callback, Fighter* delegate);
    // for copying fighter objects
    void update_delegate(Fighter *newDelegate);
    
    /**
     resets the current state of the animation, ie sets current frame to 0 and frame timer to 0
     */
    void reset();
    
    
    SDL_Texture *animationTexture;
    unsigned frameHeight, frameWidth;
    
private:
    CallbackType _myCallback;
    Fighter *_delegate;
    
    unsigned _frameCount, _currFrame;
    float _delay, _frameTimer;
};

#endif /* defined(__The_Kings_Tournament__sprite__) */
