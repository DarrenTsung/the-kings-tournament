//
//  app.h
//  The Kings Tournament
//
//  Created by Darren Tsung on 5/20/14.
//  Copyright (c) 2014 Lambawoof. All rights reserved.
//

#ifndef __The_Kings_Tournament__app__
#define __The_Kings_Tournament__app__

#include <SDL2/SDL.h>
#include <iostream>

struct Keys {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

/**
 The application class takes care of handling the key inputs and creating a managment system for the game
 */
class Application {
public:
    // constructor
    Application(unsigned width, unsigned height);
    ~Application();
    
    // initialize SDL and create rendering environment, returns true if success, false if failure
    bool initialize();
    
    // runs the application
    void run();
    
    // items that other objects will need to access
    unsigned width, height;
    Keys keystate;
    
private:
    // handle key events
    void onEvent(SDL_Event *event);
    // draw the application
    void render();
    
	SDL_Window *_window;
	SDL_Renderer *_renderer;
    
    bool _running, _paused;
};

#endif /* defined(__The_Kings_Tournament__app__) */
