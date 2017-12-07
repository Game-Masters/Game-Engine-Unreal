#ifndef RESOURCE_SHADER_OBJECT_H_
#define RESOURCE_SHADER_OBJECT_H_
#include "ModuleAssimp.h"
#include"ModuleResources.h"

enum ShaderType {
	vertex_shader = 0,
	fragment_shader,
	geometry_shader,
	tess_evaluation_shader,
	tess_control_shader,
	no_type_shader
};

class ResourceShaderObject :
	public Resource
{
public:
	ResourceShaderObject();
	ResourceShaderObject(int id);
	ResourceShaderObject(ShaderType Type, const char* filename);
	~ResourceShaderObject();

	bool ComplieShaderObject();
	void Update_Resource();
	bool LoadToMemory();
	GLuint GetID();
	const char* GetFileName();
	void Set_Type_Shader(ShaderType type);
	void ShaderUpdateInstances();
private:
	LCG uid_rm;
	ShaderType shader_obj_type = ShaderType::no_type_shader;
	GLuint id_shader_obj = 0;
	const GLchar* shader_obj_code = nullptr;
	std::string log_shader;

};

#endif