#include "ResourceShaderMaterial.h"
#include"ResourceShaderObject.h"
#include"Application.h"


ResourceShaderMaterial::ResourceShaderMaterial():Resource(uid_rm.Int(), Resources_Type::shader_program)
{
}

ResourceShaderMaterial::ResourceShaderMaterial(int id): Resource(id, Resources_Type::shader_program)
{
}

ResourceShaderMaterial::~ResourceShaderMaterial()
{
}

bool ResourceShaderMaterial::LoadToMemory()
{
	bool ret = false;
	if (loaded == 0) {
		loaded++;
		ret = Link_Program();
		App->json_class->Create_JSON_DOC(&file_proj, &obj_proj, exported_file.c_str());
		JSON_Object* node;
		int i = 0;
		std::string temo_str = "Shader" + std::to_string(i + 1);		
		json_object_get_object(obj_proj, temo_str.c_str());
		for (; i < ShaderObject_Program_v.size(); i++) {
			ResourceShaderObject* temp = (ResourceShaderObject*)App->resources_mod->Get(ShaderObject_Program_v[i]);
			temo_str= "Shader" + std::to_string(i + 1);
			json_object_set_string(obj_proj, temo_str.c_str(), temp->GetExportedFile());
		}

		char* serialized_string = json_serialize_to_string_pretty(file_proj);
		json_serialize_to_file(file_proj, exported_file.c_str());
	}
	else {
		loaded++;
		ret = false;
	}
	return ret;
}

bool ResourceShaderMaterial::Link_Program()
{


	id_program = glCreateProgram();
	if (0 == id_program)
	{
		LOG("Error creating program object.");
		return false;
	}
	if (ShaderObject_Program_v.size() >= 2) {
		for (int i = 0; i < ShaderObject_Program_v.size(); i++) {
			int uuid_temp = ShaderObject_Program_v[i];
			ResourceShaderObject* temp_shader_obj = (ResourceShaderObject*)App->resources_mod->Get(uuid_temp);
			if (temp_shader_obj->GetLoadedNum() > 0) {
				glAttachShader(id_program, temp_shader_obj->GetID());
				LOG("Attached %s shader object", temp_shader_obj->GetFileName());
			}
			else {
				LOG("Error trying to attach %s shader object", temp_shader_obj->GetFileName());
				LOG("The shader object is not compiled");
				return false;
			}
		}
		glLinkProgram(id_program);

		GLint status;
		glGetProgramiv(id_program, GL_LINK_STATUS, &status);

		if (GL_FALSE == status) {
			LOG("Failed to link shader program!");
			GLint logLen;
			glGetProgramiv(id_program, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 0)
			{
				char * log = new char[logLen];
				GLsizei written;
				glGetProgramInfoLog(id_program, logLen, &written, log);
				log_shader = log;
				delete[] log;
			}
			if (log_shader.size() > 0) {
				LOG("Program log: \n%s", log_shader.c_str());
			}
			return false;
		}
		LOG("Program linked");
	}
	else {
		LOG("Program cannot be linked because the program has only one shader attached");
		return false;
	}
	return true;
}

bool ResourceShaderMaterial::Bind_program()
{
	glUseProgram(id_program);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		//LOG("Error binding shader! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

void ResourceShaderMaterial::Unbind_program()
{
	glUseProgram(NULL);
}

void ResourceShaderMaterial::SetShaderObj_Vect(std::vector<int> vec)
{
	ShaderObject_Program_v = vec;
}

const GLuint ResourceShaderMaterial::GetID_program_shader() const
{
	return id_program;
}

const char * ResourceShaderMaterial::GetNameProgram()
{
	return name_program.c_str();
}

std::vector<int> ResourceShaderMaterial::GetShaderObj_UUID() const
{
	return ShaderObject_Program_v;
}

void ResourceShaderMaterial::SetProgram_Name(const char * name)
{
	name_program = name;
}

void ResourceShaderMaterial::GetJsonShaderProgram()
{
	App->json_class->Create_JSON_DOC(&file_proj, &obj_proj, exported_file.c_str());
	for (int i = 0; i < 2; i++) {
		std::string temo_str = "Shader" + std::to_string(i + 1);
		std::string temp_path= json_object_get_string(obj_proj, temo_str.c_str());
		int temp_uid=App->resources_mod->Find_UserRes(temp_path.c_str());
		if (temp_uid != -1) {
			ResourceShaderObject* res_temp = (ResourceShaderObject*)App->resources_mod->Get(temp_uid);
			ShaderObject_Program_v.push_back(res_temp->GetUID());
		}
	}


}