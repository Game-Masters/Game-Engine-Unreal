#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 800.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f
#define	TIME_LIMIT 100

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	bool Gui_Engine_Modules(float dt);
	update_status Update(float dt);
	bool CleanUp();


public:
	Cube_P n;
	PhysBody3D* turret;

	PhysBody3D* canonbody;

	btHingeConstraint* canon_turretconst;
	btHingeConstraint* turret_carconst;

	PhysVehicle3D* vehicle;

	p2DynArray<PhysBody3D*> CanonBallsBody;

	float turn;
	float acceleration;
	float brake;

	bool mouse= true;

	int puntuation = 0;
	int highscore = 0;
	int speedlimit = 40;

	Timer timelimit;

	unsigned int fire = 0;
};