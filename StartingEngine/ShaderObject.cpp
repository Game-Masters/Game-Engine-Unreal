#include "ShaderObject.h"
#include"Application.h"


ShaderObject::ShaderObject()
{
}

ShaderObject::ShaderObject(ShaderType Type, const char* filename ,const GLchar * Shader_obj_code):shader_obj_type(Type), file_name_shader(filename), shader_obj_code(Shader_obj_code)
{
}


ShaderObject::~ShaderObject()
{
}

bool ShaderObject::CompileShader()
{

	switch (shader_obj_type) {
	case ShaderType::vertex_shader:
		id_shader_obj = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::fragment_shader:
		id_shader_obj = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	LOG("Creating %s shader.", file_name_shader.c_str());

	if (0 == id_shader_obj)
	{
		LOG("Error creating %s shader.", file_name_shader.c_str());
		return false;
	}


	//Creating Shader source
	glShaderSource(id_shader_obj, 1, &shader_obj_code, NULL);

	//Compiling Shader
	glCompileShader(id_shader_obj);
	LOG("Compiling %s shader.", file_name_shader.c_str());

	//Success compilation?
	GLint result;
	glGetShaderiv(id_shader_obj, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result)
	{
		LOG("Error compiling %s shader", file_name_shader.c_str());
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

	compiled = true;
	return true;
}

GLuint ShaderObject::GetID()
{
	return id_shader_obj;
}

const char * ShaderObject::GetFileName()
{
	return file_name_shader.c_str();
}

bool ShaderObject::IsCompiled()
{
	return compiled;
}
