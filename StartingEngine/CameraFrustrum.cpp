#include "CameraFrustrum.h"


CameraComponent::CameraComponent(GameObject* parent, bool Active) :Component(Component_Type_Enum::component_material_type, parent, Active)
{
	if (Active) Enable();
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.nearPlaneDistance = NearPlaneDistance;
	frustum.farPlaneDistance = FarPlaneDistance;
	frustum.verticalFov = FOVVertical * DEGTORAD;
	frustum.horizontalFov = Atan(AspectRatio * Tan(frustum.verticalFov * 0.5f)) * 2.0f;
	frustum.pos = Pos;
	frustum.up = Up;
	frustum.front = Front;
	
}
CameraComponent::~CameraComponent() 
{

}
bool CameraComponent::Enable()
{
	return true;
}
bool CameraComponent::Disable()
{
	return false;
}


void CameraComponent::Update()
{
	if (first_time)
	{
		GenerateFrustumDraw();
		first_time = false;
	}
	if (parent != nullptr)
	{
		float3 position;
		float3 scale;
		Quat rotation;
		
		
		//Transform* transform = parent->;
		if (ParentHasTransform(position, scale, rotation)!= false)
		{
			//float4x4 matrix = *transform->GetMatrix();
			float4x4 transform_mesh = float4x4::FromTRS(position, rotation, scale);

			bool frustum_changed = false;
			float3 prev_pos = frustum.pos;
			frustum.pos = transform_mesh.Row3(3);
			if ((prev_pos.x != frustum.pos.x) || (prev_pos.y != frustum.pos.y) || (prev_pos.z != frustum.pos.z))
				frustum_changed = true;

			float3 prev_front = frustum.front;
			frustum.front =transform_mesh.Row3(2);
			if ((prev_front.x != frustum.front.x) || (prev_front.y != frustum.front.y) || (prev_front.z != frustum.front.z))
				frustum_changed = true;

			float3 prev_up = frustum.up;
			frustum.up = transform_mesh.Row3(1);
			if ((prev_up.x != frustum.up.x) || (prev_up.y != frustum.up.y) || (prev_up.z != frustum.up.z))
				frustum_changed = true;

			if (frustum_changed)
				GenerateFrustumDraw();
		}


		if ((DebugDrawFrustum_id_vertices != 0))
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glLineWidth(2.0f);
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, DebugDrawFrustum_id_vertices);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DebugDrawFrustum_id_indices);
			glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, NULL);
			glColor3f(1.0f, 1.0f, 1.0f);
			glLineWidth(1.0f);
		}
	}
}
void CameraComponent::GenerateFrustumDraw()
{
	//Clean if there is another frustum allocated
	CleanFrustumDraw();

	//Box math
	DebugDrawFrustum_vertices = new float[24];
	float vertices[] =
	{
		frustum.CornerPoint(0).x,frustum.CornerPoint(0).y,frustum.CornerPoint(0).z,
		frustum.CornerPoint(1).x,frustum.CornerPoint(1).y,frustum.CornerPoint(1).z,
		frustum.CornerPoint(2).x,frustum.CornerPoint(2).y,frustum.CornerPoint(2).z,
		frustum.CornerPoint(3).x,frustum.CornerPoint(3).y,frustum.CornerPoint(3).z,
		frustum.CornerPoint(4).x,frustum.CornerPoint(4).y,frustum.CornerPoint(4).z,
		frustum.CornerPoint(5).x,frustum.CornerPoint(5).y,frustum.CornerPoint(5).z,
		frustum.CornerPoint(6).x,frustum.CornerPoint(6).y,frustum.CornerPoint(6).z,
		frustum.CornerPoint(7).x,frustum.CornerPoint(7).y,frustum.CornerPoint(7).z
	};
	memcpy(DebugDrawFrustum_vertices, vertices, sizeof(float) * 24);

	DebugDrawFrustum_indices = new uint[24];
	uint indices[] =
	{
		0,2,
		0,4,
		0,1,
		7,6,
		7,3,
		7,5,
		5,1,
		5,4,
		2,3,
		2,6,
		6,4,
		3,1
	};
	memcpy(DebugDrawFrustum_indices, indices, sizeof(uint) * 24);

	//Buffer for vertex
	glGenBuffers(1, (GLuint*)&DebugDrawFrustum_id_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, DebugDrawFrustum_id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, DebugDrawFrustum_vertices, GL_STATIC_DRAW);

	// Buffer for indices
	glGenBuffers(1, (GLuint*)&DebugDrawFrustum_id_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DebugDrawFrustum_id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 24, DebugDrawFrustum_indices, GL_STATIC_DRAW);
}


void CameraComponent::CleanFrustumDraw()
{
	if (DebugDrawFrustum_vertices != nullptr)
	{
		glDeleteBuffers(1, &DebugDrawFrustum_id_vertices);
		RELEASE_ARRAY(DebugDrawFrustum_vertices);
	}
	if (DebugDrawFrustum_indices != nullptr)
	{
		glDeleteBuffers(1, &DebugDrawFrustum_id_indices);
		RELEASE_ARRAY(DebugDrawFrustum_indices);
	}
}
const float4x4* CameraComponent::GetViewProjMatrix() const
{
	return &frustum.ViewProjMatrix();
}
bool CameraComponent::ParentHasTransform(float3 & position, float3 & scaling, Quat & rotation)
{

	if (this->parent!=nullptr) {

		for (int i = 0; i < parent->Component_Vect.size(); i++) {

			if (parent->Component_Vect[i]->GetComponentType()== Component_Type_Enum::component_transform_type) {
				position = ((Transform*)parent->Component_Vect[i])->GetPosition();
				scaling = ((Transform*)parent->Component_Vect[i])->GetScale();
				rotation = ((Transform*)parent->Component_Vect[i])->GetRotation();
			}
		}
		return true;
	}
	return false;
}