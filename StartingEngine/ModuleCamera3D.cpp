#include "Globals.h"
#include "Application.h"

#include "ModuleCamera3D.h"

#include "CameraFrustrum.h"
#include"Imgui\ImGuizmo.h"



ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled)
{
	
	zoom = 50;
	X = X_AXIS;
	Y = Y_AXIS;
	Z = Z_AXIS;

	Position = float3(2.0f, 10.0f, 2.0f);
	Reference = float3(0.0f, 0.0f, 0.0f);


	
}

ModuleCamera3D::~ModuleCamera3D()
{}

bool ModuleCamera3D::Init() {

	CamComp = new CameraComponent(App->scene_intro->root_gameobject, true);
	CalculateViewMatrix();
	return true;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	
	r_cast_segm.a = float3(0, 0, 0);
	r_cast_segm.b = float3(0, 0, 0);
	temp_ray.a = float3(0, 0, 0);
	temp_ray.b = float3(0, 0, 0);
	Closest_Ray_GO = nullptr;
	//Position = Reference + zoom * Z;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}
bool Gui_Engine_Modules(float dt) {

	return true;
}
// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	float3 newPos(0, 0, 0);
	float speed = 4.0f * dt;
	float wheel_direction = (float)App->input->GetMouseZ();

	if (wheel_direction > 0) Position += ((Reference-Position) * 0.1f);
	if (wheel_direction < 0) Position -= ((Reference - Position) * 0.1f);

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN && App->gui->n4 == false)
	{
		Can_Move_Camera = !Can_Move_Camera;
	}

	if (Can_Move_Camera) {
		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;

		Move(newPos);

	}
	float3x3 cam_rot_mouse_x= float3x3::identity;
	float3x3 cam_rot_mouse_y= float3x3::identity;
			if ((App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LALT)== KEY_REPEAT && App->gui->n4 == false) || (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && Can_Move_Camera==true))
			{
				int dx = -App->input->GetMouseXMotion();
				int dy = -App->input->GetMouseYMotion();

				float Sensitivity = 0.25f;

				Position -= Reference;

				if (dx != 0)
				{
					float DeltaX = (float)dx * Sensitivity;
					cam_rot_mouse_x = float3x3::RotateAxisAngle(Y_AXIS, DeltaX * DEGTORAD);

					X = cam_rot_mouse_x*X;
					Y = cam_rot_mouse_x*Y;
					Z = cam_rot_mouse_x*Z;
				}

				if (dy != 0)
				{
					float DeltaY = (float)dy * Sensitivity;
					cam_rot_mouse_y = float3x3::RotateAxisAngle(X, DeltaY * DEGTORAD);
				

					Y = cam_rot_mouse_y*Y;
					Z = cam_rot_mouse_y*Z;

					if (Y.y < 0.0f)
					{
						Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
						Y = Z.Cross(X);
					}
				}

				Position = Reference + Z * Position.Length();
			}
	
			CalculateViewMatrix();

	// Raycast calc-------------


			if (!ImGuizmo::IsOver()) {
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->gui->n4 == false) {
					ray_cast_pressed = true;
					Closest_Ray_GO = nullptr;
					App->gui->inspection_node = nullptr;
				}
			}

		if (ray_cast_pressed) {
			Create_Ray_Mouse();
			ray_cast_pressed = false;
		}

		if (Closest_Ray_GO!=nullptr) {
			App->gui->inspection_node = Closest_Ray_GO;
		}
		

		glLineWidth(5.0f);
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(r_cast_segm.a.x, r_cast_segm.a.y, r_cast_segm.a.z);
		glVertex3f(r_cast_segm.b.x, r_cast_segm.b.y, r_cast_segm.b.z);
		glEnd();
		glColor3f(1, 1, 1);
		mymap.clear();


	return UPDATE_CONTINUE;
}

void ModuleCamera3D::Recursive_Ray_Distance(GameObject* root) {


	if (root->name != "root") {
		float distance_n=0;
		float distance_f=0;
		Mesh* go_test = root->Get_GO_Mesh();
		if (go_test != nullptr) {
			if (r_cast_segm.Intersects(go_test->GetAABB(), distance_n, distance_f)) {
				std::pair<float ,GameObject*> p;
				p.first = distance_n;
				p.second = root;
				mymap.insert(p);
			}
		}
	}

	for (int i = 0; i<root->Childrens_GameObject_Vect.size(); i++) {
		GameObject* temp = root->Childrens_GameObject_Vect[i];
		Recursive_Ray_Distance(temp);
	}

	//




}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = (Position - Reference).Normalized();
	X = ((float3(0.0f, 1.0f, 0.0f).Cross(Z))).Normalized();
	Y = Z.Cross(X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const float3 &Spot)
{
	Reference = Spot;

	Z = (Position - Reference).Normalized();
	X = ((float3(0.0f, 1.0f, 0.0f).Cross(Z))).Normalized();
	Y = Z.Cross(X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
const float* ModuleCamera3D::GetViewMatrix()
{
	return CamComp->GetViewProjMatrix();
}

void ModuleCamera3D::Create_Ray_Mouse()
{
	const Frustum temp_t = CamComp->Get_Frustum();
	float mx = (float)App->input->GetMouseX();
	float my = (float)App->input->GetMouseY();

	mouse_pos.x = -(1.0f - ((mx - App->scene_intro->tx_vec.x) / (App->scene_intro->tx_vec.z / 2.0f)));
	mouse_pos.y = (1.0f - ((my - App->scene_intro->tx_vec.y) / (App->scene_intro->tx_vec.w / 2.0f)));

	LOG("mx: %f", mx - App->scene_intro->tx_vec.x - 12);
	LOG("my: %f", my - App->scene_intro->tx_vec.y - 43);
	r_cast_segm = temp_t.UnProjectLineSegment(mouse_pos.x, mouse_pos.y);

	Recursive_Ray_Distance(App->scene_intro->root_gameobject);

	CheckCollision_Mesh();

}

void ModuleCamera3D::CheckCollision_Mesh()
{
	float dist_min_ray_go = INFINITY;
	for (std::map<float, GameObject*>::iterator it = mymap.begin(); it != mymap.end(); ++it) {
		temp_ray = r_cast_segm;
		GameObject* temp = it->second;
		float dist_to_cam = it->first;
		float4x4 mat_trans = temp->GetMatrix_Trans().Inverted();
		temp_ray.Transform(mat_trans);
		Resource_Mesh_Base* temp_mesh_base = temp->Get_GO_Mesh()->GetGeometryBaseMesh();
		//iterate the index to iterate the tris in order
		float distance = 0;
		float3 hit_point = float3::zero;
		int i = 0;
		if (temp_mesh_base->num_indices >9) {
			//while (i < temp_mesh_base->num_indices - 9) {

			/*float point1[] = {
			temp_mesh_base->vertices[temp_mesh_base->indices[i++]*3],

			};

			float point2[] = {
			temp_mesh_base->vertices[temp_mesh_base->indices[i++]*3],
			};

			float point3[] = {
			temp_mesh_base->vertices[temp_mesh_base->indices[i++]*3],

			};*/


			//}
			while (i < temp_mesh_base->num_indices) {
				Triangle tri;
				tri.a.Set(&temp_mesh_base->vertices[temp_mesh_base->indices[i++] * 3]);
				tri.b.Set(&temp_mesh_base->vertices[temp_mesh_base->indices[i++] * 3]);
				tri.c.Set(&temp_mesh_base->vertices[temp_mesh_base->indices[i++] * 3]);

				if (temp_ray.Intersects(tri, &distance, &hit_point) && dist_to_cam < dist_min_ray_go) {
					Closest_Ray_GO = temp;
					dist_min_ray_go = distance;
				}

			}

		}

	}

}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	CamComp->SetNewFrame(Position, -Z, Y);
}

void ModuleCamera3D::CameraRecenter()
{
	CameraCenter(LCenter);
}

void ModuleCamera3D::CameraCenter(AABB* mesh)
{
	if (mesh == nullptr)
	{
		Reference = float3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		
		float3 centre = mesh->CenterPoint();
		Reference = float3(centre.x, centre.y, centre.z);
		LCenter = mesh;
		Z = (Position - Reference).Normalized();

		//resize
		float3 difference = mesh->maxPoint - mesh->minPoint;
		float wide = difference.Length() + 2.0f; //This magic number is just to have some frame around geometry
		float FOVdistance = (wide * 0.5f) / tan(60.0f * 0.5f * DEGTORAD);
		Position = Z * FOVdistance;
	}

	LookAt(Reference);
}
