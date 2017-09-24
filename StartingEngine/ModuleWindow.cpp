#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Glew\include\glew.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui\imgui.h"
#include"JSON\parson.h"
ModuleWindow::ModuleWindow(bool start_enabled) : Module(start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window

		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	//Lock the cursor on screen 
	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetWindowGrab(window, SDL_TRUE);


	

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

bool ModuleWindow::Gui_Engine_Modules(float dt)
{

	if (ImGui::CollapsingHeader("Windows"))
	{
		//Button to change the name of the window
		ImGui::InputText("Name of the window", str_p, 64);
		str_window = str_p;
		SetTitle(str_window.c_str());
		ImGui::Checkbox("Fullscreen", &fullscreen_bool);
		if (fullscreen_bool) {
			//SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN);
			LOG("Fullscreen mode applicated");
		}
		ImGui::Checkbox("Fullscreen desktop ", &fullscreen_desktop_bool);
		if (fullscreen_desktop_bool) {
			//SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			LOG("Fullscreen Desktop mode applicated");
		}

		int display_count = 0, display_index = 0, mode_index = 0;
		SDL_DisplayMode mode = { SDL_PIXELFORMAT_UNKNOWN, 0, 0, 0, 0 };

		if (SDL_GetDisplayMode(display_index, mode_index, &mode) != 0) {
			SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
			return 1;
		}
		SDL_Log("SDL_GetDisplayMode(0, 0, &mode):\t\t%i bpp\t%i x %i",
			SDL_BITSPERPIXEL(mode.format), mode.w, mode.h);


		ImGui::Text("Number of Displays:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", SDL_GetNumVideoDisplays());
		ImGui::Text("Refresh rate:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", mode.refresh_rate);

		
		ImGui::InputText("Window Width", str_w, 64, ImGuiInputTextFlags_CharsDecimal);
		win_width=std::atoi(str_w);

		ImGui::InputText("Window Height", str_h, 64, ImGuiInputTextFlags_CharsDecimal);
		win_height = std::atoi(str_h);
		
		if (ImGui::Button("Save win config")) {
			SDL_SetWindowSize(window, win_width, win_height);
		}

	}

	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

bool ModuleWindow::LoadConfig(JSON_Object * node)
{
	if (json_object_get_value(node, "height") == NULL) {
		json_object_set_value(node, "height", json_value_init_object());
		win_height = SCREEN_HEIGHT*SCREEN_SIZE;
		json_object_set_number(node, "height", win_height);
	}
	else {
		win_height = json_object_get_number(node, "height");
	}

	if (json_object_get_value(node, "width") == NULL) {
		json_object_set_value(node, "width", json_value_init_object());
		win_width = SCREEN_WIDTH*SCREEN_SIZE;
		json_object_set_number(node, "width", win_width);
	}
	else {
		win_width = json_object_get_number(node, "width");
	}
	//str_window




	return true;
}

bool ModuleWindow::SaveConfig(JSON_Object * node)
{

	json_object_set_number(node, "width", win_width);
	json_object_set_number(node, "height", win_height);

	return true;
}

update_status ModuleWindow::PreUpdate(float dt)
{
	SDL_GetWindowSize(window, &win_width, &win_height);

	return update_status::UPDATE_CONTINUE;
}
