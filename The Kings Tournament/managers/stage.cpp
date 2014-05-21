//
//  stage.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "stage.h"
#include "movement.h"
#include "render.h"
#include "app.h"

Stage::Stage() {}

Stage::Stage(Application *myApp) :
    app(myApp)
{
    
}

void Stage::start() {
    configure();
    systems.configure();
    initialize();
}

void Stage::configure() {
    systems.add<MovementSystem>();
    systems.add<RenderSystem>(app->_renderer, app->_window);
}

void Stage::initialize() {
    playerOne = Fighter(LEFT);
    playerOne.initialize(&entities, &events);
}

void Stage::update(double dt) {
    systems.update<MovementSystem>(dt);
    systems.update<RenderSystem>(dt);
    
    playerOne.update(dt);
}

Stage& Stage::operator=(const Stage &other) {
    app = other.app;
    return *this;
}
