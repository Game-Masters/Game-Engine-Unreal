#include "Application.h"
#include "Glew\include\glew.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui.h"
#include"Imgui\imguidock.h"

Application::Application()
{
	window = new ModuleWindow();
	input = new ModuleInput();
	audio = new ModuleAudio(true);
	scene_intro = new ModuleSceneIntro();
	renderer3D = new ModuleRenderer3D();
	camera = new ModuleCamera3D();
	physics = new ModulePhysics3D();
	player = new ModulePlayer();
	gui = new ModuleGui();
	assimp = new ModuleAssimp();

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);

	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(assimp);
	
	// Scenes
	AddModule(scene_intro);
	AddModule(physics);
	AddModule(player);
	
	// Renderer last!
	AddModule(renderer3D);
	AddModule(gui);



	window->name = "window";
	camera->name = "camera";
	input->name = "input";
	physics->name = "physics";
	renderer3D->name = "renderer3D";
	gui->name = "gui";
	audio->name = "audio";
	player->name = "player";
	scene_intro->name = "scene intro";
	assimp->name = "assimp";

}

Application::~Application()
{
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		RELEASE((*item));
	}

	list_modules.clear();

}

bool Application::Init()
{
	bool ret = true;


	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	

	json_class = new Parson_JSON();
	json_class->Init();
	json_class->Load();


	std::list<Module*>::iterator item = list_modules.begin();
	while (item != list_modules.end() && ret == true)
	{

		ret = (*item)->Init();
		(*item)->module_timer = new Timer();
		item++;
	}

	

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
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
	frame_count++;
	last_sec_frame_count++;

	//IF WE HAVE PROBLEMS UNCOMMENT THIS
	//dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	PrepareUpdate();
	
	


	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->StartTimer();
		(*item)->PreUpdate(dt);
		(*item)->PauseTimer();
	}
	//LOG("%f", 1/dt);
	

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->ResumeTimer();
		(*item)->Update(dt);
		(*item)->PauseTimer();
	}

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->ResumeTimer();
		ret = (*item)->PostUpdate(dt);
		(*item)->StopTimer();
		if (ret == update_status::UPDATE_ERROR || ret == update_status::UPDATE_STOP)
			break;
	}
	// Framerate calculations --
	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	avg_fps = float(frame_count) / startup_time.ReadSec();
	seconds_since_startup = startup_time.ReadSec();
	last_frame_ms = frame_time.Read();
	frames_on_last_update = prev_last_sec_frame_count;



	if (capped_ms > 0 && (int)last_frame_ms < capped_ms)
	{
		j1PerfTimer t;
		SDL_Delay(capped_ms - last_frame_ms);
		LOG("We waited for %d milliseconds and got back in %f", capped_ms - last_frame_ms, t.ReadMs());
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->CleanUp();
	}
	json_class->Save();
	
	return ret;
}

bool Application::Gui_Engine_Modules(float dt)
{
	if (ImGui::BeginDock("Application", false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {

		std::list<Module*>::iterator item = App->list_modules.begin();

		while (item != App->list_modules.end())
		{

			const char* name = (*item)->name.c_str();

			(*item)->performance[(*item)->performance_offset] = (*item)->module_timer->Read_ms();
			(*item)->performance_offset = ((*item)->performance_offset + 1) % IM_ARRAYSIZE((*item)->performance);

			ImGui::PlotHistogram((char*)name, (*item)->performance, IM_ARRAYSIZE((*item)->performance), 0, name, 0.0f, 30.f, ImVec2(0, 40));
			item++;
		}
	}
	ImGui::EndDock();
	return true;
}

void Application::LoadModules()
{



}

void Application::SaveModules()
{
}

void Application::AddModule(Module* mod)
{

	list_modules.push_back(mod);
}