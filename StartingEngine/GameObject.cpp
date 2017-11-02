#include "GameObject.h"
#include"CameraFrustrum.h"


bool GameObject::IsComponentType(Component_Type_Enum temp_type)
{

	for (int i = 0; i < Component_Vect.size(); i++) {
		if (Component_Vect[i]->GetComponentType()== temp_type) {
			return true;
		}
	}

	return false;
}

void GameObject::PreUpdate()
{
	if (active) {
	
		for (int i = 0; i < this->Childrens_GameObject_Vect.size(); i++) {
			this->Childrens_GameObject_Vect[i]->PreUpdate();

		}

		for (int j = 0; j < this->Component_Vect.size(); j++) {
			this->Component_Vect[j]->PreUpdate();
		}
	}
}

void GameObject::Update()
{
	if (active) {
		for (int i = 0; i < this->Childrens_GameObject_Vect.size(); i++) {
			this->Childrens_GameObject_Vect[i]->Update();
			
		}

		for (int j = 0; j < this->Component_Vect.size(); j++) {
			this->Component_Vect[j]->Update();
		}
	}
}

Component * GameObject::AddNewComponent(Component_Type_Enum type)
{
	Component* n_component = new Component(type, this, true);
	this->Component_Vect.push_back(n_component);
	return n_component;
}

Transform * GameObject::AddNewTransform(float3 position, float3 scale, Quat rotations)
{
	Transform* n_transform = new Transform(this, position, scale, rotations);
	this->Component_Vect.push_back(n_transform);
	return n_transform;
}

Mesh * GameObject::AddNewMesh(geometry_base_creating* vec_mesh, const char* path,Material* t_mat)
{
	Mesh* n_mesh = new Mesh(this, vec_mesh, path, t_mat);
	this->Component_Vect.push_back(n_mesh);
	return n_mesh;
}

Material * GameObject::AddNewMaterial(const char * Path_texture, const char * Path_fbx)
{
	Material* n_mat = new Material(Path_texture,Path_fbx,this);
	this->Component_Vect.push_back(n_mat);
	return n_mat;
}
CameraComponent* GameObject::AddNewFrustum()
{
	CameraComponent* n_camera = new CameraComponent(this,true);
	this->Component_Vect.push_back(n_camera);
	return n_camera;
}

float4x4 GameObject::GetMatrix_GO()
{
	float4x4 matrix = float4x4::zero;
	if (this->parent != nullptr) {

		for (int i = 0; i < Component_Vect.size(); i++) {

			if (Component_Vect[i]->GetComponentType() == Component_Type_Enum::component_transform_type) {
				
				//float4x4 temp  = float4x4::FromTRS(((Transform*)Component_Vect[i])->GetPosition(), ((Transform*)Component_Vect[i])->GetRotation(), ((Transform*)Component_Vect[i])->GetScale());
				matrix = ((Transform*)Component_Vect[i])->GetMatrix();
				//NEED TO MULTYPLY WITH PARENT
			}
		}
	}
	return matrix;
}



GameObject::GameObject(const std::string name, GameObject * parent, const bool active, const Tag_Object_Enum tag_temp, const bool static_obj): name(name), parent(parent), active(active), object_tag_s(tag_temp), static_obj(static_obj)
{
	LCG UUID_temp;
	this->UUID = UUID_temp.Int();
	if (parent != nullptr) {
		this->UUID_parent = parent->UUID;
	}
}

GameObject::~GameObject()
{

	
}

const int GameObject::Get_UUID()
{
	return this->UUID;
}

void GameObject::Save(JSON_Object *root_object_scene)
{
	JSON_Object* node;
	if (this->name != "root") {
		App->scene_intro->num_GO++;
		std::string go_name = "GameObject" + std::to_string(App->scene_intro->num_GO);
		
		json_object_set_value(root_object_scene, go_name.c_str(), json_value_init_object());
		node = json_object_get_object(root_object_scene, go_name.c_str());
		json_object_set_string(node, "Name", this->name.c_str());
		json_object_set_number(node, "UUID", this->UUID);

		if (parent != nullptr) {
			json_object_set_number(node, "UUID_parent", this->UUID_parent);
		}

		if (this->Component_Vect.size() > 0) {
			for (int i = 0; i < this->Component_Vect.size(); i++) {
				this->Component_Vect[i]->Save(node);
				
			}
		}
	}

		for (int i = 0; i < this->Childrens_GameObject_Vect.size(); i++) {
			this->Childrens_GameObject_Vect[i]->Save(root_object_scene);
		}
	

}


void GameObject::Set_UUID(int UUID) {
	this->UUID = UUID;
}

void GameObject::Set_UUID_parent(int UUID) {
	this->UUID_parent = UUID;
}

void GameObject::Load(JSON_Object *root_object_scene)
{
}
