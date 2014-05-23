//
//  movement.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__movement__
#define __The_Kings_Tournament__movement__

#include <iostream>
#include <entityx/entityx.h>
#include "playerinput.h"
#include "fighter.h"

struct MovementSystem : public entityx::System<MovementSystem>, entityx::Receiver<MovementSystem> {
public:
    MovementSystem(Fighter *p1) : playerOne(p1) {}
    
    void update(entityx::EntityManager &es,
                entityx::EventManager &events,
                double dt) override;
    
    void configure(entityx::EventManager &event_manager);

    void receive(const PlayerInput &input);
    
private:
    Fighter *playerOne, *playerTwo;
};

#endif /* defined(__The_Kings_Tournament__movement__) */
