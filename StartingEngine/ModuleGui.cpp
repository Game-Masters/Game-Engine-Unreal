#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Module.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui/imgui.h"
#include"ModuleSceneIntro.h"
#define IM_ARRAYSIZE(_ARR)      ((int)(sizeof(_ARR)/sizeof(*_ARR)))

ModuleGui::ModuleGui(bool start_enabled) : Module(start_enabled), frames_on_last_update(100)
{
	
}

// Destructor
ModuleGui::~ModuleGui()
{
}

// Called before render is available
bool ModuleGui::Start()
{
	
	//ImGui_ImplSdlGL2_Init(App->window->window);
	ImGui_ImplSdlGL3_Init(App->window->window);
	ImGuiIO& io{ ImGui::GetIO() };

	SliderTest_Int_value = new int();
	return true;
}

update_status ModuleGui::PreUpdate(float dt)
{
	//ImGui_ImplSdlGL2_NewFrame(App->window->window);
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{


	bool test = false;
	ImGui::Begin("Info");
	for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {
		(*item)->Gui_Engine_Modules(dt);
	}
	ImGui::End();
	test = App->scene_intro->n_sphere_one->Intersects(*App->scene_intro->n_sphere_two);


	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
		show_gui_engine = !show_gui_engine;


	
		//------
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				
				if (ImGui::MenuItem("Show/Hide menu")) { show_gui_engine = !show_gui_engine; }
				if (ImGui::MenuItem("Console")) { show_console = !show_console; }
				if (ImGui::MenuItem("Performance")) { show_performance = !show_performance; }
				if (ImGui::MenuItem("Close App")){button_exit_app = true;}


				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();

		}
		console_imgui.Enable_Console_Imgui(show_console);
		if(show_performance)
		{
			const char* fps = "fps";
			
			//frames_on_last_update.push_back(App->frames_on_last_update);
			static uint count = 0;

			if (count >= 100)
				for (int i = 0; i < 100 - 1; i++)
				{
					frames_on_last_update[i] = frames_on_last_update[i + 1];
					
				}
			else
				count++;
			frames_on_last_update[count - 1] = App->frames_on_last_update;

			ImGui::PlotHistogram(fps, &frames_on_last_update[0], frames_on_last_update.size(), 0, fps, 0.0f,100.f, ImVec2(0, 40));

			std::list<Module*>::iterator item = App->list_modules.begin();
			
				while (item != App->list_modules.end())
				 {
				
					const char* name = (*item)->name.c_str();
				
					(*item)->performance[(*item)->performance_offset] = (*item)->module_timer->Read_ms();
				(*item)->performance_offset = ((*item)->performance_offset + 1) % IM_ARRAYSIZE((*item)->performance);
				
					ImGui::PlotHistogram((char*)name, (*item)->performance, IM_ARRAYSIZE((*item)->performance), 0, name, 0.0f, 30.f, ImVec2(0, 40));
				item++;
				}
		}
		if (show_gui_engine) {
			ImGui::ShowTestWindow();
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

		//button_exit_app = ImGui::Button("Click here to close the APP", ImVec2(0, 0));
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

bool ModuleGui::Gui_Engine_Modules(float dt)
{
	if (ImGui::CollapsingHeader("Hardware"))
	{
		ImGui::Text("CPU Cache Line Size:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", SDL_GetCPUCacheLineSize());
		ImGui::Text("Number of logical CPU cores:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", SDL_GetCPUCount());
		ImGui::Text("The amount of RAM:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i Gb", SDL_GetSystemRAM() / 1024);

		ImGui::Text("Graphic Card Corporation:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_VENDOR));
		ImGui::Text("Graphic Card:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_RENDERER));
		ImGui::Text("Graphic Card Version:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_VERSION));

		SDL_version sdl_vers;
		SDL_GetVersion(&sdl_vers);

		ImGui::Text("SDL Version patch:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", sdl_vers.patch);
		ImGui::Text("SDL Version major:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", sdl_vers.major);
		ImGui::Text("SDL Version minor:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", sdl_vers.minor);

		/*
		SDL_version sdl_vers_ret;
		SDL_VERSION(&sdl_vers_ret);

		ImGui::Text("SDL Version patch:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", sdl_vers_ret.patch);
		ImGui::Text("SDL Version major:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", sdl_vers_ret.major);
		ImGui::Text("SDL Version minor:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%i", sdl_vers_ret.minor);*/


	}
	return false;
}


// Called before quitting
bool ModuleGui::CleanUp()
{
	delete SliderTest_Int_value;
	return true;
}