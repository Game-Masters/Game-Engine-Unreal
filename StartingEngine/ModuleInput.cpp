#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Winuser.h"
#include <experimental/filesystem>
#include"ModuleResources.h"
#include"ResourceTexture.h"
#define MAX_KEYS 300

ModuleInput::ModuleInput(bool start_enabled) : Module(start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	dropped_filedir_newGO = "";
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	const aiScene* scene = nullptr;
	std::string path_r;
	Resources_Type type_file = Resources_Type::unknown_r;
	while(SDL_PollEvent(&e))
	{
		ImGui_ImplSdlGL2_ProcessEvent(&e);
		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_QUIT:
			quit = true;
			break;

			case (SDL_DROPFILE): 
				// In case if dropped file
					dropped_filedir = e.drop.file;

		
					type_file=App->resources_mod->DetectFiles_Type(dropped_filedir.c_str());
					if (type_file == Resources_Type::mesh) {
						size_t end_name = dropped_filedir.rfind(".");
						size_t sart_name = dropped_filedir.rfind("\\") + 1;
						std::string name = dropped_filedir.substr(sart_name, dropped_filedir.size());
						std::experimental::filesystem::path p1 = dropped_filedir;
						std::experimental::filesystem::path p2 = App->fs_e->Mesh_User->path+ "\\"+name;
						App->fs_e->ChangeFormat_File(dropped_filedir.c_str(), "ric", &path_r, App->fs_e->Mesh_Engine);
						if (App->fs_e->Find_in_Asset(p1.string().c_str())) {
							std::experimental::filesystem::remove(p1.string().c_str());
						}
						std::experimental::filesystem::copy_file(p1, p2);
					
						if (App->resources_mod->Find_UserRes(p2.string().c_str())==-1) {
							ResourceMesh* temp_mesh_try = (ResourceMesh*)App->resources_mod->CreateNewResource(Resources_Type::mesh);
							temp_mesh_try->Set_New_Resource_Files(path_r.c_str(), p2.string().c_str());
							App->resources_mod->AddResources(temp_mesh_try);
							temp_mesh_try->CreateMeta();
						}

						//App->imp_mesh->LoadMesh(path_r.c_str(), dropped_filedir.c_str());
					}
					if (type_file == Resources_Type::texture) {
						size_t end_name = dropped_filedir.rfind(".");
						size_t sart_name = dropped_filedir.rfind("\\") + 1;
						std::string name = dropped_filedir.substr(sart_name, dropped_filedir.size());
						std::experimental::filesystem::path p1 = dropped_filedir;
						std::experimental::filesystem::path p2 = App->fs_e->Material_User->path + "\\" + name;
						App->fs_e->ChangeFormat_File(dropped_filedir.c_str(), "dds", &path_r, App->fs_e->Material_Engine);
						if (App->fs_e->Find_in_Asset(p2.string().c_str())) {
							std::experimental::filesystem::remove(p2.string().c_str());
						}
						std::experimental::filesystem::copy_file(p1, p2);

						if (App->resources_mod->Find_UserRes(p2.string().c_str()) == -1) {
							ResourceTexture* temp_mesh_try = (ResourceTexture*)App->resources_mod->CreateNewResource(Resources_Type::texture);
							temp_mesh_try->Set_New_Resource_Files(path_r.c_str(), p2.string().c_str());
							App->resources_mod->AddResources(temp_mesh_try);
							temp_mesh_try->CreateMeta();
						}
					}

					
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "File dropped on window", dropped_filedir.c_str(), App->window->window);
					App->imp_mesh->change_nameimporter = 0;
					dropped_filedir = "";
	
				flie_dropped = true;
				// Shows directory of dropped file
				
				break;

			case SDL_WINDOWEVENT:
			{
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					App->renderer3D->OnResize(e.window.data1, e.window.data2);
			}
		}
	}

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

bool ModuleInput::Gui_Engine_Modules(float dt)
{

	if (ImGui::CollapsingHeader(name.c_str()))
	{

		


	}
	return false;
}
