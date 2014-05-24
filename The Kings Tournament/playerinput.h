//
//  playerinput.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef The_Kings_Tournament_playerinput_h
#define The_Kings_Tournament_playerinput_h

#include <entityx/entityx.h>

enum class InputType {
    PLAYER_ONE_LEFT,
    PLAYER_ONE_RIGHT,
    PLAYER_ONE_HEAVY,
    PLAYER_ONE_LIGHT
};

struct PlayerInput : public entityx::Event<PlayerInput> {
    PlayerInput(InputType type) : type(type) {}
    
    InputType type;
};

#endif
