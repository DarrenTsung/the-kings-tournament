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
    if (_app->keystate.left) {
        events.emit<PlayerInput>(PLAYER_ONE_LEFT);
    }
    if (_app->keystate.right) {
        events.emit<PlayerInput>(PLAYER_ONE_RIGHT);
    }
}
