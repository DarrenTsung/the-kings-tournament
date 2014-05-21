//
//  app.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/20/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "app.h"
#include <SDL2/SDL_Timer.h>
#include <sstream>
#include <unistd.h>

#define APPTITLE "The King's Tournament"
#define FPS 60.0f

#define DEBUG_MODE true



Application::Application(unsigned width, unsigned height) :
    width(width),
    height(height),
    _running(false),
    _paused(false),
    _debugMode(DEBUG_MODE)
{
    
}

Application::~Application() {
	if (_window)
	{
		SDL_DestroyWindow(_window);
		SDL_DestroyRenderer(_renderer);
		SDL_Quit();
	}
}

bool Application::initialize() {
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return false;
	}
    
    if (TTF_Init() < 0)
    {
		fprintf(stderr, "TTF_Init() failed: %s\n", TTF_GetError());
        return false;
    }
	
	_window = SDL_CreateWindow(APPTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return true;
}

void Application::run() {
	// Enter to the SDL event loop.
	SDL_Event event;
	_running = true;
    
    float delta = 1.0f/FPS, curr_time, prev_time = SDL_GetTicks();
	
    // Game loop
	while (_running)
	{
        // ============================================================================
        // EVENT HANDLING
        // ============================================================================
        while( SDL_PollEvent(&event) ) onEvent(&event);
        
        // ============================================================================
        // UPDATE LOGIC
        // ============================================================================
        update(delta);
        // ============================================================================
        // RENDERING
        // ============================================================================
		render();
        
        // ============================================================================
        // TIMING
        // ============================================================================
        // cap the frame rate at a steady FPS frames per second
        curr_time = SDL_GetTicks();
        // wait out the rest of the extra time
        while (curr_time - prev_time < 1000.0f/FPS) {
            curr_time = SDL_GetTicks();
        }
        // time is in milliseconds
        delta = (curr_time - prev_time) / 1000.0f;
        _fps = 1.0f/delta;
        prev_time = curr_time;
    }
}

void Application::onEvent(SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_QUIT:
			_running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if (event->key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
		}
            
            case SDL_KEYUP:
        {
            
        }
	}
}

void Application::update(float delta) {
    
}

void Application::render()
{
    // CLEAR THE RENDERER
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0, 0xff);
	SDL_RenderClear(_renderer);
    
	int w,h;
	SDL_GetWindowSize(_window, &w, &h);
    
    // if the debugMode is on and there is an fps, display it
    if (_debugMode && _fps) {
        TTF_Font *font = TTF_OpenFont("bitfont.TTF", 12);
        if(!font) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            // handle error
        }
        SDL_Color blackFontColor = {255, 255, 255};
        char fps_string[15];
        sprintf(fps_string, "FPS: %.1f", _fps);
        SDL_Surface *fps_surface = TTF_RenderText_Solid(font, fps_string, blackFontColor);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(_renderer, fps_surface);
        SDL_FreeSurface(fps_surface);
        SDL_RenderClear(_renderer);
        SDL_Rect target; target.w = 80; target.h = 30; target.x = 10; target.y = height - target.h - 5;
        SDL_RenderCopy(_renderer, tex, NULL, &target);
    }
    
	SDL_Rect r;
	r.w = 200;
	r.h = 200;
	r.x = w/2-(r.w/2);
	r.y = h/2-(r.h/2);
	
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0, 0xff);
	SDL_RenderFillRect(_renderer, &r);
	SDL_RenderPresent(_renderer);
}
	