#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Glew\include\glew.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui\imgui.h"

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
		ImGui::SliderInt("Slider to test", SliderTest_Int_value, 0, 100);
		ImGui::Text("Hello, world!");
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