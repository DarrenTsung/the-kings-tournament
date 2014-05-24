//
//  input.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "input.h"
#include "playerinput.h"

void InputSystem::update(entityx::EntityManager &es, entityx::EventManager &events, double dt) {
    if (!_p1disabled) {
        if (_app->keystate.left) {
            events.emit<PlayerInput>(InputType::PLAYER_ONE_LEFT);
            playerOne->move_left();
        }
        if (_app->keystate.right) {
            events.emit<PlayerInput>(InputType::PLAYER_ONE_RIGHT);
            playerOne->move_right();
        }
        if (_app->keystate.heavy) {
            events.emit<PlayerInput>(InputType::PLAYER_ONE_HEAVY);
            playerOne->straight();
        }
    }
}
