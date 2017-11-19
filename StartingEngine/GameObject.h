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
	no_obj_tag,
	frustrum_obj_tag
};

class Component;
class GameObject
{
public:

	std::string name="-1";
	GameObject* parent=nullptr;
	std::vector<GameObject*> Childrens_GameObject_Vect;
	std::vector<Component*> Component_Vect;
	bool active = true;
	bool static_obj = true;
	Tag_Object_Enum object_tag_s = Tag_Object_Enum::no_obj_tag;
	bool IsComponentType(Component_Type_Enum temp_type) const;
	void PreUpdate();
	void Update();
	Component* AddNewComponent(Component_Type_Enum type);
	Transform* AddNewTransform(float3 position, float3 scale, Quat rotations);
	Mesh* AddNewMesh(int UUID=-1, const char* path=nullptr, Material* t_mat=nullptr);
	Material* AddNewMaterial(int UUID);
	CameraComponent* AddNewFrustum();
	const float4x4 GetMatrix_Trans();
	GameObject(const std::string name, GameObject* parent, const bool active, const Tag_Object_Enum tag_temp, const bool static_obj);
	~GameObject();
	const int Get_UUID()const;
	void Set_UUID(int UUID);
	void Set_UUID_parent(int UUID);
	void Save(JSON_Object *root_object_scene);
	void Load(JSON_Object *root_object_scene);
	void CleanUp();
	Mesh* Get_GO_Mesh()const;

	Transform* GetTransform() const;
	const int Get_UUID_Parent() const;
	GameObject* FindUUID(int GO_Load_uuid);
private:
	int UUID=0;
	int UUID_parent = 0;
};

