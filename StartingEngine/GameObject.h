#pragma once

#include<string>
#include<vector>

#include"MathGeoLib\MathBuildConfig.h"
#include"Component.h"
#include"Mesh.h"
#include"Transform.h"
#include"Material.h"

class CameraComponent;


enum Tag_Object_Enum {
	root_tag,
	no_obj_tag
};

class Component;
class GameObject
{
public:

	std::string name;
	GameObject* parent=nullptr;
	std::vector<GameObject*> Childrens_GameObject_Vect;
	std::vector<Component*> Component_Vect;
	bool active = true;
	bool static_obj = false;
	Tag_Object_Enum object_tag_s = Tag_Object_Enum::no_obj_tag;
	bool IsComponentType(Component_Type_Enum temp_type);
	void PreUpdate();
	void Update();
	Component* AddNewComponent(Component_Type_Enum type);
	Transform* AddNewTransform(float3 position, float3 scale, Quat rotations);
	Mesh* AddNewMesh(geometry_base_creating* vec_mesh, const char* path, Material* t_mat=nullptr);
	Material* AddNewMaterial(const char* Path_texture, const char* Path_fbx);
	CameraComponent* AddNewFrustum();
	float4x4 GetMatrix_Trans();
	GameObject(const std::string name, GameObject* parent, const bool active, const Tag_Object_Enum tag_temp, const bool static_obj);
	~GameObject();
	const int Get_UUID();
	void Set_UUID(int UUID);
	void Set_UUID_parent(int UUID);
	void Save(JSON_Object *root_object_scene);
	void Load(JSON_Object *root_object_scene);
	void CleanUp();
	AABB Get_AABB_Mesh()const ;
	Transform* GetTransform();
	int Get_UUID_Parent() const;
	GameObject* FindUUID(int GO_Load_uuid);
private:
	int UUID=0;
	int UUID_parent = 0;
};

