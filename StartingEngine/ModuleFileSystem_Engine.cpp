#include "ModuleFileSystem_Engine.h"
#include<filesystem>
#include <iostream>
#include<fstream>


bool ModuleFileSystem_Engine::Start()
{

	std::experimental::filesystem::create_directory("Assets");
	//Test
	//char *buffer = new char(9999999);
	//LoadFile("..\\Game\\Assets\\Test1", &buffer);
	//buffer =  "1341343242423";
	//SaveFile("..\\Game\\Assets\\Test1", &buffer, 9999999);
	//char *buffer2 = new char(9999999);
	//LoadFile("..\\Game\\Assets\\Test1", &buffer2);

	return true;
}

bool ModuleFileSystem_Engine::CleanUp()
{
	return false;
}

bool ModuleFileSystem_Engine::LoadFile(const char * path, char ** buffer)
{
	bool ret = false;
	std::ifstream file_stream (path, std::ifstream::binary);
	
	if (file_stream.bad()) {
		LOG("The file %s cannot be readed", path);
	}
	else {
		if (file_stream) {
			//Read file explanation http://www.cplusplus.com/reference/istream/istream/read/
			// get length of file:
			file_stream.seekg(0, file_stream.end);
			int length_file = file_stream.tellg();
			file_stream.seekg(0, file_stream.beg);
			LOG("Reading File %s of %i characters", path, length_file);
			*buffer = new char[length_file];
			// read data as a block:
			file_stream.read(*buffer, length_file);

			if (file_stream) {
				LOG("File load correctly");
				ret = true;
			}
			else {
				LOG("File load without succes");
				ret = false;
			}

			file_stream.close();

		}
	}
	return ret;
}

bool ModuleFileSystem_Engine::SaveFile(const char * path, char ** buffer, uint size)
{
	//Save file documentation http://www.cplusplus.com/reference/ostream/ostream/write/
	bool ret = false;
	std::ofstream outfile(path, std::ofstream::binary);

	if (outfile.good()) {
		// write to outfile
		outfile.write(*buffer, size);
	}
	else {
		LOG("Failed to write the file %s", path);
	}


	outfile.close();
	return ret;
}

ModuleFileSystem_Engine::ModuleFileSystem_Engine()
{
}


ModuleFileSystem_Engine::~ModuleFileSystem_Engine()
{
}
