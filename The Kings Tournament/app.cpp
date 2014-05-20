//
//  app.cpp
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/20/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#include "app.h"

#define APPTITLE "The King's Tournament"

Application::Application(unsigned width, unsigned height) :
    width(width),
    height(height),
    _running(false),
    _paused(false)
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
	
	_window = SDL_CreateWindow(APPTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    return true;
}

void Application::run() {
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;
	
	while (SDL_WaitEvent(&ev))
	{
		onEvent(&ev);
		render();
		
		if (_running == false)
		{
			break;
		}
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
	}
}

void Application::render()
{
	SDL_Rect r;
	int w,h;
	SDL_GetWindowSize(_window, &w, &h);
	
	r.w = 200;
	r.h = 200;
	r.x = w/2-(r.w/2);
	r.y = h/2-(r.h/2);
	
	
	//
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0, 0xff);
	SDL_RenderClear(_renderer);
	
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0, 0xff);
	SDL_RenderFillRect(_renderer, &r);
	SDL_RenderPresent(_renderer);
}
	