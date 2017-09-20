#include "Application.h"
#include "Glew\include\glew.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui\imgui.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	physics = new ModulePhysics3D(this);
	player = new ModulePlayer(this);
	gui = new ModuleGui(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);

	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	
	
	// Scenes
	AddModule(scene_intro);
	AddModule(physics);
	AddModule(player);
	AddModule(gui);
	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		RELEASE((*item));
	}

	list_modules.clear();

}

bool Application::Init()
{
	bool ret = true;


	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	glewInit();
	ImGui_ImplSdlGL3_Init(window->window);
	ImGuiIO& io{ ImGui::GetIO() };

	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		(*item)->Start();
	}
	
	

	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	ImGui_ImplSdlGL3_NewFrame(window->window);
	PrepareUpdate();
	
	


	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		(*item)->PreUpdate(dt);
	}

	ImGui::Begin("Info");
	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		(*item)->Gui_Engine_Modules(dt);
	}
	ImGui::End();

	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		(*item)->Update(dt);
	}

	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		ret = (*item)->PostUpdate(dt);
		if (ret == update_status::UPDATE_ERROR || ret == update_status::UPDATE_STOP)
			break;
	}
	

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (std::list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.crend(); ++item) {
		(*item)->CleanUp();
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	mod->Init();
	list_modules.push_back(mod);
}