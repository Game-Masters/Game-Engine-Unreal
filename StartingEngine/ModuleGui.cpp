#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Module.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui/imgui.h"
#include"Imgui\imguidock.h"
#include"ModuleSceneIntro.h"

#include "Fluid_Studios_Memory_Manager\mmgr.h"
#include "Fluid_Studios_Memory_Manager\nommgr.h"
#include "ModuleCamera3D.h"


#include"GameObject.h";
#include"Transform.h"
#include"Mesh.h"


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
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] =ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
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
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.16f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.46f, 0.0f, 1.00f);
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
	//ImGui_ImplSdlGL2_Init(App->window->window);
	ImGui_ImplSdlGL3_Init(App->window->window);
	ImGuiIO& io{ ImGui::GetIO() };
	

	io.Fonts->AddFontFromFileTTF("Data\\Fonts\\OpenSans-Regular.ttf", 16);


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
			for (std::list<Module*>::reverse_iterator item = App->list_modules.rbegin(); item != App->list_modules.crend(); ++item) {

				(*item)->Gui_Engine_Modules(dt);
			}

		}
		ImGui::EndDock();


		Transform* t_temp = nullptr;
		Mesh* m_temp = nullptr;
		Component* Comp_temp = nullptr;
		if (ImGui::BeginDock("Inspector", false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {
			for (int i = 0; i < App->scene_intro->root_gameobject->Childrens_GameObject_Vect.size(); i++) {
				for (int j = 0; j < App->scene_intro->root_gameobject->Childrens_GameObject_Vect[i]->Component_Vect.size(); j++) {
					Comp_temp = App->scene_intro->root_gameobject->Childrens_GameObject_Vect[i]->Component_Vect[j];
					switch (Comp_temp->GetComponentType())
					{
					case Component_Type_Enum::component_transform_type:
						t_temp = (Transform*)Comp_temp;
						ImGui::Text("Pos x: %f", t_temp->GetPosition().x);
						ImGui::Text("Pos y: %f", t_temp->GetPosition().y);
						ImGui::Text("Pos z: %f", t_temp->GetPosition().z);

						break;
					case Component_Type_Enum::component_mesh_type:
						m_temp = (Mesh*)Comp_temp;
						ImGui::Text("Geometry path: %s", m_temp->GetGeometryPath());
						break;
					default:
						break;
					}
				}
			}

		}
		ImGui::EndDock();


		//To print information about the geometry in the scene
		if (ImGui::BeginDock("Geometry Scene", false, false, false/*, App->IsPlaying()*/, ImGuiWindowFlags_HorizontalScrollbar)) {
			/*for (int p = 0; p < App->assimp->meshes_vec.size(); p++) {

				ImGui::Text("");
				ImGui::Text("Mesh %i", p + 1);

				ImGui::Text("Mesh triangles %i", App->assimp->meshes_vec[p]->mesh.num_tris);

				float3 t_temp = App->assimp->meshes_vec[p]->mesh.translation;

				ImGui::Text("Translation.x %f", t_temp.x);
				ImGui::Text("Translation.x %f", t_temp.y);
				ImGui::Text("Translation.x %f", t_temp.z);
				math::Quat q_temp = App->assimp->meshes_vec[p]->mesh.rotation;
				float3 eul_ang = q_temp.ToEulerXYZ()*RADTODEG;
				ImGui::Text("");
				ImGui::Text("Rotation.x %f", eul_ang.x);
				ImGui::Text("Rotation.y %f", eul_ang.y);
				ImGui::Text("Rotation.z %f", eul_ang.z);

				float3 s_temp = App->assimp->meshes_vec[p]->mesh.scaling;
				ImGui::Text("");
				ImGui::Text("Scale.x %f", s_temp.x);
				ImGui::Text("Scale.y %f", s_temp.y);
				ImGui::Text("Scale.z %f", s_temp.z);
				ImGui::Text("-------------------------");

				ImGui::Text("Texture Information");
				ImGui::Text("Path: %s", App->assimp->meshes_vec[p]->mesh.texture_str.c_str());
				if (App->assimp->meshes_vec[p]->mesh.texture_w_h_geom != nullptr) {
					ImGui::Text("Texture Width: %i", App->assimp->meshes_vec[p]->mesh.texture_w_h_geom[0]);
					ImGui::Text("Texture Height: %i", App->assimp->meshes_vec[p]->mesh.texture_w_h_geom[1]);
				}
				ImGui::Image((void*)App->assimp->meshes_vec[p]->mesh.id_image_devil, ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, -1));
			}*/

		}
		ImGui::EndDock();

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
			ImGui::Text("Render info");
			ImGui::SameLine();
			if (App->camera->Can_Move_Camera == true)
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "FREE CAMERA MODE ACTIVATED");
			}

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
			ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "CAMERA TYPES");
			ImGui::Text("When the engine is started, the camera is set to default");
			ImGui::Text("press RIGHT CLICK to activate FREE CAMERA MODE \N\N");


			if (ImGui::CollapsingHeader("Default Camera"))
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "ALT+LEFT CLICK");
				ImGui::Text("Click alt+left click to orbit around axis,\n or the center of the object, if there is one");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "SCROLL WHEEL");
				ImGui::Text("use the scroll wheel to zoom in/ zoom out");
			}
			if (ImGui::CollapsingHeader("Free Camera"))
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "RIGHT CLICK");
				ImGui::Text("Activates the free camera mode");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "LEFT CLICK");
				ImGui::Text("rotates freely around the world");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "W A S D");
				ImGui::Text("use w a s d to move around the world");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "R F");
				ImGui::Text("use R & F to go up or go down in the Y axis");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "SCROLL WHEEL");
				ImGui::Text("use the scroll wheel to zoom in/ zoom out");
			}
			ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "\n TABS");
			if (ImGui::CollapsingHeader("##6"))
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), " Right tabs\n");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "\n Geometry scene\n");
				ImGui::Text("It displays info of the meshes that are loaded in scene, like position, rotation, texture, texture size and others");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "\n Information\n");
				ImGui::Text("Every important variable of each module is displayed here, like your computer's info, change scene background and others");

				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "\n Main tabs\n");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "Rendering options");
				ImGui::Text("Buttons that let you activate different rendering options, check out it's help icon for more...");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "World");
				ImGui::Text("World is displayed");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "About");
				ImGui::Text("Info about the engine and its creators");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 0.70f), "Application");
				ImGui::Text("Performance graphs");
			}
			ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "\n MENU");
			if (ImGui::CollapsingHeader("##7"))
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "Console");
				ImGui::Text("opens the console");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "Open github");
				ImGui::Text("opens developer github's page");
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "Close");
				ImGui::Text("closes the app");
			}
			if (ImGui::CollapsingHeader("SPECIAL CONTROLS"))
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "Z");
				ImGui::Text("turns on\off the editor");

			}
			if (ImGui::CollapsingHeader("HOW TO LOAD FBX AND TEXTURES"))
			{
				ImGui::TextColored(ImVec4(1.00f, 0.46f, 0.0f, 1.00f), "DRAG AND DROP ");
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


	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
		show_gui_engine = !show_gui_engine;



	//------
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Image((void*)Icon, ImVec2(25, 25), ImVec2(0, 0), ImVec2(1, -1));
		ImGui::SameLine();
		if (ImGui::BeginMenu("Menu"))
		{

			if (ImGui::MenuItem("Console")) { show_console = !show_console; }
			if (ImGui::MenuItem("Go to github")) { ShellExecuteA(NULL, "open", "https://github.com/Game-Masters/Game-Engine-Unreal", NULL, NULL, SW_SHOWNORMAL); }
			if (ImGui::MenuItem("Close App")) { button_exit_app = true; }
			ImGui::EndMenu();
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

		sMStats Gpu_Vram_Stats = m_getMemoryStatistics();

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