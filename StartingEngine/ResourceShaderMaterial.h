#ifndef RESOURCE_SHADER_MATERIAL_H_
#define RESOURCE_SHADER_MATERIAL_H_
#include"ModuleResources.h"
#include<vector>
#include "ModuleAssimp.h"
#include"JSON\parson.h"

class ResourceShaderMaterial: public Resource
{
public:
	ResourceShaderMaterial();
	ResourceShaderMaterial(int id);
	~ResourceShaderMaterial();
	bool LoadToMemory();
	bool Link_Program();
	bool Bind_program();
	void Unbind_program();
	void SetShaderObj_Vect(std::vector<int> vec);
	const GLuint GetID_program_shader() const;
	const char* GetNameProgram();
	std::vector<int> GetShaderObj_UUID() const;
	void SetProgram_Name(const char* name);
	void GetJsonShaderProgram();
private:
	LCG uid_rm;
	std::vector<int> ShaderObject_Program_v;
	GLuint id_program = 0;
	bool linked_program = false;
	std::string log_shader;
	std::string name_program;
	JSON_Object* obj_proj;
	JSON_Value* file_proj;
};
#endif // !1