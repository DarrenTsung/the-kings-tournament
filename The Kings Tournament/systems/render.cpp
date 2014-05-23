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
        
        appearance->update(dt);
        SDL_Texture *tex = appearance->texture();
        SDL_Rect srcTarget = appearance->rect();
        SDL_Rect destTarget;
        destTarget.w = srcTarget.w; destTarget.h = srcTarget.h;
        destTarget.x = pos->x; destTarget.y = (float)h - pos->y;
        SDL_RenderCopy(_renderer, tex, &srcTarget, &destTarget);
    }
}