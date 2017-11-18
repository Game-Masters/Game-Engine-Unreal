#include "Application.h"
#include "Glew\include\glew.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui.h"
#include"Imgui\imguidock.h"
#include"Quadtree.h"

Application::Application()
{
	window = new ModuleWindow();
	input = new ModuleInput();
	audio = new ModuleAudio(true);
	scene_intro = new ModuleSceneIntro();
	renderer3D = new ModuleRenderer3D();
	camera = new ModuleCamera3D();
	gui = new ModuleGui();
	assimp = new ModuleAssimp();
	fs_e = new ModuleFileSystem_Engine();
	resources_mod = new ModuleResources();
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(fs_e);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(assimp);
	AddModule(resources_mod);
	// Scenes
	AddModule(scene_intro);


	
	// Renderer last!
	AddModule(renderer3D);
	AddModule(gui);



	window->name = "window";
	fs_e->name = "filesystem";
	camera->name = "camera";
	input->name = "input";

	renderer3D->name = "renderer3D";
	gui->name = "gui";
	audio->name = "audio";

	scene_intro->name = "scene intro";
	assimp->name = "assimp";
	resources_mod->name = "resources_manager";
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
	
	imp_mat = new MaterialImporter();
	imp_mesh = new MeshImporter();
	json_class = new Parson_JSON();
	json_class->Init();
	json_class->Load();
	ImGui::LoadDocks();


	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		ret = (item)._Ptr->_Myval->Init();
		(item)._Ptr->_Myval->module_timer = new Timer();

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

	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

void Application::SetFramesCapped(int cap_temp)
{
	capped_ms = cap_temp;
}

int Application::GetFramesCapped()
{
	return capped_ms;
}

void Application::Play()
{
	timeStatus = play;
	play_timer = 0;
	DtSwitch();
}

void Application::Pause()
{
	timeStatus = pause;
	DtSwitch();
}

void Application::Stop()
{
	timeStatus = stop;
	play_timer = 0;
	DtSwitch();
}

void Application::DtSwitch()
{
	if (timeStatus == play)
	{
		dtvariation = tempdt;
		StartPlayingScene();
	}
	if (timeStatus == pause)
	{
		tempdt = dtvariation;
		dtvariation = 0.0f;
	}
	if (timeStatus == stop)
	{
		tempdt = dtvariation;
		dtvariation = 0.0f;
		ReStartScene();
	}
}

void Application::ReStartScene()
{
	App->gui->inspection_node = nullptr;
	App->scene_intro->num_GO = 0;
	App->scene_intro->root_gameobject->CleanUp();
	App->json_class->Create_JSON_DOC(&App->scene_intro->root_value_scene, &App->scene_intro->root_object_scene,"..\\Game\\Library\\TempPlay");
	App->scene_intro->Load_Scene(App->scene_intro->root_object_scene);
	App->scene_intro->calc_octree_stop_button = true;

}

void Application::StartPlayingScene()
{
	App->json_class->Create_JSON_DOC(&App->scene_intro->root_value_scene, &App->scene_intro->root_object_scene, "..\\Game\\Library\\TempPlay");
	json_object_clear(App->scene_intro->root_object_scene);
	App->scene_intro->root_gameobject->Save(App->scene_intro->root_object_scene);
	char* serialized_string = json_serialize_to_string_pretty(App->scene_intro->root_value_scene);
	json_serialize_to_file(App->scene_intro->root_value_scene, "..\\Game\\Library\\TempPlay");
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	PrepareUpdate();
	
	//change dt time
	float tempdt = dt * dtvariation;
	if (NextFrame)
	{
		tempdt = dt;
		NextFrame = false;
	}
	//



	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->StartTimer();
		if ((*item) == camera)
		{
			(*item)->PreUpdate(dt);
		}
		else {
			(*item)->PreUpdate(tempdt);
		}
		(*item)->PauseTimer();
	}
	//LOG("%f", 1/dt);
	

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->ResumeTimer();
		if ((*item) == camera)
		{
			(*item)->Update(dt);
		}
		else {
			(*item)->Update(tempdt);
		}
		(*item)->PauseTimer();
		
	}
	if (timeStatus == play)
	{
		play_timer += tempdt;
	}
	
	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->ResumeTimer();
		if ((*item) == camera)
		{
			ret = (*item)->PostUpdate(dt);
		}
		else {
			ret = (*item)->PostUpdate(tempdt);
		}
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


	if (capped_ms > 0)
	{
		uint cap = 1000 / capped_ms;
		if (last_frame_ms < cap)
			SDL_Delay(cap - last_frame_ms);
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		delete (item)._Ptr->_Myval->module_timer;
	}

	for (std::list<Module*>::iterator item = list_modules.begin(); item != list_modules.end(); ++item) {
		(*item)->CleanUp();
	}
	json_class->Save();
	json_class->CleanUp();
	ImGui::SaveDocks();
	App->imp_mat->Mat_Map.clear();
	delete imp_mat;
	delete imp_mesh;

	delete json_class;
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


	const char* name = "fps";

	this->performance[this->performance_offset] = App->frames_on_last_update;
	this->performance_offset = (this->performance_offset + 1) % IM_ARRAYSIZE(this->performance);

	ImGui::PlotHistogram((char*)name, this->performance, IM_ARRAYSIZE(this->performance), 0, name, 0.0f, 150.f, ImVec2(0, 40));
	int temp_cap = capped_ms;
	if (ImGui::InputInt("Fps capped:", &temp_cap, -1, 100, ImGuiInputTextFlags_EnterReturnsTrue)) {
		capped_ms = temp_cap;
	}
	ImGui::SliderFloat("dt", &dtvariation ,0.0f, 10.0f);
	;
	ImGui::Text("Time Since Startup: %f", play_timer);
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