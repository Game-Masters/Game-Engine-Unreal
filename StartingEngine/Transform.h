#pragma once
#include"ModuleSceneIntro.h"
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include"Component.h"
class GameObject;
class Transform :
	public Component
{
private:
	float3 position;
	float3 scale;
	Quat rotation;


public:
	float4x4 matrix;
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
};

