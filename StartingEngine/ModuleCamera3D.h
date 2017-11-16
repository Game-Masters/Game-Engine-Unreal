#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "GameObject.h"
#include"Component.h"
#include<map>
class CameraComponent;

#define X_AXIS float3(1.0f, 0.0f, 0.0f)
#define Y_AXIS float3(0.0f, 1.0f, 0.0f)
#define Z_AXIS float3(0.0f, 0.0f, 1.0f)

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	bool Init();
	update_status Update(float dt);
	bool CleanUp();
	bool LoadConfig(JSON_Object* node);
	bool SaveConfig(JSON_Object* node);
	bool Gui_Engine_Modules(float dt);
	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3 &Movement);
	void CameraCenter(AABB* mesh);
	void CameraRecenter();
	const float* GetViewMatrix();
	AABB* LCenter = nullptr;
	void Create_Ray_Mouse();
	void CheckCollision_Mesh();
	CameraComponent* CamComp=nullptr;
	bool ray_cast_pressed = false;
	math::LineSegment r_cast_segm;
	math::LineSegment temp_ray;
	void Recursive_Ray_Distance(GameObject* root);
	std::map<float, GameObject*> mymap;
	GameObject* Closest_Ray_GO = nullptr;
	float2 mouse_pos = float2(0, 0);
private:

	void CalculateViewMatrix();
	float zoom= 50;
public:
	float3 X= X_AXIS, Y= Y_AXIS, Z= Z_AXIS, Position= float3(2.0f, 2.0f, 2.0f), Reference= float3(0.0f, 0.0f, 0.0f);
	bool Can_Move_Camera = false;

};