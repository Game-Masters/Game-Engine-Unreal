#include "ResourceShaderObject.h"
#include"Application.h"


ResourceShaderObject::ResourceShaderObject():Resource(uid_rm.Int(), Resources_Type::shader_obj)
{
}

ResourceShaderObject::ResourceShaderObject(int id) : Resource(id, Resources_Type::shader_obj)
{
}



ResourceShaderObject::ResourceShaderObject(ShaderType Type, const char* filename):Resource(uid_rm.Int(), Resources_Type::shader_obj),	shader_obj_type(Type)
{
	std::string str;
	if (Type == ShaderType::vertex_shader) {
		App->fs_e->ChangeFormat_File(filename, "vert", &str, App->fs_e->Shader_User);
	}
	if (Type == ShaderType::fragment_shader) {
		App->fs_e->ChangeFormat_File(filename, "frag", &str, App->fs_e->Shader_User);
	}
	this->exported_file = str;
}


ResourceShaderObject::~ResourceShaderObject()
{
}



bool ResourceShaderObject::LoadToMemory()
{
	bool ret = false;
	if (loaded == 0) {
		loaded++;
		ret=ComplieShaderObject();
	}
	else {
			loaded++;
			ret = false;
	}
	return ret;	
}


bool ResourceShaderObject::ComplieShaderObject()
{

	char* buffer = nullptr;

	int size_file = App->fs_e->LoadFile(this->exported_file.c_str(), &buffer,true);
	buffer[size_file] = '\0';
	shader_obj_code = buffer;

	switch (shader_obj_type) {
	case ShaderType::vertex_shader:
		id_shader_obj = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::fragment_shader:
		id_shader_obj = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	LOG("Creating %s shader.", this->exported_file.c_str());

	if (0 == id_shader_obj)
	{
		LOG("Error creating %s shader.", this->exported_file.c_str());
		return false;
	}


	//Creating Shader source
	glShaderSource(id_shader_obj, 1, &shader_obj_code, NULL);

	//Compiling Shader
	glCompileShader(id_shader_obj);
	LOG("Compiling %s shader.", this->exported_file.c_str());

	//Success compilation?
	GLint result;
	glGetShaderiv(id_shader_obj, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result)
	{
		LOG("Error compiling %s shader", this->exported_file.c_str());
		GLint logLen;
		//Error in?
		glGetShaderiv(id_shader_obj, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(id_shader_obj, logLen, &written, log);
			log_shader = log;
			delete[] log;

		}
		if (log_shader.size() > 0) {
			LOG("Shader log: %s", log_shader.c_str());
		}
		return false;

	}
	return true;
}

void ResourceShaderObject::Update_Resource()
{
	glDeleteShader(id_shader_obj);
	//RELEASE(shader_obj_code);
	ComplieShaderObject();
	ShaderUpdateInstances();

}

GLuint ResourceShaderObject::GetID()
{
	return id_shader_obj;
}

const char * ResourceShaderObject::GetFileName()
{
	return this->exported_file.c_str();
}

void ResourceShaderObject::Set_Type_Shader(ShaderType type)
{
	shader_obj_type = type;
}

void ResourceShaderObject::ShaderUpdateInstances()
{
	std::vector<Resource*> temp_V = App->resources_mod->Get_TypeResources(Resources_Type::shader_program);
	for (int i = 0; i < temp_V.size();i++) {
		ResourceShaderMaterial* temp= (ResourceShaderMaterial*)temp_V[i];
		std::vector<int> shader_object_uuid = temp->GetShaderObj_UUID();
		for (int j = 0; j < shader_object_uuid.size(); j++) {
			if (shader_object_uuid[j]==this->uid) {
				temp->Link_Program();
			}
		}

	}


}

void ResourceShaderObject::DeleteRes()
{
	glDeleteShader(id_shader_obj);
	delete[] shader_obj_code;
	delete this;

}
