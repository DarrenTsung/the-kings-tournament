//
//  movement.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

// components
#include "position.h"
#include "movement.h"

void MovementSystem::update(entityx::EntityManager &es, entityx::EventManager &events, double dt) {
    
}

void MovementSystem::configure(entityx::EventManager &event_manager) {
    event_manager.subscribe<PlayerInput>(*this);
}


void MovementSystem::receive(const PlayerInput &input) {
    switch (input.type) {
        case PLAYER_ONE_LEFT:
            playerOne->move_left();
            break;
        case PLAYER_ONE_RIGHT:
            playerOne->move_right();
    }
}