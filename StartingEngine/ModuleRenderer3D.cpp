#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include"Mesh.h"
#include"Material.h"
#include"GameObject.h"
#include"ModuleCamera3D.h"
#include "CameraFrustrum.h"
#include"ResourceTexture.h"

#pragma comment (lib, "Glew/libx86/glew32.lib")
#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(bool start_enabled) : Module(start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	
	
	LOG("Creating 3D Renderer context");

	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);

	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
	
	}
	
	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	if(Window_Color!=nullptr)
	glClearColor(*(Window_Color), *(Window_Color + 1), *(Window_Color + 2), 1.f);

	App->camera->CamComp->SetFOV_WH();
	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*App->scene_intro->test_program->Bind_program();
	glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);
	glBegin(GL_QUADS);
	glColor3f(0.f, 1.f, 1.f);
	glVertex2f(-0.3f, -0.3f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.3f, 0.3f);
	glVertex2f(-0.3f, 0.3f);
	glEnd();
	App->scene_intro->test_program->Unbind_program();
	glMatrixMode(GL_MODELVIEW);*/


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glLoadMatrixf(App->camera->CamComp->Get_Frustum().ViewProjMatrix().Transposed().ptr());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	if (cullface)
	{
		glDisable(GL_CULL_FACE);
	}
	else if (wireframe) {
		glLineWidth(3.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (points)
	{
		glPointSize(4.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (mat)
	{
		glDisable(GL_LIGHTING);
	}
	else if (color)
	{
		float diffuse_light[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float specular_light[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
		glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
		glEnable(GL_COLOR_MATERIAL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);

	}



	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{


	
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

bool ModuleRenderer3D::Start()
{

		
	return true;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);
	
	return true;
}

bool ModuleRenderer3D::Gui_Engine_Modules(float dt)
{
	if (ImGui::CollapsingHeader(name.c_str()))
	{		
		if (Window_Color != nullptr) {
			ImGui::ColorPicker3("Screen Color", Window_Color);
			glClearColor(*(Window_Color), *(Window_Color + 1), *(Window_Color + 2), 1.f);
		}
		
	}
	
	return false;
}

void ModuleRenderer3D::Render_3D(Mesh* m, int uuid, Material* texture_mesh) {
	
	if (m->Get_Parent()->active) {
		ResourceMesh* mesh_v = (ResourceMesh*)App->resources_mod->Get(uuid);
		if (App->gui->inspection_node != nullptr) {
			GameObject* par = m->Get_Parent();
			//std::string str_ins = ((ResourceMesh*)App->gui->inspection_node->Get_GO_Mesh()->mesh_r)->Res_Mesh_Base->name;
			if (App->gui->inspection_node == par) {


				float3 position;
				float3 scale;
				Quat rotation;

				glLineWidth(2.0f);
				glColor3f(0.0f, 1.0f, 0.0f);
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, ((ResourceMesh*)m->mesh_r)->Res_Mesh_Base->id_aabb);
				glVertexPointer(3, GL_FLOAT, 0, NULL);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((ResourceMesh*)m->mesh_r)->Res_Mesh_Base->id_index_aabb);
				glDrawElements(GL_LINES, 8 * 3, GL_UNSIGNED_INT, NULL);
				glLineWidth(1.0f);
				glColor3f(1.0f, 1.0f, 1.0f);

			}

		}

		if (mesh_v->Res_Mesh_Base->num_indices > 0 && mesh_v->Res_Mesh_Base->num_vertices > 0) {
			/*if (texture_mesh != nullptr) {
				Resource* text_m = App->resources_mod->Get(texture_mesh->UUID_mat);
				if (mesh_v->Res_Mesh_Base != nullptr) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindTexture(GL_TEXTURE_2D, ((ResourceTexture*)text_m)->id_image_devil);

					if (mesh_v->Res_Mesh_Base->textures_coord != nullptr) {

						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glBindBuffer(GL_ARRAY_BUFFER, mesh_v->Res_Mesh_Base->id_texture);
						glTexCoordPointer(2, GL_FLOAT, 0, NULL);

					}
				}
			}*/
		
	

			App->scene_intro->test_program->Bind_program();
			//glPushMatrix();
			float3 position;
			float3 scale;
			Quat rotation;
			float4x4 transform_mesh = m->Get_Parent()->GetMatrix_Trans();
			transform_mesh.Transpose();

			//glLoadMatrixf(trans_point);
			//glMultMatrixf(transform_mesh.ptr());
			if (App->renderer3D->debugnormals == true && mesh_v->Res_Mesh_Base->normals != nullptr) {
				for (uint k = 0; k < mesh_v->Res_Mesh_Base->num_vertices * 3; k += 3)
				{
					glLineWidth(2.0f);
					glColor3f(1.0f, 0.0f, 0.0f);

					glBegin(GL_LINES);
					glVertex3f(mesh_v->Res_Mesh_Base->vertices[k], mesh_v->Res_Mesh_Base->vertices[k + 1], mesh_v->Res_Mesh_Base->vertices[k + 2]);
					glVertex3f(mesh_v->Res_Mesh_Base->vertices[k] + mesh_v->Res_Mesh_Base->normals[k], mesh_v->Res_Mesh_Base->vertices[k + 1] + mesh_v->Res_Mesh_Base->normals[k + 1], mesh_v->Res_Mesh_Base->vertices[k + 2] + mesh_v->Res_Mesh_Base->normals[k + 2]);
					glEnd();

					glLineWidth(1.0f);
					glColor3f(1.0f, 1.0f, 1.0f);
				}
			}

			int tota_save_buffer = 8;
			if (mesh_v->Res_Mesh_Base->textures_coord == nullptr) {
				tota_save_buffer -= 2;
			}
			if (mesh_v->Res_Mesh_Base->normals == nullptr) {
				tota_save_buffer -= 3;
			}

			projLoc = glGetUniformLocation(App->scene_intro->test_program->GetID_program_shader(), "projection_view");
			glUniformMatrix4fv(projLoc, 1, GL_TRUE, App->camera->CamComp->Get_Frustum().ViewProjMatrix().ptr());
			modelLoc = glGetUniformLocation(App->scene_intro->test_program->GetID_program_shader(), "mat_model");
			glUniformMatrix4fv(modelLoc, 1, GL_TRUE, m->Get_Parent()->GetMatrix_Trans().ptr());

			if (mesh_v->Res_Mesh_Base->vertices != nullptr && mesh_v->Res_Mesh_Base->indices != nullptr) {
				glBindBuffer(GL_ARRAY_BUFFER, mesh_v->Res_Mesh_Base->id_total_buffer);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, tota_save_buffer * sizeof(GLfloat), (char *)NULL + (0 * sizeof(float)));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, tota_save_buffer * sizeof(GLfloat), (char *)NULL + (3 * sizeof(float)));
				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, tota_save_buffer * sizeof(GLfloat), (char *)NULL + (5 * sizeof(float)));

				glEnableClientState(GL_ELEMENT_ARRAY_BUFFER);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_v->Res_Mesh_Base->id_indices);
				glDrawElements(GL_TRIANGLES, mesh_v->Res_Mesh_Base->num_indices, GL_UNSIGNED_INT, NULL);
				glPopMatrix();
			}
		
		
	
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			App->scene_intro->test_program->Unbind_program();
		}
		else {
			LOG("Impossible to draw the mesh");
		}
	}

}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = App->camera->CamComp->Get_Frustum().ViewProjMatrix().Transposed();
	glLoadMatrixf(ProjectionMatrix.ptr());


	App->camera->CamComp->SetFOV_WH();
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();







}

bool ModuleRenderer3D::LoadConfig(JSON_Object * node)
{
	Window_Color = new float(2);
	if (json_object_get_value(node, "Window_Color.r") == NULL || 
		json_object_get_value(node, "Window_Color.g") == NULL ||
		json_object_get_value(node, "Window_Color.b") == NULL) {
		json_object_set_value(node, "Window_Color.r", json_value_init_object());
		json_object_set_value(node, "Window_Color.g", json_value_init_object());
		json_object_set_value(node, "Window_Color.b", json_value_init_object());
	}
	else {
		if (Window_Color!=nullptr){
			Window_Color[0] = json_object_get_number(node, "Window_Color.r");
			Window_Color[1] = json_object_get_number(node, "Window_Color.g");
			Window_Color[2] = json_object_get_number(node, "Window_Color.b");
		}
	}

	return true;
}

bool ModuleRenderer3D::SaveConfig(JSON_Object * node)const
{
	
	json_object_set_number(node, "Window_Color.r", Window_Color[0]);
	json_object_set_number(node, "Window_Color.g", Window_Color[1]);
	json_object_set_number(node, "Window_Color.b", Window_Color[2]);
	return true;
}
