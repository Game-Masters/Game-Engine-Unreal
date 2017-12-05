#ifndef SHADER_PROGRAM_OBJECT_H_
#define SHADER_PROGRAM_OBJECT_H_
#include"Globals.h"

#include<vector>
#include "ModuleAssimp.h"

class ShaderProgramObject
{
public:
	ShaderProgramObject();
	ShaderProgramObject(std::vector<int> id_all_shader_object);
	~ShaderProgramObject();
	bool Link_Program();
	bool Bind_program();
	void Unbind_program();
private:

	std::vector<int> ShaderObject_Program_v;
	GLuint id_program=0;
	bool linked_program = false;
	std::string log_shader;
};
#endif
