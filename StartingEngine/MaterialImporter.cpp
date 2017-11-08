#include "MaterialImporter.h"
#include"Application.h"
#include"ModuleFileSystem_Engine.h"

MaterialImporter::MaterialImporter()
{
}


MaterialImporter::~MaterialImporter()
{
}


void MaterialImporter::ImportMaterial(const char * path, std::string *new_path)
{

	char* buffer = nullptr;
	std::string str = path;
	size_t s_type = str.rfind(".");
	s_type += 1;
	std::string str_ex = str.substr(s_type, str.size());
	std::string str_path_to_load;
	App->fs_e->ChangeFormat_File(path, str_ex.c_str(), &str_path_to_load, App->fs_e->Material_User);
	int size_buffer = App->fs_e->LoadFile(str_path_to_load.c_str(), &buffer);
	if (buffer != nullptr && size_buffer > 0) {

		uint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);
		ILboolean success = ilLoadImage(str_path_to_load.c_str());
		if (success == IL_TRUE) {
			ILuint size;
			ILubyte *data;
			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use
			size = ilSaveL(IL_DDS, NULL, 0); // Get the size of the data buffer
			if (size > 0) {
				data = new ILubyte[size]; // allocate data buffer
				if (ilSaveL(IL_DDS, data, size) > 0) {// Save to buffer with the ilSaveIL function
					std::string final_path;
					App->fs_e->ChangeFormat_File(str_path_to_load.c_str(), "dds", &final_path,App->fs_e->Material_Engine);
					App->fs_e->SaveFile(final_path.c_str(), (char*)data, size);
					*new_path = final_path;
				}
				//ret = App->fs_e->SaveFile(output_file, data, size, LIBRARY_TEXTURES_FOLDER, "texture", "dds");
				RELEASE_ARRAY(data);
			}
			ilDeleteImages(1, &imgID);
		}
	}
	RELEASE_ARRAY(buffer);

}
