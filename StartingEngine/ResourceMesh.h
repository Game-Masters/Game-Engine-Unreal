#pragma once
#include "ModuleResources.h"
#include"MathGeoLib\MathGeoLib.h"
class ResourceMesh :
	public Resource
{
public:
	ResourceMesh();
	~ResourceMesh();
	ResourceMesh(int id);

	//bool LoadInMemory() override;
	//void Save(Config& config) const;
	//void Load(const Config& config);

public:
	LCG uid_rm;
};

