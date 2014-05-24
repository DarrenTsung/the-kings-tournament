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
#include "helper.h"

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
    _stage = Stage(this);
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
    
    // open the font
    debug_font = TTF_OpenFont("bitfont.TTF", 12);
    if(!debug_font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
	
	_window = SDL_CreateWindow(APPTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    _stage.start();
    return true;
}

void Application::run() {
	// Enter to the SDL event loop.
	SDL_Event event;
	_running = true;
    
    double delta = 1.0f/FPS, curr_time, prev_time = SDL_GetTicks();
	
    // Game loop
	while (_running)
	{
        // EVENT HANDLING
        while( SDL_PollEvent(&event) ) onEvent(&event);
        
        // UPDATING
        _stage.update(delta);
        // RENDERING
        render();
        
        // TIMING
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
			switch (event->key.keysym.sym)
            {
                case SDLK_ESCAPE:
    				_running = false;
                    break;
                case SDLK_w:
                    keystate.up = true;
                    break;
                case SDLK_s:
                    keystate.down = true;
                    break;
                case SDLK_d:
                    keystate.right = true;
                    break;
                case SDLK_a:
                    keystate.left = true;
                    break;
                case SDLK_k:
                    keystate.heavy = true;
                    break;
                case SDLK_j:
                    keystate.light = true;
                    break;
            }
            break;
		}
            
        case SDL_KEYUP:
        {
			switch (event->key.keysym.sym)
            {
                case SDLK_w:
                    keystate.up = false;
                    break;
                case SDLK_s:
                    keystate.down = false;
                    break;
                case SDLK_d:
                    keystate.right = false;
                    break;
                case SDLK_a:
                    keystate.left = false;
                    break;
                case SDLK_k:
                    keystate.heavy = false;
                    break;
                case SDLK_j:
                    keystate.light = false;
                    break;
            }
            break;
        }
	}
}

void Application::update(float delta) {
    
}

void Application::render()
{
    // if the debugMode is on and there is an fps, display it
    if (_debugMode && _fps) {
        char fps_string[15];
        sprintf(fps_string, "FPS: %.1f", _fps);
        SDL_Surface *fps_surface = helper::SurfaceForFontAndString(debug_font, std::string(fps_string), {255, 255, 255});
        SDL_Texture *tex = SDL_CreateTextureFromSurface(_renderer, fps_surface);
        SDL_FreeSurface(fps_surface);
        SDL_Rect target; target.w = 95; target.h = 30; target.x = 10; target.y = height - target.h - 5;
        SDL_RenderCopy(_renderer, tex, NULL, &target);
    }
	SDL_RenderPresent(_renderer);
}
	