#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include"ModulePlayer.h"
#include "Glew\include\glew.h"
#include "Imgui\imgui_impl_sdl_gl3.h"

#include"Imgui\imgui.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	glewInit();
	ImGui_ImplSdlGL3_Init(App->window->window);
	ImGuiIO& io{ ImGui::GetIO() };
	//io.IniFilename = "/Settings/imgui.ini";
	
	
	//Only to try if we can print objects
	/*App->camera->LookAt(vec3(0, 0, 0));
	App->camera->Position = {0,80,0};
	Cube PlainGame;
	PlainGame.size.x = 700;
	PlainGame.size.z = 700;
	MyCubeMap.push_back(PlainGame);
	PlainGame_Body = App->physics->AddBody(PlainGame, 0);
	PlainGame_Body->SetPos(50, 0, 0);
	PlainGame_Body->collision_listeners.add(this);
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
	
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	ImGui::ShowTestWindow();

	ImGui::Begin("Click here to close the APP");
	paco=ImGui::Button("Click here to close the APP", ImVec2(0, 0));
	ImGui::Text("Hello, world!");
	ImGui::End();

	for (int i = 0; i < MyCubeMap.size(); i++) {
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
	}

	

	ImGui::Render();
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	if (paco == true) {
		return UPDATE_STOP;
	}
	return UPDATE_CONTINUE;
}




