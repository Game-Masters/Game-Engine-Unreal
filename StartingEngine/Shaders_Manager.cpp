#include "Shaders_Manager.h"
#include"Application.h"
#include"ModuleCamera3D.h"
#include"CameraFrustrum.h"

Shaders_Manager::Shaders_Manager()
{
}


Shaders_Manager::~Shaders_Manager()
{
}

bool Shaders_Manager::Init()
{
	return true;
}

bool Shaders_Manager::Start()
{
	return true;
}

update_status Shaders_Manager::Update(float dt)
{
	std::vector<Resource*> temp_V= App->resources_mod->Get_TypeResources(Resources_Type::shader_program);
	for (int i = 0; i < temp_V.size(); i++) {

		ResourceShaderMaterial* selector_program = (ResourceShaderMaterial*)temp_V[i];
		selector_program->Bind_program();

		projLoc = glGetUniformLocation(selector_program->GetID_program_shader(), "projection_view");
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, App->camera->CamComp->Get_Frustum().ViewProjMatrix().ptr());

		timeloc = glGetUniformLocation(selector_program->GetID_program_shader(), "time");
		glUniform1f(timeloc, App->GetPlay_Time());

		selector_program->Unbind_program();
	}

	return update_status::UPDATE_CONTINUE;
}

bool Shaders_Manager::CleanUp()
{
	return true;
}
