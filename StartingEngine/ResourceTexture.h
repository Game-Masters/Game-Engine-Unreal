#pragma once
#include "ModuleResources.h"
#include"Application.h"
#include"MathGeoLib\MathGeoLib.h"
enum Format {
	color_index,
	rgb,
	rgba,
	bgr,
	bgra,
	luminance,
	unknown_form
};


class ResourceTexture :
	public Resource
{
public:
	ResourceTexture();
	virtual ~ResourceTexture();
	ResourceTexture(int id);
	bool LoadToMemory();
	//bool LoadInMemory() override;
	//void Save(Config& config) const;
	//void Load(const Config& config);

public:
	LCG uid_rt;
	uint width = 0;
	uint height = 0;
	uint depth = 0;
	uint mips = 0;
	uint bytes = 0;
	uint gpu_id = 0;
	uint id_image_devil = 0;
	Format format = Format::unknown_form;

};

