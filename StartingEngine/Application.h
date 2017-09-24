#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModulePlayer.h"
#include "ModuleGui.h"
#include "Parson_JSON.h"
#include"Parson_JSON.h"
#include <list>
#include <vector>
class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	ModulePlayer* player;
	ModuleGui* gui;



	//----
	Parson_JSON* json_class;

private:

	Timer	ms_timer;
	float	dt;
	//p2List<Module*> list_modules;
	j1PerfTimer			ptimer;
	unsigned int long	frame_count = 0;
	Timer				startup_time;
	Timer				frame_time;
	Timer				last_sec_frame_time;
	Uint32				last_sec_frame_count = 0;
	Uint32				prev_last_sec_frame_count = 0;
//	float				dt = 0.0f;
	int					capped_ms = -1;
	float				avg_fps = 0.0f;
	float				seconds_since_startup = 0.0f;
	Uint32				last_frame_ms = 0;
	

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	std::list<Module*> list_modules;
	Uint32				frames_on_last_update = 0;
	void LoadModules();
	void SaveModules();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;