#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Glew\include\glew.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui\imgui.h"
#include"ModuleSceneIntro.h"


ModuleGui::ModuleGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleGui::~ModuleGui()
{
}

// Called before render is available
bool ModuleGui::Start()
{
	glewInit();
	ImGui_ImplSdlGL3_Init(App->window->window);
	ImGuiIO& io{ ImGui::GetIO() };
	//io.IniFilename = "/Settings/imgui.ini";
	SliderTest_Int_value = new int();
	return true;
}


update_status ModuleGui::Update(float dt)
{
	bool test = false;
	test = App->scene_intro->n_sphere_one->Intersects(*App->scene_intro->n_sphere_two);


	ImGui_ImplSdlGL3_NewFrame(App->window->window);

	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
		show_gui_engine = !show_gui_engine;


	if (show_gui_engine) {
		ImGui::ShowTestWindow();
		//------
		ImGui::Begin("Click here to close the APP");

		//to change the font scale of the window
		//ImGui::SetWindowFontScale(1);
		if (ImGui::CollapsingHeader("Widgets"))
		{
			if (ImGui::TreeNode("Bullets"))
			{
				ImGui::BulletText("Bullet point 1");
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Colored Text"))
			{
				// Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");

				ImGui::TreePop();
			}
		}

		button_exit_app = ImGui::Button("Click here to close the APP", ImVec2(0, 0));
		button_rand = ImGui::Button("Click here to create random int", ImVec2(0, 0));
	
		if(button_rand== true)
		{
			
			
			iop = rand_test.Int(0, 100);
			n1 = true;
			
		}
		
		if(n1==true)
		{
			
			ImGui::SameLine(250);
			ImGui::Text("%i", iop);
		}
		button_rand2 = ImGui::Button("Click here to create random floatie", ImVec2(0, 0));
		if (button_rand2 == true)
		{
			iop2 = rand_test.Float(0.0, 1.0);
			n2 = true;
		}
		if (n2 == true)
		{

			ImGui::SameLine(300);
			ImGui::Text("%.4f", iop2);
		}
		
	

		ImGui::Text("Two Spheres intersecting");
		ImGui::SliderFloat("s1", &App->scene_intro->n_sphere_one->pos.x, 2.0, -2.0);
		ImGui::SameLine(350);
		ImGui::Checkbox("Inters", &test);
		ImGui::SliderFloat("s2", &App->scene_intro->n_sphere_two->pos.x, 2.0, -2.0);
		ImGui::SameLine(350);
		ImGui::Checkbox("Inters", &test);

		
		ImGui::End();
	}
	ImGui::Render();



	return UPDATE_CONTINUE;
}

update_status ModuleGui::PostUpdate(float dt)
{
	if (button_exit_app == true) {
		return UPDATE_STOP;
	}
	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleGui::CleanUp()
{
	delete SliderTest_Int_value;
	return true;
}