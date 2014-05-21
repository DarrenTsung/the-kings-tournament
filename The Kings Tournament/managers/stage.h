//
//  stage.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__stage__
#define __The_Kings_Tournament__stage__

#include <iostream>
#include <entityx/entityx.h>
#include "fighter.h"

class Application;

class Stage : public entityx::EntityX {
public:
    Stage();
    Stage(Application *myApp);
    
    void start();
    void update(double dt);
    
    // copy constructor
    Stage& operator =(const Stage& other);
    
protected:
    void configure();
    void initialize();
    
private:
    Application *app;
    Fighter playerOne;
};

#endif /* defined(__The_Kings_Tournament__stage__) */
