#include "ShaderProgramObject.h"



ShaderProgramObject::ShaderProgramObject()
{
}

ShaderProgramObject::ShaderProgramObject(std::vector<ShaderObject*> id_all_shader_object): ShaderObject_Program_v(id_all_shader_object)
{
}


ShaderProgramObject::~ShaderProgramObject()
{
}

bool ShaderProgramObject::Link_Program()
{


	id_program = glCreateProgram();
	if (0 == id_program)
	{
		LOG("Error creating program object.");
		return false;
	}
	for (int i = 0; i < ShaderObject_Program_v.size(); i++) {
		if (ShaderObject_Program_v[i]->IsCompiled()) {
			glAttachShader(id_program, ShaderObject_Program_v[i]->GetID());
			LOG("Attached %s shader object", ShaderObject_Program_v[i]->GetFileName());
		}
		else {
			LOG("Error trying to attach %s shader object", ShaderObject_Program_v[i]->GetFileName());
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
		glGetProgramiv(id_program, GL_INFO_LOG_LENGTH,&logLen);

		if (logLen > 0)
		{
			char * log = new char [logLen];
			GLsizei written;
			glGetProgramInfoLog(id_program, logLen,&written, log);
			log_shader = log;
			delete[] log;
		}
		if (log_shader.size()>0) {
			LOG("Program log: \n%s", log_shader.c_str());
		}
		return false;
	}
	LOG("Program linked");

	return true;
}

bool ShaderProgramObject::Bind_program()
{
	glUseProgram(id_program);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOG("Error binding shader! %s\n", gluErrorString(error));
		return false;
	}

	return true;
}

void ShaderProgramObject::Unbind_program()
{
	glUseProgram(NULL);
}
