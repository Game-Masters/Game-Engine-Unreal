#include "MaterialImporter.h"
#include"Application.h"
#include"ModuleFileSystem_Engine.h"

MaterialImporter::MaterialImporter()
{
}


MaterialImporter::~MaterialImporter()
{
}


void MaterialImporter::ImportMaterial(const char * path)
{

	char* buffer = nullptr;
	int size_buffer = App->fs_e->LoadFile(path, &buffer);
	if (buffer != nullptr && size_buffer > 0) {

		uint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);
		ILboolean success = ilLoadImage(path);
		if (success == IL_TRUE) {
			ILuint size;
			ILubyte *data;
			ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use
			size = ilSaveL(IL_DDS, NULL, 0); // Get the size of the data buffer
			if (size > 0) {
				data = new ILubyte[size]; // allocate data buffer
				if (ilSaveL(IL_DDS, data, size) > 0) {// Save to buffer with the ilSaveIL function
					std::string final_path;
					App->fs_e->ChangeFormat_File(path, "dds", &final_path,App->fs_e->Material);
					App->fs_e->SaveFile(final_path.c_str(), (char*)data, size);
				}
				//ret = App->fs_e->SaveFile(output_file, data, size, LIBRARY_TEXTURES_FOLDER, "texture", "dds");
				RELEASE_ARRAY(data);
			}
			ilDeleteImages(1, &imgID);
		}
	}


}
