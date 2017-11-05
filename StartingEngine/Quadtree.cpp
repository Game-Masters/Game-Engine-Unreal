#include "Quadtree.h"

//QUADTREE NODE
QuadTreeNode::QuadTreeNode()
{
}

QuadTreeNode::~QuadTreeNode()
{
}

void QuadTreeNode::Insert(GameObject * game_object)
{
	gameobjs.push_back(game_object);
}

void QuadTreeNode::Clear()
{
	for (std::vector<QuadTreeNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		RELEASE(*it);
	}
	children.clear();
	gameobjs.clear();
}

void QuadTreeNode::Subdivide()
{
}

void QuadTreeNode::Fill()
{
}

std::vector<QuadTreeNode*> QuadTreeNode::GetChildren()
{
	return children;
}

std::vector<GameObject*> QuadTreeNode::GetGameObjects()
{
	return gameobjs;
}

//QUADTREE
QuadTreeZ::QuadTreeZ()
{
}

QuadTreeZ::~QuadTreeZ()
{
}

void QuadTreeZ::Calculate()
{
	root.Clear();
	root.Fill();
}

void QuadTreeZ::Clear()
{
}
