#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

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


	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

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
	//delete[] Window_Color;
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


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

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

bool ModuleRenderer3D::SaveConfig(JSON_Object * node)
{
	
	json_object_set_number(node, "Window_Color.r", Window_Color[0]);
	json_object_set_number(node, "Window_Color.g", Window_Color[1]);
	json_object_set_number(node, "Window_Color.b", Window_Color[2]);
	return true;
}
