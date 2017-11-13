#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Module.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui/imgui.h"
#include"Imgui\imguidock.h"
#include"ModuleSceneIntro.h"
#include "ModuleCamera3D.h"
#include"ModuleInput.h"
#include"Imgui\ImGuizmo.h"
#include"GameObject.h";
#include"Transform.h"
#include"Mesh.h"
#include"ModuleFileSystem_Engine.h"

#define COLOR_ENGINE ImVec4(0.878, 0.262, 0, 1.0f)
#define MAIN_COLOUR_HARDWARE ImVec4(1.00f, 0.60f, 0.0f, 1.0f)



ModuleGui::ModuleGui(bool start_enabled) : Module(start_enabled), frames_on_last_update(100)
{
	
}

// Destructor
ModuleGui::~ModuleGui()
{
}

bool ModuleGui::Init() {

	

	return true;
}
// Called before render is available
bool ModuleGui::Start()
{

	Gpu_Vram_Stats = m_getMemoryStatistics();
	//IMGUI STYLE START
	ImGuiStyle& style = ImGui::GetStyle();


	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.WindowPadding = ImVec2(12,15);
	style.WindowRounding = 0.0f;
	style.FramePadding = ImVec2(15, 5);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(5,4);
	style.ItemInnerSpacing = ImVec2(14, 14);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;
	
	style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.878, 0.262, 0, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.47f, 0.47, 0.47f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.47f, 0.47, 0.47f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.47f, 0.47, 0.47f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = COLOR_ENGINE;
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.16f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = COLOR_ENGINE;
	style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = COLOR_ENGINE;
	style.Colors[ImGuiCol_HeaderActive] = COLOR_ENGINE;
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.0f, 0.49f, 0.00f, 0.3f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.0f, 0.49f, 0.00f, 0.6);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	//IMGUI STYLE END

	//load things

	App->assimp->LoadImage_devil("Data/Icons/BFC.png",&BFC);
	App->assimp->LoadImage_devil("Data/Icons/CC.png", &CC);
	App->assimp->LoadImage_devil("Data/Icons/N.png", &N);
	App->assimp->LoadImage_devil("Data/Icons/P.png", &P);
	App->assimp->LoadImage_devil("Data/Icons/SM.png", &SM);
	App->assimp->LoadImage_devil("Data/Icons/WF.png", &WF);
	App->assimp->LoadImage_devil("Data/Icons/CA.png", &CA);
	App->assimp->LoadImage_devil("Data/Icons/Q.png", &Q);
	App->assimp->LoadImage_devil("Data/Icons/logo.png", &Logo);
	App->assimp->LoadImage_devil("Data/Icons/Icon.png", &Icon);
	App->assimp->LoadImage_devil("Data/Icons/Daniel.png", &Dani);
	App->assimp->LoadImage_devil("Data/Icons/Nicolas.png", &Nico);
	App->assimp->LoadImage_devil("Data/Icons/Play.png", &Play);
	App->assimp->LoadImage_devil("Data/Icons/Pause.png", &Pause);
	App->assimp->LoadImage_devil("Data/Icons/Stop.png", &Stop);
	App->assimp->LoadImage_devil("Data/Icons/NextFrame.png", &NextFrame);
	App->assimp->LoadImage_devil("Data/Icons/directory-icon.png", &App->fs_e->Dir_Image);
	App->assimp->LoadImage_devil("Data/Icons/fbx-icon.png", &App->fs_e->Fbx_Image);
	App->assimp->LoadImage_devil("Data/Icons/image-icon.png", &App->fs_e->Png_Image);
	//ImGui_ImplSdlGL2_Init(App->window->window);
	ImGui_ImplSdlGL3_Init(App->window->window);
	ImGuiIO& io{ ImGui::GetIO() };
	

	io.Fonts->AddFontFromFileTTF("Data\\Fonts\\Product Sans Bold.ttf", 15);
	Current_Dir = App->fs_e->RootDirect_User->path.c_str();
	str_path_fbx = "-1";
	str_path_img = "-1";
	//io.Fonts->AddFontFromFileTTF("Fonts\Roboto-Regular.ttf", 10);
	//io.Fonts->AddFontFromFileTTF("Fonts\Roboto-Regular.ttf", 14);
	//io.Fonts->AddFontFromFileTTF("Fonts\Roboto-Regular.ttf", 18);
	
	//px = 0;
	inspection_node = nullptr;
	str_geom_user = new char[100];
	str_geom_user = "";
	str_text_user = new char[100];
	str_text_user = "";
	SliderTest_Int_value = new int();
	return true;
}

update_status ModuleGui::PreUpdate(float dt)
{
	//ImGui_ImplSdlGL2_NewFrame(App->window->window);
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	ImGuizmo::BeginFrame();
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) show_editor = !show_editor;
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleGui::Update(float dt)
{



	if (show_editor == false) {
		ImGui::Begin("World_Without_Editor", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
		ImGui::Image((void*)App->scene_intro->world_texture->GetTexture(), ImVec2(App->window->win_width, App->window->win_height), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
	}



	ImVec2 display_size = ImGui::GetIO().DisplaySize;
	ImGui::SetNextWindowSize(display_size);
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("PanelEditor", NULL, ImVec2(0, 0), 1.0f, ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);


	ImGui::Separator();
	
	ImGui::BeginDockspace();
	

	if (show_editor == true) {

		App->Gui_Engine_Modules(dt);
		if (ImGui::BeginDock("Information", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {
			for (std::list<Module*>::iterator item = App->list_modules.begin(); item != App->list_modules.end(); ++item) {
				(*item)->Gui_Engine_Modules(dt);
			}

		}
		ImGui::EndDock();

	
		
		Quat result_rot;
	
		if (ImGui::BeginDock("Inspector", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {
			if (inspection_node != nullptr) {
				InspectionNode_Gui();
			}
		}
		ImGui::EndDock();

		GameObject* temp=nullptr;
	
		if (ImGui::BeginDock("Scene", false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {
			

				if (ImGui::TreeNode(App->scene_intro->root_gameobject->name.c_str())) {
					for (int i = 0; i < App->scene_intro->root_gameobject->Childrens_GameObject_Vect.size(); i++) {
						temp = App->scene_intro->root_gameobject->Childrens_GameObject_Vect[i];
						IterateChilds(temp);

					}
					ImGui::TreePop();
				}
				/*
			if (ImGui::BeginPopupContextItem("Paco")) {
				ImGui::Text("PACOTETE");
				ImGui::EndPopup();
			}
			*/
			ImGui::EndDock();
		}
		//To print information about the geometry in the scene
		
		

		if (ImGui::BeginDock("World", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {
			ImGui::Image((void*)App->scene_intro->world_texture->GetTexture(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::EndDock();

		if (ImGui::BeginDock("Render Options", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_NoTitleBar)) {
			//POINT
			ImGui::Image((void*)P, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Checkbox("##1", &App->renderer3D->points);
			ImGui::SameLine();
			//WIRE
			ImGui::Image((void*)WF, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Checkbox("##2", &App->renderer3D->wireframe);
			ImGui::SameLine();
			//BACKFACE
			ImGui::Image((void*)BFC, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Checkbox("##3", &App->renderer3D->cullface);
			ImGui::SameLine();

			//SHADELESS
			ImGui::Image((void*)SM, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Checkbox("##4", &App->renderer3D->mat);
			ImGui::SameLine();
			//NORMAL
			ImGui::Image((void*)N, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Checkbox("##5", &App->renderer3D->debugnormals);
			ImGui::SameLine();
			ImGui::Text("|||");
			ImGui::SameLine();
			//Stick to camera
			bool temp = ImGui::ImageButton((void*)CC, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1), 0);
			if (temp == true)
			{
				App->camera->CameraRecenter();
			}
			ImGui::SameLine();
			bool temp2 = ImGui::ImageButton((void*)CA, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1), 0);
			if (temp2 == true)
			{
				App->camera->CameraCenter(nullptr);
			}
			ImGui::SameLine();
			bool temp3 = ImGui::ImageButton((void*)Q, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1), 0);
			if (temp3 == true)
			{
				n3 = true;
			}
			ImGui::SameLine();
			ImGui::Text("                             ");
			ImGui::SameLine();
			//ImGui::Begin("##15", NULL, ImVec2(App->window->win_width / 2, 0), 1.0f, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
			if (ImGui::ImageButton((void*)Play, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, -1), 0))
			{
				App->Play();
			}
			ImGui::SameLine();
			if (ImGui::ImageButton((void*)Pause, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, -1), 0))
			{
				App->Pause();
			}
			ImGui::SameLine();
			if (ImGui::ImageButton((void*)Stop, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, -1), 0))
			{
				App->Stop();
			}
			ImGui::SameLine();
			if(ImGui::ImageButton((void*)NextFrame, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, -1), 0))
			{
				App->NextFrame = true;
			}

			//ImGui::End();
			ImGui::SameLine();

			
			if (App->camera->Can_Move_Camera == true)
			{
				ImGui::TextColored(COLOR_ENGINE, "FREE CAMERA MODE ACTIVATED");
			}
			//ImGui::End();
		}
		ImGui::EndDock();
		if (n3 == true)
		{
			ImGui::Begin("Help", &n3);
			ImGui::Image((void*)P, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("POINT MODE");
			ImGui::Image((void*)WF, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("WIREFRAME MODE");
			ImGui::Image((void*)BFC, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("BACKFACE CULLING");

			ImGui::Image((void*)SM, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("SHADELESS");
			ImGui::Image((void*)N, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("NORMALS");
			ImGui::Image((void*)CC, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("CENTER TO OBJECT");
			ImGui::Image((void*)CA, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Text("CENTER TO AXIS");
			ImGui::Text("NOTE:");
			ImGui::Text("If backface culling is activated");
			ImGui::Text("no other buttons will work");
			ImGui::Text("so deactivate it before changing ");
			ImGui::Text("of rendering mode.");
			
			ImGui::End();
		}
		if (n4 == true)
		{
			ImGui::Begin("Controls layout", &n4);
			ImGui::TextColored(COLOR_ENGINE, "CAMERA TYPES");
			ImGui::Text("When the engine is started, the camera is set to default");
			ImGui::Text("press RIGHT CLICK to activate FREE CAMERA MODE \N\N");


			if (ImGui::CollapsingHeader("Default Camera"))
			{
				ImGui::TextColored(COLOR_ENGINE, "ALT+LEFT CLICK");
				ImGui::Text("Click alt+left click to orbit around axis,\n or the center of the object, if there is one");
				ImGui::TextColored(COLOR_ENGINE, "SCROLL WHEEL");
				ImGui::Text("use the scroll wheel to zoom in/ zoom out");
			}
			if (ImGui::CollapsingHeader("Free Camera"))
			{
				ImGui::TextColored(COLOR_ENGINE, "RIGHT CLICK");
				ImGui::Text("Activates the free camera mode");
				ImGui::TextColored(COLOR_ENGINE, "LEFT CLICK");
				ImGui::Text("rotates freely around the world");
				ImGui::TextColored(COLOR_ENGINE, "W A S D");
				ImGui::Text("use w a s d to move around the world");
				ImGui::TextColored(COLOR_ENGINE, "R F");
				ImGui::Text("use R & F to go up or go down in the Y axis");
				ImGui::TextColored(COLOR_ENGINE, "SCROLL WHEEL");
				ImGui::Text("use the scroll wheel to zoom in/ zoom out");
			}
			ImGui::TextColored(COLOR_ENGINE, "\n TABS");
			if (ImGui::CollapsingHeader("##6"))
			{
				ImGui::TextColored(COLOR_ENGINE, " Right tabs\n");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "\n Geometry scene\n");
				ImGui::Text("It displays info of the meshes that are loaded in scene, like position, rotation, texture, texture size and others");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "\n Information\n");
				ImGui::Text("Every important variable of each module is displayed here, like your computer's info, change scene background and others");

				ImGui::TextColored(COLOR_ENGINE, "\n Main tabs\n");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "Rendering options");
				ImGui::Text("Buttons that let you activate different rendering options, check out it's help icon for more...");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "World");
				ImGui::Text("World is displayed");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "About");
				ImGui::Text("Info about the engine and its creators");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "Application");
				ImGui::Text("Performance graphs");
			}
			ImGui::TextColored(COLOR_ENGINE, "\n MENU");
			if (ImGui::CollapsingHeader("##7"))
			{
				ImGui::TextColored(COLOR_ENGINE, "Console");
				ImGui::Text("opens the console");
				ImGui::TextColored(COLOR_ENGINE, "Open github");
				ImGui::Text("opens developer github's page");
				ImGui::TextColored(COLOR_ENGINE, "Close");
				ImGui::Text("closes the app");
			}
			if (ImGui::CollapsingHeader("SPECIAL CONTROLS"))
			{
				ImGui::TextColored(COLOR_ENGINE, "Z");
				ImGui::Text("turns on\off the editor");

			}
			if (ImGui::CollapsingHeader("HOW TO LOAD FBX AND TEXTURES"))
			{
				ImGui::TextColored(COLOR_ENGINE, "DRAG AND DROP ");
				ImGui::Text("drag and drop your files");
			}



			ImGui::End();
		}


	

		if (ImGui::BeginDock("About", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {

			ImGui::Image((void*)Logo, ImVec2(314, 100), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::Text("GameEngine");
			ImGui::Text("We are students from the UPC CITM and we are making a game engine for 3D videogames.");
			ImGui::Text("v0.01");
			ImGui::Text("In the first version we added the ImGui Library and if you run it you should press the 'GRAVE' to show the game engine GUI. Also, if you press F1 button you can move ");
			ImGui::Text("around the 3D world with the mouse.");
			ImGui::Text("V0.02");
			ImGui::Text("A window for all the options of every module, such as: wireframe mode, show normal, size of the window,full screen…");
			ImGui::Text("A window that shows the performance of the engine. You can see the frames average and also the time spend in every module.");
			ImGui::Text("Console to see the outputs of the Engine.");
			ImGui::Text("Drag and drop of FBX in the Engine and importing geometry.");
			ImGui::Text("V0.03 -- WIP -- ");
			ImGui::Text("The geometry is imported with the same transformation and it can have normals and textures");
			ImGui::Text("You can move arround the world using WASD and also the wheel mouse to Zoom if yoy press alt you will rotate the camera arround");
			ImGui::Text("the geometry in the world");
			ImGui::Text("We also added the system of Dock to make the UI of our Engine better");
			ImGui::Text("Added JSON library to access to XML files");


			ImGui::Text("Collaborators Github:");
			ImGui::Image((void*)Nico, ImVec2(150, 150), ImVec2(0, 0), ImVec2(1, -1));
			ImGui::SameLine();
			ImGui::Image((void*)Dani, ImVec2(150, 150), ImVec2(0, 0), ImVec2(1, -1));

			ImGui::Text("        ");
			ImGui::SameLine();
			if (ImGui::Button("Nicolas Babot")) {
				ShellExecuteA(NULL, "open", "https://github.com/nicobabot", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::SameLine();
			ImGui::Text("                    ");

			ImGui::SameLine();
			if (ImGui::Button("Daniel Olondriz")) {
				ShellExecuteA(NULL, "open", "https://github.com/danielolondriz", NULL, NULL, SW_SHOWNORMAL);
			}

		}
		ImGui::EndDock();
	}


	if (ImGui::BeginDock("Assets", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {


		App->fs_e->Asset_Editor(Current_Dir.c_str());

		ImGui::EndDock();
	}


	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
		show_gui_engine = !show_gui_engine;



	//------
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Image((void*)Icon, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, -1));
		ImGui::SameLine();
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Create Empty GameObject")) { create_empty_gameobject = true; }
			if (ImGui::MenuItem("Save")) { App->scene_intro->save_scene = !App->scene_intro->save_scene; }
			if (ImGui::MenuItem("Load")) { App->scene_intro->load_scene = !App->scene_intro->load_scene; }
			if (ImGui::MenuItem("Console")) { show_console = !show_console; }
			if (ImGui::MenuItem("Go to github")) { ShellExecuteA(NULL, "open", "https://github.com/Game-Masters/Game-Engine-Unreal", NULL, NULL, SW_SHOWNORMAL); }
			if (ImGui::MenuItem("Close App")) { button_exit_app = true; }
			ImGui::EndMenu();
		}
		if (create_empty_gameobject)
		{
			GameObject* temp = new GameObject("Empty_Obj",App->scene_intro->root_gameobject,true, Tag_Object_Enum::no_obj_tag,true);
			temp->AddNewTransform(math::float3::zero, math::float3(1, 1, 1), math::Quat(0, 0, 0, 1));
			App->scene_intro->root_gameobject->Childrens_GameObject_Vect.push_back(temp);
			create_empty_gameobject = false;
		}

		bool temp = ImGui::ImageButton((void*)Q, ImVec2(30, 30), ImVec2(0, 0), ImVec2(1, -1), 0);
		if (temp == true)
		{
			n4 = true;
		}
		ImGui::SameLine();
		ImGui::Text("Controls info");
	
		
		ImGui::EndMainMenuBar();

	}
	if (show_console) {
		console_imgui.Enable_Console_Imgui(show_console);
	}

	

	ImGui::EndDockspace();
	ImGui::End();


	if (App->scene_intro->load_scene) {
		ImGui::Begin("Load Directory:", &App->scene_intro->load_scene);

		App->fs_e->IterateAllDirect(App->fs_e->RootDirect_User->path.c_str(), &path_to_load);
		if (path_to_load != "-1") {
			App->json_class->Create_JSON_DOC(&App->scene_intro->root_value_scene, &App->scene_intro->root_object_scene, path_to_load.c_str());
			App->scene_intro->Load_Scene(App->scene_intro->root_object_scene);
			path_to_load = "-1";
			App->scene_intro->load_scene = false;
		}
		ImGui::End();
	}

	if (App->scene_intro->save_scene) {
		ImGui::Begin("Save Directory:", &App->scene_intro->save_scene);
		std::string filename_last = "-1";
		App->fs_e->IterateAllDirect_To_Save(App->fs_e->RootDirect_User->path.c_str(), &path_to_load);
		ImGui::Text("Directory Selected:"); 
		ImGui::SameLine();
		if (path_to_load!="-1") {
			ImGui::Text(path_to_load.c_str());
		}
		else{
			ImGui::Text("");
		}
		if (ImGui::InputText("Filename:", filename_save, 64, ImGuiInputTextFlags_EnterReturnsTrue)) {
			filename_last = path_to_load + "\\" + filename_save;
		}

		if (filename_last != "-1") {

			App->json_class->Create_JSON_DOC(&App->scene_intro->root_value_scene, &App->scene_intro->root_object_scene, filename_last.c_str());
			json_object_clear(App->scene_intro->root_object_scene);
			App->scene_intro->root_gameobject->Save(App->scene_intro->root_object_scene);
			char* serialized_string = json_serialize_to_string_pretty(App->scene_intro->root_value_scene);
			json_serialize_to_file(App->scene_intro->root_value_scene, filename_last.c_str());
			App->scene_intro->save_scene = false;
		}
		ImGui::End();
	}



	if (show_performance)
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

		ImGui::PlotHistogram(fps, &frames_on_last_update[0], frames_on_last_update.size(), 0, fps, 0.0f, 100.f, ImVec2(0, 40));

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

		if (button_rand == true)
		{


			iop = rand_test.Int(0, 100);
			n1 = true;

		}

		if (n1 == true)
		{

			ImGui::SameLine(250);
			ImGui::Text("%i", iop);
		}
		button_rand2 = ImGui::Button("Click here to create random float", ImVec2(0, 0));
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


	
	App->scene_intro->world_texture->Unbind();
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
		ImGui::Text("CPU Cache Line Size:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%i", SDL_GetCPUCacheLineSize());
		ImGui::Text("Number of logical CPU cores:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%i", SDL_GetCPUCount());
		ImGui::Text("The amount of RAM:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%i Gb", SDL_GetSystemRAM() / 1024);

		ImGui::Text("Graphic Card Corporation:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%s", glGetString(GL_VENDOR));
		ImGui::Text("Graphic Card:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%s", glGetString(GL_RENDERER));

		SDL_version sdl_vers;
		SDL_GetVersion(&sdl_vers);

		ImGui::Text("SDL Version patch:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%i", sdl_vers.patch);
		ImGui::Text("SDL Version major:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%i", sdl_vers.major);
		ImGui::Text("SDL Version minor:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%i", sdl_vers.minor);

		ImGui::Text("Devil Version:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "1.7.3");
		ImGui::Text("OpenGL Version:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%s", glGetString(GL_VERSION));
		ImGui::Text("ImGui Version:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%s", IMGUI_VERSION);



		ImGui::Text("Total Reported Mem:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.totalReportedMemory);
		ImGui::Text("Total Actual Mem:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.totalActualMemory);
		ImGui::Text("Peak Reported Mem:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.peakReportedMemory);
		ImGui::Text("Peak Actual Mem:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.peakActualMemory);
		ImGui::Text("Accumulated Reported Mem:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.accumulatedReportedMemory);
		ImGui::Text("Accumulated Actual Mem:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.accumulatedActualMemory);
		ImGui::Text("Accumulated Alloc Unit Count:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.accumulatedAllocUnitCount);
		ImGui::Text("Total Alloc Unit Count:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.totalAllocUnitCount);
		ImGui::Text("Peak Alloc Unit Count:"); ImGui::SameLine(); ImGui::TextColored(MAIN_COLOUR_HARDWARE, "%u", Gpu_Vram_Stats.peakAllocUnitCount);

	}
	return false;
}

// Called before quitting
bool ModuleGui::CleanUp()
{

	aiDetachAllLogStreams();

	return true;
}

void ModuleGui::InspectionNode_Gui()
{
	Transform* t_temp = nullptr;
	Mesh* m_temp = nullptr;
	Material* mat_temp = nullptr;
	Component* Comp_temp = nullptr;
	math::Quat q_temp;
	float3 eul_ang;
	material_base_geometry* temp_v = nullptr;
	math::float3 trans;
	math::float3 scale;
	float3 temp_transf;

	ImGui::Checkbox("##100", &inspection_node->active); ImGui::SameLine();
	ImGui::Text("Name: %s", inspection_node->name.c_str());
	for (int j = 0; j < inspection_node->Component_Vect.size(); j++) {
		bool modify = false;
		Comp_temp = inspection_node->Component_Vect[j];
		switch (Comp_temp->GetComponentType())
		{


		case Component_Type_Enum::component_material_type:
			mat_temp = (Material*)Comp_temp;
			if (mat_temp != nullptr) {
				//temp_v = mat_temp->GetMaterialVec();
				if (temp_v != nullptr) {
					ImGui::Text("Texture path: %s", mat_temp->GetPathMaterial());
					if (temp_v->texture_w_h != nullptr) {
						ImGui::Text("Texture width: %i", temp_v->texture_w_h[0]);
						ImGui::Text("Texture height: %i", temp_v->texture_w_h[1]);
					}
					ImGui::Image((void*)temp_v->id_image_devil, ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, -1));
				}
			}
			break;
		case Component_Type_Enum::component_null_type:
			break;
		case Component_Type_Enum::component_transform_type:
			if (ImGui::CollapsingHeader("Transformation"))
			{
				modify = false;
				t_temp = (Transform*)Comp_temp;
				trans = t_temp->GetPosition();
				temp_transf = trans;
				//ImGui::Text("                                Position");
				ImGui::Text("Pos :"); ImGui::SameLine();
				ImGui::DragFloat3("##6", &trans[0], 0.1f, -500.0f, 500.0f);
				if (trans.x != temp_transf.x || trans.y != temp_transf.y || trans.z != temp_transf.z) {
					//t_temp->SetPosition(trans);
					modify = true;
				}

				scale = t_temp->GetScale();
				temp_transf = scale;
				//ImGui::Text("                                Scale");
				ImGui::Text("Scale:"); ImGui::SameLine();
				ImGui::DragFloat3("##9", &scale[0], 0.1f, 1.0f, 500.0f);

				if (scale.x != temp_transf.x || scale.y != temp_transf.y || scale.z != temp_transf.z) {
					//t_temp->SetScale(scale);
					modify = true;
				}

				q_temp = t_temp->GetRotation();
				eul_ang = q_temp.ToEulerXYZ()*RADTODEG;
				temp_transf = eul_ang;
				//ImGui::Text("                                Rotation");
				ImGui::Text("Rot :"); ImGui::SameLine();
				ImGui::DragFloat3("##12", &eul_ang[0], 0.1f, -180.0f, 180.0f);

				//Not really working
				if (eul_ang.x != temp_transf.x || eul_ang.y != temp_transf.y || eul_ang.z != temp_transf.z) {
					eul_ang *= DEGTORAD;
					q_temp = q_temp.FromEulerXYZ(eul_ang.x, eul_ang.y, eul_ang.z);
					modify = true;
				}

				if (inspection_node->GetTransform() != nullptr && modify == true)
					inspection_node->GetTransform()->SetMatrix(float4x4::FromTRS(trans, q_temp, scale));
			}
			break;
		case Component_Type_Enum::component_mesh_type:
			if (ImGui::CollapsingHeader("Mesh"))
			{
				m_temp = (Mesh*)Comp_temp;
				ImGui::Text("Geometry path: %s", m_temp->GetGeometryPath());
			}
			break;
		default:
			break;
		}

	}ImGui::Separator();

	if (ImGui::Button("Add new Component", ImVec2(250, 30)) && inspection_node)
		ImGui::OpenPopup("Add new Component");
	if (ImGui::BeginPopup("Add new Component"))
	{
		if (ImGui::MenuItem("Component Mesh"))
		{
			if (inspection_node->Get_GO_Mesh() == nullptr) {
				win_choose_fbx = true;
							//App->resources_mod->find
				//inspection_node->AddNewMesh()
			}
		}
		if (ImGui::MenuItem("Component Material"))
		{
			if (inspection_node->Get_GO_Mesh() != nullptr) {
				if (inspection_node->Get_GO_Mesh()->GetMaterial() != nullptr) {
					win_choose_img = true;
				}
			}
		}
		ImGui::EndPopup();
	}


	
	if (win_choose_fbx) {
		ImGui::Begin(("Meshes_dis"), &win_choose_fbx);
		
		App->fs_e->Asset_Editor(App->fs_e->Mesh_User->path.c_str(), &str_path_fbx);
		if (str_path_fbx != "-1") {
			std::string str_path_img_end;
			App->fs_e->ChangeFormat_File(str_path_fbx.c_str(), "ric", &str_path_img_end, App->fs_e->Mesh_Engine);
			int uuid_mesh = App->resources_mod->Find_EngineRes(str_path_img_end.c_str());
			if (uuid_mesh == -1) {
				int uuid_mesh_n = App->resources_mod->ImportFile(str_path_img_end.c_str());
				App->imp_mesh->LoadMesh(str_path_img_end.c_str(), str_path_fbx.c_str());
				//inspection_node->AddNewMesh(uuid_mesh_n);
				win_choose_fbx = false;
			}
			else {
				ResourceMesh* r_mesh= (ResourceMesh*)App->resources_mod->Get(uuid_mesh);
				App->imp_mesh->LoadMesh(r_mesh->GetFile() , r_mesh->GetExportedFile(),inspection_node);
				int p_t = r_mesh->GetUID();
				win_choose_fbx = false;
				//r_mesh->LoadToMemory();
				//inspection_node->AddNewMesh(p_t, r_mesh->GetExportedFile());
			}
		}

		ImGui::End();
	}

	if (win_choose_img) {
		ImGui::Begin(("Texture_dis"), &win_choose_img);

		App->fs_e->Asset_Editor(App->fs_e->Material_User->path.c_str(), &str_path_img);

		if (str_path_img != "-1") {
			int i = 12312;
		}
		ImGui::End();
	}
	
}

void ModuleGui::CreateButtonWithTextAndImage(GLuint temp, const char * str)
{
	ImGui::ImageButton((void*)temp, ImVec2(45, 45), ImVec2(0, 0), ImVec2(1, -1), 0);
	ImGui::Text(str);
	ImGui::AlignFirstTextHeightToWidgets();
}

void ModuleGui::IterateChilds(GameObject * item)
{
	GameObject* temp = nullptr;
	Transform* t_temp = nullptr;
	Mesh* m_temp = nullptr;
	Material* mat_temp= nullptr;
	Component* Comp_temp = nullptr;
	math::Quat q_temp;
	float3 eul_ang;
	material_base_geometry* temp_v;
			if (ImGui::TreeNode(item->name.c_str())) {
				if (ImGui::IsItemClicked()) {
					inspection_node = item;
				}
				ImGui::TreePop();
				for (int k = 0; k < item->Childrens_GameObject_Vect.size(); k++)
					IterateChilds(item->Childrens_GameObject_Vect[k]);

			}



}





