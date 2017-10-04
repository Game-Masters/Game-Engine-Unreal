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
	//IMGUI STYLE START
	ImGuiStyle& style = ImGui::GetStyle();


	
	style.WindowPadding = ImVec2(10, 15);
	style.WindowRounding = 2.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 2.0f;
	style.ItemSpacing = ImVec2(4,4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 2.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 2.0f;
	
	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.47f, 0.47, 0.47f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.47f, 0.47, 0.47f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.47f, 0.47, 0.47f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	//IMGUI STYLE END
	//ImGui_ImplSdlGL2_Init(App->window->window);
	ImGui_ImplSdlGL3_Init(App->window->window);
	ImGuiIO& io{ ImGui::GetIO() };
	
	io.Fonts->AddFontFromFileTTF("..\\Game\\Fonts\\OpenSans-Regular.ttf", 16);

	//io.Fonts->AddFontFromFileTTF("Fonts\Roboto-Regular.ttf", 10);
	//io.Fonts->AddFontFromFileTTF("Fonts\Roboto-Regular.ttf", 14);
	//io.Fonts->AddFontFromFileTTF("Fonts\Roboto-Regular.ttf", 18);


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

	

	ImGui::Begin("Info", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {
		(*item)->Gui_Engine_Modules(dt);
	}
	
	ImGui::End();
	

	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
		show_gui_engine = !show_gui_engine;


	
		//------
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				
				
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
		ImGui::Text("CPU Cache Line Size:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%i", SDL_GetCPUCacheLineSize());
		ImGui::Text("Number of logical CPU cores:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%i", SDL_GetCPUCount());
		ImGui::Text("The amount of RAM:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%i Gb", SDL_GetSystemRAM() / 1024);

		ImGui::Text("Graphic Card Corporation:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%s", glGetString(GL_VENDOR));
		ImGui::Text("Graphic Card:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%s", glGetString(GL_RENDERER));
		ImGui::Text("Graphic Card Version:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%s", glGetString(GL_VERSION));

		SDL_version sdl_vers;
		SDL_GetVersion(&sdl_vers);

		ImGui::Text("SDL Version patch:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%i", sdl_vers.patch);
		ImGui::Text("SDL Version major:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%i", sdl_vers.major);
		ImGui::Text("SDL Version minor:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1.00f, 0.60f, 0.0f, 1.0f), "%i", sdl_vers.minor);

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
	aiDetachAllLogStreams();

	return true;
}