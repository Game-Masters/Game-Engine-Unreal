#include"Globals.h"
#include "Application.h"
#define NODE_CAPACITY = 4;
class GameObject;

class QuadTreeNode
{
public:
	QuadTreeNode();
	~QuadTreeNode();
	void Insert(GameObject* game_object);
	void Clear();
	void Subdivide();
	void Fill();
	std::vector<QuadTreeNode*> GetChildren();
	std::vector<GameObject*> GetGameObjects();

public:

	std::vector<GameObject*> gameobjs;
	std::vector<QuadTreeNode*> children;
};
class QuadTreeZ
{
public:

	QuadTreeZ();
	~QuadTreeZ();
	void Calculate();
	void Clear();
	QuadTreeNode root;
	std::vector<GameObject*> gameobjs;
};