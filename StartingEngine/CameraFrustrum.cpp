#include "CameraFrustrum.h"
#include "GameObject.h"
#include "Component.h"
#include "Mesh.h"

CameraComponent::CameraComponent(GameObject* parent, bool Active) :Component(Component_Type_Enum::component_camera, parent, Active)
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
	float4x4 p=	frustum.ViewProjMatrix();

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

void CameraComponent::PreUpdate()
{

}

void CameraComponent::CheckInFrustum(GameObject* temp_obj)
{
	if (temp_obj->object_tag_s != Tag_Object_Enum::frustrum_obj_tag) {
		if (temp_obj->Get_GO_Mesh() != nullptr) {
			
			AABB* temp2 = &temp_obj->Get_GO_Mesh()->GetAABB();
			//DO THE CULLING FUNCTION
			if (InsideFrustrum(temp2) == CULL_OUTSIDE)
			{
				temp_obj->active = false;
			}
			else
			{
				temp_obj->active = true;
			}


		}	//
	
	
	if (temp_obj->Childrens_GameObject_Vect.size() != 0)
	{
		for (int i = 0; i < temp_obj->Childrens_GameObject_Vect.size(); i++) {
			CheckInFrustum(temp_obj->Childrens_GameObject_Vect[i]);

		}
	}
	}
}
const CamCulling CameraComponent::InsideFrustrum(const AABB * aabb)
{
	float3 vCorner[8];
	int iTotalIn = 0;
	aabb->GetCornerPoints(vCorner);
	 // get the corners of the box into the vCorner array
								 // test all 8 corners against the 6 sides
								 // if all points are behind 1 specific plane, we are out
								 // if we are in with all points, then we are fully in
	for (int p = 0; p < 6; p++) {
		int iInCount = 8;
		int iPtIn = 1;
		for (int i = 0; i < 8; i++) {
			// test this point against the planes
			if (frustum.GetPlane(p).IsOnPositiveSide(vCorner[i]))
			{
				iPtIn = 0;
				iInCount--;
			}
		}
		// were all the points outside of plane p?
		if(iInCount == 0)
			return(CULL_OUTSIDE);
		// check if they were all on the right side of the plane
		iTotalIn += iPtIn;
	}
	// so if iTotalIn is 6, then all are inside the view
	if (iTotalIn == 6)
		return(CULL_INSIDE);
	// we must be partly in then otherwise
	return(CULL_INTERSECT);

}
Frustum CameraComponent::Get_Frustum() const
{
	return frustum;
}
void CameraComponent::SetVertFOV(float n_fov)
{
	frustum.verticalFov = n_fov;
}
void CameraComponent::SetFOV_WH()
{
	frustum.horizontalFov = (2 * math::Atan(math::Tan(frustum.verticalFov / 2) * App->window->GetAspect_Ratio()));

}
void CameraComponent::Update()
{

	GameObject* temp = App->scene_intro->root_gameobject;
	CheckInFrustum(temp);

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
		float4x4 transform_mesh;
		
		//Transform* transform = parent->;
		if (this->parent != nullptr)
		{
		
			//transform_mesh = float4x4::FromTRS(position, rotation, scale);
			transform_mesh = this->parent->GetMatrix_Trans().Transposed();
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
			glColor3f(1.0f, 0.43f, 0.0f);
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

void CameraComponent::SetNewFrame(const float3 pos, const float3 front, const float3 up) {
	

	frustum.front= front;
	frustum.pos = pos;
	frustum.up = up;

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

float* CameraComponent::GetViewProjMatrix()const
{
	return frustum.ViewProjMatrix().Transposed().ptr();
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