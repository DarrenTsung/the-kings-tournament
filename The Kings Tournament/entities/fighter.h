//
//  fighter.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__fighter__
#define __The_Kings_Tournament__fighter__

#include <iostream>
#include <entityx/entityx.h>

enum StartPosition {
    LEFT = 0,
    RIGHT = 1
};

/**
 Fighter class representing the characters in the game
 */
class Fighter {
public:
    // constructors
    Fighter() {}
    Fighter(StartPosition pos);
    
    void initialize(entityx::EntityManager *es, entityx::EventManager *events);
    
    void update(double dt);
    
    Fighter& operator=(const Fighter& other);
    
private:
    entityx::Entity _entity;
    entityx::EntityManager *_manager;
    
    StartPosition _startingPosition;
};

#endif /* defined(__The_Kings_Tournament__fighter__) */
