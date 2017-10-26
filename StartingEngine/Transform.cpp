#include "Transform.h"
#include"GameObject.h"

Transform::Transform(GameObject *parent, float3 position, float3 scale, Quat rotations ):Component(
	Component_Type_Enum::component_transform_type, parent, true), position(position),scale(scale), rotation(rotations)
{
	if (parent->parent != nullptr) {
		//Need to fix why son has matrix before than the parent
		matrix = float4x4::FromTRS(position, rotation, scale);
		if (parent->parent->name != "root") {
			float4x4 matrix_parent = parent->parent->GetMatrix_GO();
			matrix = matrix*matrix_parent;
		}
		//matrix = float4x4::FromTRS(position, rotation, scale);
	}
}

Transform::~Transform()
{
}

void Transform::Update()
{

}

void Transform::SetPosition(float3 n_pos)
{
	this->position = n_pos;
}

void Transform::SetRotation(Quat n_rot)
{
	this->rotation = n_rot;
}

void Transform::SetScale(float3 n_scal)
{
	this->scale = n_scal;
}

float3 Transform::GetPosition()
{
	return this->position;
}

Quat Transform::GetRotation()
{
	return this->rotation;
}

float3 Transform::GetScale()
{
	return this->scale;
}

float4x4 Transform::GetMatrix()
{
	return matrix;
}


