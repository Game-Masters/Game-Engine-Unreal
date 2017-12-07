#ifndef SHADERS_MANAGER_H_
#define SHADERS_MANAGER_H_

#include "Module.h"
#include"ShaderProgramObject.h"

class Shaders_Manager :
	public Module
{
public:
	Shaders_Manager();
	~Shaders_Manager();
	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	std::vector<ShaderProgramObject*> shader_program_v;
	GLint projLoc = 0;
	GLint timeloc = 0;
};

#endif // !1