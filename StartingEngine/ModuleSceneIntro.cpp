#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"





ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	//LOG("Loading Intro assets");
	bool ret = true;

	vec p1 = { 2,0,0 };
	vec p2 = { -2,0,0 };
	n_sphere_one = new Sphere(p1,1);
	n_sphere_two = new Sphere(p2,1);
	

	//Random
	LCG rand_test;
	int iop;
	float iop2;
	iop = rand_test.Int(0, 1500);
	iop2 = rand_test.Float(0.0,1.0);
	

	//Only to try if we can print objects
	/*App->camera->LookAt(vec3(0, 0, 0));
	App->camera->Position = {0,80,0};
	Cube_P PlainGame;
	PlainGame.size.x = 700;
	PlainGame.size.z = 700;
	MyCubeMap.push_back(PlainGame);
	PlainGame_Body = App->physics->AddBody(PlainGame, 0);
	PlainGame_Body->SetPos(50, 0, 0);
	PlainGame_Body->collision_listeners.push_back(this);
	MyPhysbodyCubeMap.push_back(PlainGame_Body);*/



	
	return ret;
}


update_status ModuleSceneIntro::PreUpdate(float dt)
{

	

	return UPDATE_CONTINUE;
}


// Update
update_status ModuleSceneIntro::Update(float dt)
{
	

	/*for (int i = 0; i < MyCubeMap.size(); i++) {
		MyPhysbodyCubeMap[i]->GetTransform(&MyCubeMap[i].transform);
		MyCubeMap[i].Render();
	}

	for (int i = 0; i < MySphereObj.size(); i++) {
		MyPhysbodySphereobj[i]->GetTransform(&MyCubeMap[i].transform);
		MySphereObj[i].Render();
	}

	for (int i = 0; i < MyCubeObj.size(); i++) {
		MyPhysbodyCubeobj[i]->GetTransform(&MyCubeMap[i].transform);
		MyCubeObj[i].Render();
	}*/

	

	
	
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
	return false;
}




