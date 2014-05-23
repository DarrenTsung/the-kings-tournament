//
//  fighter.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "fighter.h"
#include "position.h"
#include "size.h"
#include "identity.h"
#include "velocity.h"
#include "fighter_look.h"

#define SCREEN_WIDTH 1280

Fighter::Fighter(StartPosition pos) :
    _startingPosition(pos)
{
    _moveSpeed = 60.0f;
    _state = State::GROUND;
}

void Fighter::initialize(entityx::EntityManager *es, entityx::EventManager *events) {
    _manager = es;
    
    _entity = es->create();
    //_entity.assign<Identity>(EntityIdentity::Fighter);
    _entity.assign<Fighter_look>(this);
    
    float w = _entity.component<Fighter_look>()->get_width();
    float h = _entity.component<Fighter_look>()->get_height();
    
    _entity.assign<Size>(w, h);
    switch (_startingPosition)
    {
        case LEFT:
            _entity.assign<Position>(100, 100 + h);
            _entity.assign<Identity>(EntityIdentity::PLAYER_ONE);
            _facing = Direction::RIGHT;
            break;
        case RIGHT:
            _entity.assign<Position>(SCREEN_WIDTH - 100 - w, 100 + h);
            _entity.assign<Identity>(EntityIdentity::PLAYER_TWO);
            _facing = Direction::LEFT;
            break;
    }
    _entity.assign<Velocity>(0,0);
}

void Fighter::update(double dt) {
    entityx::ComponentHandle<Velocity> vel = _entity.component<Velocity>();
    entityx::ComponentHandle<Position> pos = _entity.component<Position>();
    switch (_state) {
        case State::GROUND:
        {
            float dtPos_x = dt * vel->x;
            // switch position change if facing left (a positive change adds negative x)
            if (_facing == Direction::LEFT) dtPos_x *= -1;
            if (dtPos_x > 0.0) {
                std::cout << "dtPos : " << dtPos_x << std::endl;
            }
            pos->x += dtPos_x;
            
            // friction, velocity decreases by fraction every second
            // INTEGRATION PROBLEMS I KNOW FIX LATER
            vel->x -= dt*2*_moveSpeed;
            if (vel->x > 0.0) {
                std::cout << "xVel : " << vel->x << std::endl;
            }
            if (vel->x < 10) vel->x = 0;
            break;
        }
        case State::IN_AIR:
        {
            // handle y changes here as well
            break;
        }
    }
}

void Fighter::move_left() {
    // no input allowed if not on ground
    if (_state == State::GROUND) {
        entityx::ComponentHandle<Velocity> vel = _entity.component<Velocity>();
        if (_facing == Direction::LEFT) {
            vel->x = _moveSpeed;
        } else {
            // TURN HERE
            _facing = Direction::LEFT;
        }
    }
}

void Fighter::move_right() {
    // no input allowed if not on ground
    if (_state == State::GROUND) {
        entityx::ComponentHandle<Velocity> vel = _entity.component<Velocity>();
        if (_facing == Direction::RIGHT) {
            vel->x = _moveSpeed;
        } else {
            // TURN HERE
            _facing = Direction::RIGHT;
        }
    }
}

std::string Fighter::current_frame() {
    return "bear_map.bmp";
}

Fighter& Fighter::operator=(const Fighter& other) {
    _startingPosition = other._startingPosition;
    _moveSpeed = other._moveSpeed;
    _state = other._state;
    return *this;
}