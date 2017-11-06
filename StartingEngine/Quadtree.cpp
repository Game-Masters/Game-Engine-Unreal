#include "Quadtree.h"
#define  U_NE 0
#define  U_SE 1
#define  U_SW 2
#define  U_NW 3
#define  D_NE 4
#define  D_SE 5
#define  D_SW 6
#define  D_NW 7
//QUADTREE NODE
QuadTreeNode::QuadTreeNode()
{
}
QuadTreeNode::QuadTreeNode(float3 min_point, float3 max_point, int max_objects) :max_game_objects(max_objects)
{
	bounds.maxPoint = max_point;
	bounds.minPoint + min_point;
}
QuadTreeNode::~QuadTreeNode()
{
}

void QuadTreeNode::Insert(GameObject * game_object)
{

	gameobjs.push_back(game_object);
}

void QuadTreeNode::Erase(GameObject * game_object)
{
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
	float3 center_point = { (bounds.minPoint.x + bounds.maxPoint.x) / 2,0,(bounds.minPoint.z + bounds.maxPoint.z) / 2 };
	float3 min_point1 = bounds.minPoint;
	float3 max_point1 = { center_point.x,bounds.maxPoint.y,center_point.z };
	float3 min_point2 = { center_point.x,bounds.minPoint.y,center_point.z };
	float3 max_point2 = bounds.maxPoint;
	float3 min_point3 = { center_point.x,bounds.minPoint.y,bounds.minPoint.z };
	float3 max_point3 = { bounds.maxPoint.x,bounds.maxPoint.y,center_point.z };
	float3 min_point4 = { bounds.minPoint.x,bounds.minPoint.y,center_point.z };
	float3 max_point4 = { center_point.x,bounds.maxPoint.y,bounds.maxPoint.z };
	QuadTreeNode* child1 = new QuadTreeNode(min_point1, max_point1, NODE_CAPACITY);
	QuadTreeNode* child2 = new QuadTreeNode(min_point2, max_point2, NODE_CAPACITY);
	QuadTreeNode* child3 = new QuadTreeNode(min_point3, max_point3, NODE_CAPACITY);
	QuadTreeNode* child4 = new QuadTreeNode(min_point4, max_point4, NODE_CAPACITY);

	children.push_back(child1);
	child1->Fill();
	children.push_back(child2);
	child2->Fill();
	children.push_back(child3);
	child3->Fill();
	children.push_back(child4);
	child4->Fill();
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

bool QuadTreeNode::IsLeaf() const
{
	return children[0] == nullptr;
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

void QuadTreeZ::SetBoundaries(const AABB & bounds)
{
}

void QuadTreeZ::Insert(GameObject * game_object)
{
}

void QuadTreeZ::Erase(GameObject * game_object)
{
}

void QuadTreeZ::Clear()
{
}
