#pragma once

#include<string>
#include<vector>
#include"MathGeoLib\MathGeoLib.h"
#include"MathGeoLib\MathBuildConfig.h"
#include"Component.h"
#include"Mesh.h"
#include"Transform.h"


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
	void Update();
	Component* AddNewComponent(Component_Type_Enum type);
	Transform* AddNewTransform(float3 position, float3 scale, Quat rotations);
	GameObject(const std::string name, GameObject* parent, const bool active, const Tag_Object_Enum tag_temp, const bool static_obj);
	~GameObject();
};

