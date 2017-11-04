#include "Globals.h"
#include "Application.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"
#include "ModulePlayer.h"
#include "CameraFrustrum.h"

#define X_AXIS float3(1.0f, 0.0f, 0.0f)
#define Y_AXIS float3(0.0f, 1.0f, 0.0f)
#define Z_AXIS float3(0.0f, 0.0f, 1.0f)


ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled)
{
	
	zoom = 50;
	X = X_AXIS;
	Y = Y_AXIS;
	Z = Z_AXIS;

	Position = float3(2.0f, 2.0f, 2.0f);
	Reference = float3(0.0f, 0.0f, 0.0f);


	
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;
	CamComp = new CameraComponent(App->scene_intro->root_gameobject,true);
	CalculateViewMatrix();


	//CamComp = App->scene_intro->frustrumtest->;
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
	float3x3 cam_rot_mouse_x;
	float3x3 cam_rot_mouse_y;
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

	// Recalculate matrix -------------

	

	return UPDATE_CONTINUE;
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
	const float* temp_t = CamComp->GetViewProjMatrix();
	return temp_t;
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
