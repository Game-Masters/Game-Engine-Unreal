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
#include "ModuleGui.h"
#include "ModuleAssimp.h"
#include "Parson_JSON.h"
#include"Parson_JSON.h"
#include"ModuleFileSystem_Engine.h"
#include"ModuleResources.h"
#include"Shaders_Manager.h"
#include <list>
#include <vector>
#include "Geometry.h"
#include "../StartingEngine/Assimp/include/assimp/cimport.h"
#include "../StartingEngine/Assimp/include/assimp/scene.h"
#include "../StartingEngine/Assimp/include/assimp/postprocess.h"
#include "../StartingEngine/Assimp/include/assimp/cfileio.h"

#pragma comment (lib, "../StartingEngine/Assimp/include/libx86/assimp.lib")

enum TimeState
{
	play,
	pause,
	stop
};
class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	Shaders_Manager* shaders_manager;
	ModuleGui* gui;
	ModuleFileSystem_Engine* fs_e;
	ModuleAssimp* assimp;
	ModuleResources* resources_mod;
	//----
	Parson_JSON* json_class;
	MaterialImporter* imp_mat = nullptr;
	MeshImporter* imp_mesh = nullptr;
	bool NextFrame = false;
private:

	Timer	ms_timer;
	float play_timer = 0;
	float continue_timer = 0;
	float	dt;
	float	dtvariation = 0;
	float	tempdt = 1;
	
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
	bool Gui_Engine_Modules(float dt);
	std::list<Module*> list_modules;
	Uint32				frames_on_last_update = 0;
	void LoadModules();
	void SaveModules();
	void SetFramesCapped(int cap_temp);
	int GetFramesCapped();
	void Play();
	void Pause();
	void Stop();
	void DtSwitch();
	void ReStartScene();
	void StartPlayingScene();
	TimeState timeStatus = TimeState::stop;
	float GetPlay_Time()const;
private:
	float performance[90] = { 0 };
	int performance_offset = 0;
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	
};

extern Application* App;