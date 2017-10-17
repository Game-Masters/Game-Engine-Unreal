#include "ModuleAssimp.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleGui.h"
#include "Module.h"
#include"Imgui/imgui_impl_sdl.h"
#include"Imgui\imgui_impl_sdl_gl3.h"
#include"Imgui/imgui.h"
#include"ModuleSceneIntro.h"
#include"Mesh.h"
#include"Material.h"

ModuleAssimp::ModuleAssimp(bool start_enabled) : Module(start_enabled)
{

}

// Destructor
ModuleAssimp::~ModuleAssimp()
{
}

// Called before render is available
bool ModuleAssimp::Start()
{
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	ilClearColour(255, 255, 255, 000);

	//Check for error
	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		LOG("IlInit error!!");
	}



	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, NULL);
	aiAttachLogStream(&stream);


	/*for (int p = 0; p < meshes_vec.size(); p++) {
		meshes_vec[p]->Initialize();
	}*/

	return true;
}

update_status ModuleAssimp::PreUpdate(float dt)
{



	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAssimp::Update(float dt)
{

	/*for (int p = 0; p < meshes_vec.size(); p++) {
		meshes_vec[p]->Draw();
	}
	
	if (App->input->flie_dropped) {
		if (IsTexture(App->input->dropped_filedir.c_str()) == false) {
			for (int p = 0; p < meshes_vec.size(); p++) {
				delete meshes_vec[p];
			}

			meshes_vec.clear();
		}
		loaded = ImportGeometry(App->input->dropped_filedir.c_str());
		for (int p = 0; p < meshes_vec.size(); p++) {
			meshes_vec[p]->Initialize();
		}

		if (loaded == true)
		{
			App->camera->CameraCenter(&meshes_vec.back()->mesh.BoundBox);
		}

		App->input->flie_dropped = false;


			App->input->flie_dropped = false;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) {
	//	App->camera->CameraRecenter();
	}*/

	return UPDATE_CONTINUE;
}


update_status ModuleAssimp::PostUpdate(float dt)
{

	


	return UPDATE_CONTINUE;
}

bool ModuleAssimp::Gui_Engine_Modules(float dt)
{

	if (ImGui::CollapsingHeader(name.c_str()))
	{
		
		

	}
	return true;

}


// Called before quitting
bool ModuleAssimp::CleanUp()
{

	



	return true;
}


std::vector<geometry_base_creating*> ModuleAssimp::ImportGeometry(const char* fbx)
{

	//----------------ASSIMP
	std::vector<geometry_base_creating*> mesh_v_temp;

	std::string full_path;
	full_path = fbx;
	std::size_t pos_to_find = full_path.rfind("\\");
	std::string Imp_Path = full_path.substr(0, pos_to_find + 1);

	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++) {

			LOG("Mesh imported %i----------------", i);
			m = new geometry_base_creating();
			m->num_vertices = scene->mMeshes[i]->mNumVertices;
			m->vertices = new float[m->num_vertices * 3];
        LOG("New mesh with %d vertices", m->num_vertices);
			memcpy(m->vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m->num_vertices * 3);
			if (m->vertices==nullptr) {
				LOG("The new mesh has failed trying to import the vertices");
			}
			else {
				LOG("The new mesh has succed trying to import the vertices");
			}        
        //Generate bounding bax
			m->BoundBox.SetNegativeInfinity();
			m->BoundBox.Enclose((float3*)m->vertices, m->num_vertices);
			App->camera->CameraCenter(&m->BoundBox);
			LOG("A BoundBox has been added to the mesh", m->num_vertices);
			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
        m->num_tris = scene->mMeshes[i]->mNumFaces;
				m->num_indices = scene->mMeshes[i]->mNumFaces * 3;
        	LOG("The mesh has %d triangles", m->num_tris);
				m->indices = new uint[m->num_indices]; // assume each face is a triangle
			 LOG("The mesh has %d indices", m->num_indices);

				for (uint k = 0; k < scene->mMeshes[i]->mNumFaces; ++k)
				{
					if (scene->mMeshes[i]->mFaces[k].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else {
						memcpy(&m->indices[k * 3], scene->mMeshes[i]->mFaces[k].mIndices, 3 * sizeof(uint));
					}
				}
			}
			if (m->indices == nullptr) {
				LOG("The new mesh has failed trying to import the indices");
			}
			else {
				LOG("The new mesh has succed trying to import the indices");
			}

			if (scene->mMeshes[i]->HasNormals()) {

				LOG("The new mesh has normals");
		    m->normals = new float[m->num_vertices * 3];
				memcpy(m->normals, scene->mMeshes[i]->mNormals, sizeof(float) * m->num_vertices * 3);
				if (m->normals == nullptr) {
					LOG("The new mesh has failed trying to import the normals");
				}
				else {
					LOG("The new mesh has succed trying to import the normals");
				}
			}
			else {
				LOG("The new mesh has not normals so the engine cannot import them");
			}

			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion rotation;
			
			aiNode* nod =Calc_AllGeometry_Childs(scene->mRootNode, i);
			aiMatrix4x4 temp_trans;
			if (nod != nullptr) {
				while (nod->mParent != nullptr) {
					temp_trans *= nod->mTransformation;
					nod = nod->mParent;
				}
				LOG("The new mesh is imported in the same position as in the original file");
			}
			else {
				LOG("The new mesh has failed trying to import the transformation of the geometry");
			}
			temp_trans.Decompose(scaling, rotation, translation);
			m->translation.Set(translation.x, translation.y, translation.z);
			m->scaling.Set(scaling.x, scaling.y, scaling.z);
			m->rotation.Set(rotation.x, rotation.y, rotation.z, rotation.w);
			
			// texture coords (only one texture for now)

			/*if (scene->mMeshes[i]->HasTextureCoords(0))
			{
        LOG("The new mesh has normals");
				m->textures_coord = new float[m->num_vertices * 2];


				for (int z = 0; z < scene->mMeshes[i]->mNumVertices; ++z) {

					m->textures_coord[z * 2] = scene->mMeshes[i]->mTextureCoords[0][z].x;
					m->textures_coord[z * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][z].y;


				}

				if (m->textures_coord == nullptr) {
					LOG("The new mesh has failed trying to import the texture coords");
				}
				
			}
			else {
				LOG("The mesh doesn't have texture");
			}
			

			aiMaterial* material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
			uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);
			
			aiString path;
			uint p;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
			std::string temp = path.C_Str();
			path = Imp_Path + temp;
			m->texture_str = path.C_Str();*/

			

			mesh_v_temp.push_back(m);



		}
		
		aiReleaseImport(scene);
	}

		return mesh_v_temp;
	
}



std::vector<material_base_geometry*> ModuleAssimp::ImportGeometry_Texture(const char* fbx)
{

	//----------------ASSIMP
	std::vector<material_base_geometry*> mesh_v_temp;

	std::string full_path;
	full_path = fbx;
	const aiScene* scene = aiImportFile(full_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++) {
			mat_geom = new material_base_geometry();
			mat_geom->num_vertices = scene->mMeshes[i]->mNumVertices;
			
			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				mat_geom->textures_coord = new float[mat_geom->num_vertices * 2];

				for (int z = 0; z < scene->mMeshes[i]->mNumVertices; ++z) {

					mat_geom->textures_coord[z * 2] = scene->mMeshes[i]->mTextureCoords[0][z].x;
					mat_geom->textures_coord[z * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][z].y;


				}

			}

			mesh_v_temp.push_back(mat_geom);

		}
		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene %s", full_path);
	}
	//aiMesh

	return mesh_v_temp;

}


uint* ModuleAssimp::LoadImage_devil(const char * theFileName, GLuint *buff)
{
	uint* texture_w_h = nullptr;
	//Texture loading success
	bool textureLoaded = false;

	//Generate and set current image ID
	uint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	//Load image
	ILboolean success = ilLoadImage(theFileName);

	//Image loaded successfully
	if (success == IL_TRUE)
	{
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		//Convert image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE)
		{
			textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT), buff);
			texture_w_h = new uint(1);
			texture_w_h[0]= (uint)ilGetInteger(IL_IMAGE_WIDTH); texture_w_h[1] = (uint)ilGetInteger(IL_IMAGE_HEIGHT);
			//Create texture from file pixels
			textureLoaded = true;
		}

		//Delete file from memory
		ilDeleteImages(1, &imgID);
	}

	return texture_w_h;

}

bool ModuleAssimp::loadTextureFromPixels32(GLuint * id_pixels, GLuint width_img, GLuint height_img, GLuint *buff)
{


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, buff);
	glBindTexture(GL_TEXTURE_2D, *buff);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img,
		0, GL_RGBA, GL_UNSIGNED_BYTE, id_pixels);
	glBindTexture(GL_TEXTURE_2D, NULL);
	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error loading texture from %p pixels! %s\n", id_pixels, gluErrorString(error));
		return false;
	}

	return true;
}

bool ModuleAssimp::IsTexture(const char * path)
{
	bool ret = false;

	uint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	//Load image
	ILboolean success = ilLoadImage(path);
	if (success) {
		ret = true;
	}
	ilDeleteImages(1, &imgID);

	return ret;
}


aiNode* ModuleAssimp::Calc_AllGeometry_Childs(aiNode* Parent_node, uint search_mesh) {

	aiNode* temp;
	if (Parent_node != nullptr) {
		int i;
		for (i = 0; i < Parent_node->mNumChildren; i++) {
			for (int j = 0; j < Parent_node->mChildren[i]->mNumMeshes; j++) {
				if (Parent_node->mChildren[i]->mMeshes[j] == search_mesh) {
					return Parent_node->mChildren[i];
				}
			}
			if (Parent_node->mNumChildren > 0) {
				temp = Calc_AllGeometry_Childs(Parent_node->mChildren[i], search_mesh);
				if (temp != nullptr)
					return temp;
			}
		}	
		
		

	}
	return nullptr;

}

