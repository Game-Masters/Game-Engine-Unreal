﻿#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include"GameObject.h"
#include"Component.h"
#include"Mesh.h"
#include"Transform.h"


ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	bool ret = true;

	GLfloat LightModelAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
	lights[0].ref = GL_LIGHT0;
	lights[0].ambient.Set(0.5f, 0.5f, 0.5f, 1.0f);
	lights[0].diffuse.Set(.5f, .5f, 0.5f, 1.0f);
	lights[0].SetPos(1.0f, 0.0f, 2.5f);
	lights[0].Init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	lights[0].Active(true);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);


	world_texture = new Texture_Engine();
	world_texture->Create(nullptr, App->window->win_width, App->window->win_height);
	std::string path_temp = "E:\\CITM\\3ero VJ\\Game-Engine-Unreal\\StartingEngine\\Game\\BakerHouse.fbx";
	std::string path_temp2 = "E:\\CITM\\3ero VJ\\Game-Engine-Unreal\\StartingEngine\\Game\\Baker_house.png";
	Material* temp = nullptr;

	root_gameobject = CreateNewGameObjects("root", true, nullptr, Tag_Object_Enum::root_tag, false);
	root_gameobject->Childrens_GameObject_Vect.push_back(CreateNewGameObjects("geometry1", true, root_gameobject, Tag_Object_Enum::no_obj_tag, false));
	root_gameobject->Childrens_GameObject_Vect[0]->AddNewTransform(float3(10,15,1), float3(0, 0, 0), Quat(1,0,0,0));
	temp = root_gameobject->Childrens_GameObject_Vect[0]->AddNewMaterial(path_temp2.c_str(),path_temp.c_str());
	root_gameobject->Childrens_GameObject_Vect[0]->AddNewMesh(path_temp.c_str(), temp);

	return ret;
}


update_status ModuleSceneIntro::PreUpdate(float dt)
{
	world_texture->Bind();
	
	


	return UPDATE_CONTINUE;
}


// Update
update_status ModuleSceneIntro::Update(float dt)
{

	
	

	for (int i = 0; i < root_gameobject->Childrens_GameObject_Vect.size(); i++) {
		root_gameobject->Childrens_GameObject_Vect[i]->Update();
	}
	

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 3.f, 0.f);

	glEnd();
	glColor3f(1, 1, 1);

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(3.f, 0.f, 0.f);

	glEnd();
	glColor3f(1, 1, 1);


	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0, 0, 1);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 0.f, 3.f);

	glEnd();
	glColor3f(1, 1, 1);


//	 light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
	lights[i].Render();
	

	

	
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneIntro::Gui_Engine_Modules(float dt)
{
	return true;
}

bool ModuleSceneIntro::CleanUp()
{

	return true;
}

GameObject * ModuleSceneIntro::CreateNewGameObjects(const char * name, bool active, GameObject* parent, Tag_Object_Enum tag_temp, bool static_s)
{

	std::string name_f = name;

	GameObject* n_gameobject = new GameObject(name_f, parent, active, tag_temp, static_s);

	return n_gameobject;
}






