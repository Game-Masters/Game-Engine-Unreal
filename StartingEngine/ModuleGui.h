#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include"Console_ImGui.h"
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

public:
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
	//
	Console console_imgui;
	LCG rand_test;
	int iop;
	float iop2;
};

#endif // ModuleGui