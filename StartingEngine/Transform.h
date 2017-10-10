#pragma once
#include "Component.h"
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
class GameObject;
class Transform :
	public Component
{
private:
	float3 position;
	float3 scale;
	Quat rotation;


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
};

