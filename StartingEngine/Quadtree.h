#include"Globals.h"
#include "Application.h"
#define NODE_CAPACITY  4
class GameObject;

class QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(float3 min_point, float3 max_point, int max_objects);
	~QuadTreeNode();
	void Insert(GameObject* game_object);
	void Erase(GameObject* game_object);
	void Clear();
	void Subdivide();
	void Fill();
	std::vector<QuadTreeNode*> GetChildren();
	std::vector<GameObject*> GetGameObjects();
	bool IsLeaf() const;

public:

	std::vector<GameObject*> gameobjs;
	std::vector<QuadTreeNode*> children;
	QuadTreeNode* parent = nullptr;
	AABB bounds;
	int max_game_objects = NODE_CAPACITY;
};


class QuadTreeZ
{
public:

	QuadTreeZ();
	~QuadTreeZ();
	void Calculate();
	void SetBoundaries(const AABB& bounds);
	void Insert(GameObject*  game_object);
	void Erase(GameObject*  game_object);
	void Clear();
	QuadTreeNode root;
	std::vector<GameObject*> gameobjs;
};