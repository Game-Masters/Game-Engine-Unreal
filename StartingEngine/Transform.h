#pragma once
#include"ModuleSceneIntro.h"
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include"Component.h"
#include"Imgui\ImGuizmo.h"
class GameObject;
class Transform :
	public Component
{
private:
	float3 position;
	float3 scale;
	Quat rotation;
	float4x4 matrix= float4x4::identity;
	ImGuizmo::OPERATION Operator_Guiz = ImGuizmo::OPERATION::ROTATE;
public:

	Transform(GameObject *parent, float3 position, float3 scale, Quat rotations);
	~Transform();
	void SetPosition(float3 n_pos);
	void SetRotation(Quat n_rot);
	void SetScale(float3 n_scal);
	void Update();
	float3 GetPosition();
	Quat GetRotation();
	float3 GetScale();
	float4x4 GetMatrix();
	float4x4 SetMatrix(float4x4 temp);
	virtual void Save(JSON_Object *root_object_scene);
	virtual void Load(JSON_Object *root_object_scene);

};

