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
#include "fighter_look.h"

#define SCREEN_WIDTH 1280

Fighter::Fighter(StartPosition pos) :
    _startingPosition(pos)
{
    
}

void Fighter::initialize(entityx::EntityManager *es, entityx::EventManager *events) {
    _manager = es;
    
    _entity = es->create();
    //_entity.assign<Identity>(EntityIdentity::Fighter);
    _entity.assign<Fighter_look>();
    
    float w = _entity.component<Fighter_look>()->get_width();
    float h = _entity.component<Fighter_look>()->get_height();
    
    _entity.assign<Size>(w, h);
    switch (_startingPosition)
    {
        case LEFT:
            _entity.assign<Position>(100, 100 + h);
            break;
        case RIGHT:
            _entity.assign<Position>(SCREEN_WIDTH - 100 - w, 100 + h);
    }
}

void Fighter::update(double dt) {
    
}

Fighter& Fighter::operator=(const Fighter& other) {
    _startingPosition = other._startingPosition;
    return *this;
}