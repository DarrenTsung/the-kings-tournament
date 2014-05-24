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
    _moveSpeed = 130.0f;
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
    Sprite *a3 = new Sprite("bear_man_backwalk_right.bmp", renderer, 4, 180, 0.23);
    _animationMap.insert(std::pair<std::pair<Animation, Direction>, Sprite*>(
         std::make_pair(Animation::BACKWALK, Direction::RIGHT), a3));
    Sprite *a4 = new Sprite("bear_man_straight_right.bmp", renderer, 5, 180, 0.06);
    a4->set_callback(&Fighter::set_idle, this);
    _animationMap.insert(std::pair<std::pair<Animation, Direction>, Sprite*>(
         std::make_pair(Animation::STRAIGHT, Direction::RIGHT), a4));
    Sprite *a5 = new Sprite("bear_man_jab_right.bmp", renderer, 4, 180, 0.05);
    a5->set_callback(&Fighter::set_idle, this);
    _animationMap.insert(std::pair<std::pair<Animation, Direction>, Sprite*>(
         std::make_pair(Animation::JAB, Direction::RIGHT), a5));
    
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
    typedef std::map<std::pair<Animation, Direction>, Sprite*>::iterator it_type;
    // update the delegate for all the animations (as long as no callback is created, no callbacks will be called);
    for(it_type iterator = _animationMap.begin(); iterator != _animationMap.end(); iterator++) {
        iterator->second->update_delegate(this);
    }
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
            if (abs(dtPos_x) > 0) {
                std::cout << "dtPos_x: " << dtPos_x << std::endl;
            }
            pos->x += dtPos_x;
            
            // friction, velocity decreases by fraction every second
            // INTEGRATION PROBLEMS I KNOW FIX LATER
            float change = 0;
            if (vel->x != 0)
                change = vel->x > 0.0 ? -dt*2.0*_moveSpeed : dt*2.0*2.0/3.0*_moveSpeed;
            if (abs(change) > 0) {
                std::cout << "vel: " << vel->x << " | " << vel->y << std::endl;
                std::cout << "change: " << change << std::endl;
            }
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
    if (_state == State::GROUND && !_inputDisabled) {
        entityx::ComponentHandle<Velocity> vel = _entity.component<Velocity>();
        if (_facing == Direction::LEFT) {
            vel->x = _moveSpeed;
            if (currentAnimation != Animation::WALK)
                switchAnimation(Animation::WALK);
        } else {
            vel->x = -1.0/2.0*_moveSpeed;
            if (currentAnimation != Animation::BACKWALK)
                switchAnimation(Animation::BACKWALK);
        }
    }
}

void Fighter::move_right() {
    // no input allowed if not on ground
    if (_state == State::GROUND && !_inputDisabled) {
        entityx::ComponentHandle<Velocity> vel = _entity.component<Velocity>();
        if (_facing == Direction::RIGHT) {
            vel->x = _moveSpeed;
            if (currentAnimation != Animation::WALK)
                switchAnimation(Animation::WALK);
        } else {
            vel->x = -1.0/2.0*_moveSpeed;
            if (currentAnimation != Animation::BACKWALK)
                switchAnimation(Animation::BACKWALK);
        }
    }
}

void Fighter::straight() {
    // no input is allowed if not on ground
    if (_state == State::GROUND && !_inputDisabled) {
        switchAnimation(Animation::STRAIGHT);
        _inputDisabled = true;
    }
}

void Fighter::jab() {
    // no input if not on ground or if input is disabled
    if (_state == State::GROUND && !_inputDisabled) {
        switchAnimation(Animation::JAB);
        _inputDisabled = true;
    }
}

void Fighter::set_idle() {
    switchAnimation(Animation::IDLE);
    _inputDisabled = false;
}

void Fighter::switchAnimation(Animation animationToSwitchTo) {
    if (!_inputDisabled) {
        currentAnimation = animationToSwitchTo;
        _animationMap[std::make_pair(currentAnimation, _facing)]->reset();
    }
}