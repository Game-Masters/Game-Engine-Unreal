#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	//bool Gui_Engine_Modules(float dt);
	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	void CameraCenter(AABB* mesh);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();
	float zoom;
public:
	
	vec3 X, Y, Z, Position, Reference;

private:
	mat3x3 R;
	mat4x4 ViewMatrix, ViewMatrixInverse;
};