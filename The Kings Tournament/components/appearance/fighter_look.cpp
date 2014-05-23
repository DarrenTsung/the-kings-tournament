//
//  fighter_look.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "fighter_look.h"

SDL_Texture* Fighter_look::texture() {
    Sprite *currSprite = _fighter->animations[_fighter->currSprite];
    return currSprite->animationTexture;
}

SDL_Rect Fighter_look::rect() {
    Sprite *currSprite = _fighter->animations[_fighter->currSprite];
    return currSprite->currentFrameRect();
}

void Fighter_look::update(double dt) {
    Sprite *currSprite = _fighter->animations[_fighter->currSprite];
    currSprite->update(dt);
}
