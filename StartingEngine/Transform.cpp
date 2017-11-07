#include "Transform.h"
#include"GameObject.h"
#include"CameraFrustrum.h"
Transform::Transform(GameObject *parent, float3 position, float3 scale, Quat rotations ):Component(
	Component_Type_Enum::component_transform_type, parent, true), position(position),scale(scale), rotation(rotations)
{
	this->matrix = float4x4::FromTRS(position, rotations, scale);

}

Transform::~Transform()
{
}

void Transform::Update()
{
	this->matrix.Decompose(this->position, this->rotation, this->scale);

	if (this->parent==App->gui->inspection_node) {
		ImGuizmo::Enable(true);
		float4x4 mat_proj = App->camera->CamComp->Get_Frustum().ProjectionMatrix();
		float4x4 mat = App->camera->CamComp->Get_Frustum().ViewMatrix();
		float4x4 matrix_t = parent->GetMatrix_Trans();

		ImGuiIO& io = ImGui::GetIO();
		ImGuizmo::SetRect(App->scene_intro->tx_vec.x, App->scene_intro->tx_vec.y, App->scene_intro->tx_vec.z, App->scene_intro->tx_vec.w);

		
		float matrixTranslation[3], matrixRotation[4], matrixScale[3];

		ImGuizmo::DecomposeMatrixToComponents(this->parent->GetMatrix_Trans().Inverted().ptr(), matrixTranslation, matrixRotation, matrixScale);
		/*position.x = matrixTranslation[0];	position.y = matrixTranslation[1];	position.z = matrixTranslation[2];
		scale.x = matrixScale[0];	scale.y = matrixScale[1];	scale.z = matrixScale[2];
		rotation.x = matrixRotation[0];	position.y = matrixRotation[1];	position.z = matrixRotation[2];*/
		ImGuizmo::Manipulate(mat.Transposed().ptr(), mat_proj.Transposed().ptr(), Operator_Guiz, ImGuizmo::WORLD, matrix_t.Transposed().ptr());

		float4x4 temp_mat;
		ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, temp_mat.ptr());
		
		temp_mat.Decompose(position,rotation,scale);
		
		


		ImGuizmo::Enable(false);
	}

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
	
	return  float4x4::FromTRS(position, rotation, scale);

}

float4x4 Transform::SetMatrix(float4x4 temp)
{
	return this->matrix=temp;
}

void Transform::Save(JSON_Object * root_object_scene)
{
	JSON_Object* node;
	json_object_set_value(root_object_scene, "Transform", json_value_init_object());
	node = json_object_get_object(root_object_scene, "Transform");
	json_object_set_number(node, "UUID", this->UUID_comp);
	if (parent != nullptr) {
		json_object_set_number(node, "UUID_parent", this->UUID_parent_GO);
	}


	JSON_Value* va = json_value_init_array();
	JSON_Array* array = nullptr;
	array = json_value_get_array(va);
	json_object_set_value(node, "Position", va);
	json_array_append_number(array, this->position.x);
	json_array_append_number(array, this->position.y);
	json_array_append_number(array, this->position.z);

	va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(node, "Scale", va);
	json_array_append_number(array, this->scale.x);
	json_array_append_number(array, this->scale.y);
	json_array_append_number(array, this->scale.z);


	va = json_value_init_array();
	array = json_value_get_array(va);
	json_object_set_value(node, "Rotation", va);
	json_array_append_number(array, this->rotation.x);
	json_array_append_number(array, this->rotation.y);
	json_array_append_number(array, this->rotation.z);
	json_array_append_number(array, this->rotation.w);

}

void Transform::Load(JSON_Object * root_object_scene)
{
}


