#include"Globals.h"
#include "Application.h"
#define NODE_CAPACITY  6
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
	bool Full() const;
	bool InsideTree(std::vector<GameObject*>::iterator it, QuadTreeNode* node);
	bool IsSmall();
	void DebugDraw() const;
	
public:

	std::vector<GameObject*> gameobjs;
	std::vector<QuadTreeNode*> children;
	QuadTreeNode* parent = nullptr;
	AABB bounds;
	int max_game_objects = NODE_CAPACITY;
	float3 min{ 0,0,0 };
	float3 max{ 1,1,1 };
private:
	
	AABB MinAbb = AABB(min, max);
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
	void Clear()const;
	void DebugDraw() const;
	void AdaptativeBoundaries(AABB temp);
	QuadTreeNode* root;
	std::vector<GameObject*> gameobjs;
	float3 QuadMin;
	float3 QuadMax;
};