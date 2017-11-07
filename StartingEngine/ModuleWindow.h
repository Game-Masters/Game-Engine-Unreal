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
	bool LoadConfig(JSON_Object* node);
	bool SaveConfig(JSON_Object* node);
	update_status PreUpdate(float dt);

public:
	//The window we'll be rendering to
	SDL_Window* window;
	char str_p[64] = { 0 };
	char str_w[64] = { 0 };
	char str_h[64] = { 0 };
	float GetAspect_Ratio();
	//The surface contained by the window
	SDL_Surface* screen_surface;
	bool fullscreen_bool = false;
	bool fullscreen_desktop_bool = false;
	std::string str_window;
	int win_width, win_height;
};

#endif // __ModuleWindow_H__