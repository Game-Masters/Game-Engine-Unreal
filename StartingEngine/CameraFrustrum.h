#pragma once
#include "Component.h"
#include"MathGeoLib\MathGeoLib.h"
#include"Application.h"
#include"Globals.h"
#include "Transform.h"

class CameraComponent : public Component
{
public:
	CameraComponent(GameObject* parent, bool Active);
	~CameraComponent();
	void Preupdate();
	
	void Update();
	bool Enable();
	bool Disable();
	const float4x4* GetViewProjMatrix() const;
	bool ParentHasTransform(float3 &position, float3 &scaling, Quat &rotation);
	void CheckInFrustum(GameObject*);
	
private:
	void GenerateFrustumDraw();
	void CleanFrustumDraw();

private:
	Frustum frustum;
	float NearPlaneDistance = 0.1f;
	float FarPlaneDistance = 5.0f;
	float FOVVertical = 60.0f;
	float AspectRatio = 1280.0f / 720.0f;
	float3 Pos = { 0.0f, 0.0f, 0.0f };
	float3 Up = { 0.0f, 1.0f, 0.0f };
	float3 Front = { 0.0f, 0.0f, 1.0f };

	bool DebugDrawFrustum = false;
	uint DebugDrawFrustum_id_vertices = 0; // id in VRAM
	float* DebugDrawFrustum_vertices = nullptr;
	uint DebugDrawFrustum_id_indices = 0; // id in VRAM
	uint* DebugDrawFrustum_indices = nullptr;
	bool first_time = true;
};