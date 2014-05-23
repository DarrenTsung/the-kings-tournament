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
#include "app.h"

#define SCREEN_WIDTH 1280

Fighter::Fighter(StartPosition pos, SDL_Renderer *renderer) :
    _startingPosition(pos)
{
    _moveSpeed = 60.0f;
    _state = State::GROUND;
    
    switch(_startingPosition) {
        case LEFT:
            _facing = Direction::RIGHT;
            break;
        case RIGHT:
            _facing = Direction::LEFT;
            break;
    }
    
    // filename, renderer, frame count, frame width, delay (ms) 
    Sprite *a1 = new Sprite("bear_man_idle_right.bmp", renderer, 4, 180, 0.2);
    // keys are (animation type, direction)
    _animationMap.insert(std::pair<std::pair<Animation, Direction>, Sprite*>(
         std::make_pair(Animation::IDLE, Direction::RIGHT), a1));
    Sprite *a2 = new Sprite("bear_man_walk_right.bmp", renderer, 4, 180, 0.2);
    _animationMap.insert(std::pair<std::pair<Animation, Direction>, Sprite*>(
         std::make_pair(Animation::WALK, Direction::RIGHT), a2));
    Sprite *a3 = new Sprite("bear_man_backwalk_right.bmp", renderer, 4, 180, 0.3);
    _animationMap.insert(std::pair<std::pair<Animation, Direction>, Sprite*>(
         std::make_pair(Animation::BACKWALK, Direction::RIGHT), a3));
    
    // idle sprite is start animation
    currentAnimation = Animation::IDLE;
}

Fighter& Fighter::operator=(const Fighter& other) {
    _startingPosition = other._startingPosition;
    _moveSpeed = other._moveSpeed;
    _state = other._state;
    
    _facing = other._facing;
    _startingPosition = other._startingPosition;
    
    currentAnimation = other.currentAnimation;
    _animationMap = other._animationMap;
    return *this;
}

Sprite* Fighter::currentSprite() {
    return _animationMap[std::make_pair(currentAnimation, _facing)];
}

void Fighter::initialize(entityx::EntityManager *es, entityx::EventManager *events) {
    _manager = es;
    
    _entity = es->create();
    //_entity.assign<Identity>(EntityIdentity::Fighter);
    _entity.assign<Fighter_look>(this);
    
    float w = currentSprite()->frameWidth;
    float h = currentSprite()->frameHeight;
    
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
            pos->x += dtPos_x;
            
            // friction, velocity decreases by fraction every second
            // INTEGRATION PROBLEMS I KNOW FIX LATER
            float change = vel->x > 0 ? -dt*2*_moveSpeed : dt*2*_moveSpeed;
            vel->x += change;
            if (abs(vel->x) < 10) {
                vel->x = 0;
                if (currentAnimation != Animation::IDLE)
                    switchAnimation(Animation::IDLE);
            }
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
            vel->x = -_moveSpeed;
            if (currentAnimation != Animation::BACKWALK)
                switchAnimation(Animation::BACKWALK);
        }
    }
}

void Fighter::move_right() {
    // no input allowed if not on ground
    if (_state == State::GROUND) {
        entityx::ComponentHandle<Velocity> vel = _entity.component<Velocity>();
        if (_facing == Direction::RIGHT) {
            vel->x = _moveSpeed;
            if (currentAnimation != Animation::WALK)
                switchAnimation(Animation::WALK);
        } else {
            // TURN HERE
            _facing = Direction::RIGHT;
        }
    }
}

void Fighter::switchAnimation(Animation animationToSwitchTo) {
    currentAnimation = animationToSwitchTo;
    _animationMap[std::make_pair(currentAnimation, _facing)]->reset();
}