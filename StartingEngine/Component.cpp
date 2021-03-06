#include"GameObject.h"
#include "Component.h"

Component::Component(Component_Type_Enum type_component, GameObject* parent, bool active): type_component(type_component), parent(parent), active(active)
{
	LCG UUID_temp;
	this->UUID_comp = UUID_temp.Int();
	if (parent != nullptr)
	{
		this->UUID_parent_GO = parent->Get_UUID();
	}
	

}

Component::~Component()
{
}

void Component::SetActive(bool state)
{
	active = state;
}

void Component::PreUpdate()
{
}

void Component::Update()
{
}

const Component_Type_Enum Component::GetComponentType() const
{
	return type_component;
}

void Component::Set_Parent(GameObject& par)
{
	parent = &par;
}

GameObject * Component::Get_Parent() const
{
	return parent;
}

void Component::Save(JSON_Object * root_object_scene)
{

}

void Component::Load(JSON_Object * root_object_scene)
{

}

void Component::CleanUp()
{
}




