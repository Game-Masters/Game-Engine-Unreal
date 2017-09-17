#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include"j1PerfTimer.h"
#include"Imgui/imgui.h"

#include<vector>

#define MAX_SNAKE 2
#define MAX_CUBE 50
struct PhysBody3D;
struct PhysMotor3D;
struct btHingeConstraint;
enum guy {
	bad_guy,
	good_guy,
	unknown
};
class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	update_status PostUpdate(float dt);


public:

	PhysBody3D*PlainGame_Body;

	std::vector<Cube>MyCubeMap;
	std::vector<PhysBody3D*>MyPhysbodyCubeMap;

	std::vector<Cube>MySphereObj;
	std::vector<PhysBody3D*>MyPhysbodySphereobj;


	std::vector<Cube>MyCubeObj;
	std::vector<PhysBody3D*>MyPhysbodyCubeobj;


	std::vector<Cube>MySensorCube;
	std::vector<PhysBody3D*>MySensorCubeBody;


};
