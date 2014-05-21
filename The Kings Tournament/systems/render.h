//
//  render.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__render__
#define __The_Kings_Tournament__render__

#include <iostream>
#include <entityx/entityx.h>
#include <SDL2/SDL.h>

class RenderSystem : public entityx::System<RenderSystem> {
public:
    RenderSystem(SDL_Renderer* ren, SDL_Window *win) : _window(win), _renderer(ren) {}
    
    void update(entityx::EntityManager &es,
                entityx::EventManager &events,
                double dt) override;
private:
    SDL_Renderer* _renderer;
    SDL_Window* _window;
};

#endif /* defined(__The_Kings_Tournament__render__) */
