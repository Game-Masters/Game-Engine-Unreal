#ifndef OBJECT_SHADER_H
#define OBJECT_SHADER_H
#include<string>
#include"Glew\include\glew.h"

enum ShaderType {
	vertex_shader=0,
	fragment_shader,
	geometry_shader,
	tess_evaluation_shader,
	tess_control_shader,
	no_type_shader
};

class ShaderObject
{
public:
	ShaderObject();
	ShaderObject(ShaderType Type, const char* filename, const GLchar * Shader_obj_code);
	~ShaderObject();
	bool CompileShader();
	GLuint GetID();
	const char* GetFileName();
	bool IsCompiled();
private:

	ShaderType shader_obj_type = ShaderType::no_type_shader;
	GLuint id_shader_obj = 0;
	const GLchar* shader_obj_code = nullptr;
	std::string file_name_shader;
	std::string log_shader;
	bool compiled = false;
};

#endif // !
