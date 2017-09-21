#pragma once
#include<string>
#include"Timer.h"
class Application;
struct PhysBody3D;

class Module
{
private :
	bool enabled;

public:


	Module(bool start_enabled = true)
	{}

	virtual ~Module()
	{}

	virtual bool Init() 
	{
		return true; 
	}

	virtual bool Start()
	{
		return true;
	}

	virtual bool Gui_Engine_Modules(float dt)
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}
	virtual void StartTimer() {
		this->module_timer->Start();
		
	};
	virtual void PauseTimer() {
		this->module_timer->Pause();
		
	};
	virtual void ResumeTimer() {
		this->module_timer->Resume();
		
	};
	virtual void StopTimer() {
		this->module_timer->Stop();
		
	}

	virtual void OnCollision(PhysBody3D* body1, PhysBody3D* body2)
	{}
public:
	Timer* module_timer;
	std::string name = "";
	
	float performance[90] = { 0 };
	int performance_offset = 0;
};