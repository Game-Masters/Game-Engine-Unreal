#pragma once
#include "Component.h"
#include"MathGeoLib\MathGeoLib.h"
#include"Application.h"
#include"Globals.h"
#include "Transform.h"
#include"Quadtree.h"
enum CamCulling
{
	CULL_INSIDE,
	CULL_OUTSIDE,
	CULL_INTERSECT
};
class CameraComponent : public Component
{
public:
	CameraComponent(GameObject* parent, bool Active);
	~CameraComponent();
	void PreUpdate();

	void Update();
	bool Enable();
	bool Disable();
	const float* GetViewProjMatrix()const;
	bool ParentHasTransform(float3 &position, float3 &scaling, Quat &rotation);
	void CheckInFrustum(QuadTreeNode*);
	void CheckInFrustumNOStatic(GameObject*);
	void SetNewFrame(const float3 pos, const float3 front, const float3 up);
	const CamCulling InsideFrustrum(const AABB* aabb);
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);
	const Frustum Get_Frustum()const;
	void SetVertFOV(float n_fov);
	void SetNearFarPlane(float near_p, float far_p);
	void SetFOV_WH();
	void CleanUp();
private:
	void GenerateFrustumDraw();
	void CleanFrustumDraw();

private:
	Frustum frustum;
	float NearPlaneDistance = 0.1f;
	float FarPlaneDistance = 100.0f;
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