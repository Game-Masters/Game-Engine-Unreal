#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "GameObject.h"
#include"Component.h"
class CameraComponent;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	//bool Gui_Engine_Modules(float dt);
	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3 &Movement);
	void CameraCenter(AABB* mesh);
	void CameraRecenter();
	const float* GetViewMatrix();
	AABB* LCenter = nullptr;
	CameraComponent* CamComp;
private:

	void CalculateViewMatrix();
	float zoom;
public:
	const float* mat_temp;
	float3 X, Y, Z, Position, Reference;
	bool Can_Move_Camera = false;

};