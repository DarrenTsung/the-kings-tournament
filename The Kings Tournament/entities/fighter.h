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
#include <map>
#include "sprite.h"

enum StartPosition {
    LEFT = 0,
    RIGHT = 1
};

enum class Direction { LEFT, RIGHT };
enum class State { IN_AIR, GROUND };

enum class Animation {
    IDLE,
    WALK,
    BACKWALK,
    STRAIGHT
};

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
     Input functions
     */
    void move_left();
    void move_right();
    void straight();
    
    void set_idle();
    
    
    // gets the sprite instance currently playing
    Sprite* currentSprite();
    
    Fighter& operator=(const Fighter& other);
    Animation currentAnimation;
    
private:
    void switchAnimation(Animation animationToSwitchTo);
    entityx::Entity _entity;
    entityx::EntityManager *_manager;
    
    // maps animations to their id (key) to the sprite
    std::map<std::pair<Animation, Direction>, Sprite*> _animationMap;
    
    bool _inputDisabled;
    float _moveSpeed;
    StartPosition _startingPosition;
    Direction _facing;
    State _state;
};

#endif /* defined(__The_Kings_Tournament__fighter__) */
