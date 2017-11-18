#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include"Console_ImGui.h"
#include "Fluid_Studios_Memory_Manager\mmgr.h"
#include "Fluid_Studios_Memory_Manager\nommgr.h"
#include"ModuleFileSystem_Engine.h"
#define IM_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))
class Application;

class ModuleGui : public Module
{
public:

	ModuleGui(bool start_enabled = true);

	// Destructor
	virtual ~ModuleGui();
	bool Init();
	
	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool Gui_Engine_Modules(float dt);
	bool CleanUp();
	void InspectionNode_Gui();
	void CreateButtonWithTextAndImage(GLuint temp, const char* str);
public:
	sMStats Gpu_Vram_Stats;
	bool button_exit_app = false;
	bool button_rand = false;
	bool button_rand2 = false;
	int* SliderTest_Int_value = nullptr;
	bool show_gui_engine = false;
	bool show_performance = false;
	bool show_console = false;
	bool n1 = false;
	bool n2 = false;
	bool n3 = false;
	bool n4 = false;
	std::vector<float> frames_on_last_update;
	ImGuiStyle style_custom;
	//ICONS
		GLuint P;
		GLuint WF;
		GLuint N;
		GLuint SM;
		GLuint CC;
		GLuint BFC;
		GLuint CA;
		GLuint Q;
		GLuint Logo;
		GLuint Icon;
		GLuint Dani;
		GLuint Nico;
		GLuint Play;
		GLuint Pause;
		GLuint NextFrame;
		GLuint Stop;
	//
	Console console_imgui;
	LCG rand_test;
	int iop;
	float iop2;
	bool show_editor = true;

	void IterateChilds(GameObject* item);
	bool create_empty_gameobject = false;
	bool win_choose_fbx = false;
	bool win_choose_img = false;
	bool world_focused = false;
	bool assets_dock_focus = false;
	bool Octree_Window = false;
	bool createnew = false;

	std::string str_path_fbx;
	std::string str_path_img;
	int num_f = 0;
	char filename_save[64] = { 0 };
	char* str_geom_user;
	char* str_text_user;
	std::string name_gameobject = "";
	float3 pos_gameobject = { 0,0,0 };
	float3 scale_gameobject = { 0,0,0 };
	Quat rotation_gameobject = { 1,0,0,0 };
	std::string Imp_Path;
	std::string full_path;
	GameObject* inspection_node = nullptr;
	std::string path_to_load = "-1";
	std::string Current_Dir;
};

#endif // ModuleGui