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
#include <vector>
#include "sprite.h"

enum StartPosition {
    LEFT = 0,
    RIGHT = 1
};

enum class Direction { LEFT, RIGHT };
enum class State { IN_AIR, GROUND };

/**
 Fighter class representing the characters in the game
 */
class Fighter {
public:
    // constructors
    Fighter() {}
    Fighter(StartPosition pos, SDL_Renderer *renderer);
    
    void initialize(entityx::EntityManager *es, entityx::EventManager *events);
    
    void update(double dt);
    
    /**
     Move the character according to input
     */
    void move_left();
    void move_right();
    
    Fighter& operator=(const Fighter& other);
    std::vector<Sprite*> animations;
    unsigned currSprite;
    
private:
    entityx::Entity _entity;
    entityx::EntityManager *_manager;
    
    float _moveSpeed;
    StartPosition _startingPosition;
    Direction _facing;
    State _state;
};

#endif /* defined(__The_Kings_Tournament__fighter__) */
