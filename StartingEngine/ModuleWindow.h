#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();
	bool Gui_Engine_Modules(float dt);
	void SetTitle(const char* title);

public:
	//The window we'll be rendering to
	SDL_Window* window;
	char str_p[64] = { 0 };
	//The surface contained by the window
	SDL_Surface* screen_surface;
	bool fullscreen_bool = false;
	bool fullscreen_desktop_bool = false;
};

#endif // __ModuleWindow_H__