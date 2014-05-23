//
//  render.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/21/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "render.h"
#include "appearance.h"
#include "position.h"
#include "size.h"

void RenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, double dt) {
    // CLEAR THE RENDERER
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0, 0xff);
	SDL_RenderClear(_renderer);
    
	int w,h;
	SDL_GetWindowSize(_window, &w, &h);
    
    for (auto entity : es.entities_with_components<Appearance, Size, Position>()) {
        entityx::ComponentHandle<Appearance> appearance = entity.component<Appearance>();
        entityx::ComponentHandle<Size> size = entity.component<Size>();
        entityx::ComponentHandle<Position> pos = entity.component<Position>();
        
        SDL_Surface *render_surface = appearance->render(dt);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(_renderer, render_surface);
        if (tex == nullptr){
            std::cout << "SDL_CreateTextureFromSurface Error: "
            << SDL_GetError() << std::endl;
        }
        SDL_Rect target; target.w = size->width; target.h = size->height; target.x = pos->x; target.y = (float)h - pos->y;
        SDL_RenderCopy(_renderer, tex, NULL, &target);
    }
}