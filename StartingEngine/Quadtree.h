#include"Globals.h"
#include "Application.h"
#define NODE_CAPACITY  4
class GameObject;

class QuadTreeNode
{
public:
	QuadTreeNode();
	QuadTreeNode(AABB* box);
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
	bool Full();
	bool InsideTree(std::vector<GameObject*>::iterator it, QuadTreeNode* node);
	bool IsSmall();
	void DebugDraw();
public:

	std::vector<GameObject*> gameobjs;
	std::vector<QuadTreeNode*> children;
	QuadTreeNode* parent = nullptr;
	AABB bounds;
	int max_game_objects = NODE_CAPACITY;
private:
	float3 min { 0,0,0 };
	float3 max2 { 10,200,10 };
	AABB MinAbb = AABB(min, max2);
};


class QuadTreeZ
{
public:

	QuadTreeZ();
	~QuadTreeZ();
	void Calculate();
	void SetBoundaries(const AABB* bounds);
	void Insert(GameObject*  game_object);
	void Erase(GameObject*  game_object);
	void Clear();
	void DebugDraw();
	QuadTreeNode* root;
	std::vector<GameObject*> gameobjs;
};