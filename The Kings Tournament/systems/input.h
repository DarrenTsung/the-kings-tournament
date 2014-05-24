//
//  input.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__input__
#define __The_Kings_Tournament__input__

#include <iostream>
#include <entityx/entityx.h>
#include "app.h"

class InputSystem : public entityx::System<InputSystem> {
public:
    InputSystem(Application *app, Fighter *p1) : _app(app), playerOne(p1), _p1disabled(false), _p2disabled(false) {}
    
    void update(entityx::EntityManager &es,
                entityx::EventManager &events,
                double dt) override;
    
    bool _p1disabled, _p2disabled;
    
private:
    Fighter *playerOne, *playerTwo;
    
    Application *_app;
};

#endif /* defined(__The_Kings_Tournament__input__) */
