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

class MovementSystem : public entityx::System<MovementSystem> {
    public:
        MovementSystem() {}
        
        void update(entityx::EntityManager &es,
                    entityx::EventManager &events,
                    double dt) override;
};

#endif /* defined(__The_Kings_Tournament__movement__) */
