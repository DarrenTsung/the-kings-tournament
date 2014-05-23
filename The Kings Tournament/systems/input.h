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
    InputSystem(Application *app) : _app(app) {}
    
    void update(entityx::EntityManager &es,
                entityx::EventManager &events,
                double dt) override;
private:
    Application *_app;
};

#endif /* defined(__The_Kings_Tournament__input__) */
