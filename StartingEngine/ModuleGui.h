#ifndef __ModuleGui_H__
#define __ModuleGui_H__

#include "Module.h"
#include "SDL/include/SDL.h"


class Application;

class ModuleGui : public Module
{
public:

	ModuleGui(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleGui();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:
	bool button_exit_app = false;
	bool button_rand = false;
	bool button_rand2 = false;
	int* SliderTest_Int_value = nullptr;
	bool show_gui_engine = false;
	bool n1 = false;
	bool n2 = false;
	LCG rand_test;
	int iop;
	float iop2;
};

#endif // ModuleGui