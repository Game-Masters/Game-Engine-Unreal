#include "GameObject.h"



void GameObject::Update()
{

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



GameObject::GameObject(const std::string name, GameObject * parent, const bool active, const Tag_Object_Enum tag_temp, const bool static_obj): name(name), parent(parent), active(active), object_tag_s(tag_temp), static_obj(static_obj)
{
}

GameObject::~GameObject()
{
}
