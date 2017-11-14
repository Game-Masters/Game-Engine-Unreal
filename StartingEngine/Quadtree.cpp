#include "Quadtree.h"

//QUADTREE NODE
QuadTreeNode::QuadTreeNode()
{
}
QuadTreeNode::QuadTreeNode(AABB * box)
{
	bounds = *box;
}
QuadTreeNode::QuadTreeNode(float3 min_point, float3 max_point, int max_objects) :max_game_objects(max_objects)
{
	bounds.maxPoint = max_point;
	bounds.minPoint = min_point;
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
	std::vector<GameObject*> root_children = App->scene_intro->root_gameobject->Childrens_GameObject_Vect;
	for (std::vector<GameObject*>::iterator it = root_children.begin(); it != root_children.end(); it++)
	{
		if (InsideTree(it, this) == false)
		{
			//CHECK IF IT IS SMALLER THAN THE SMALLEST POSSIBLE
			if (this->IsSmall() == false)
			{
				
				gameobjs.clear();
				Subdivide();
				break;
			}
			else
			{
				break;
			}


		}
	}

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
	return children.size() <= 0;
}

bool QuadTreeNode::Full()
{
	return gameobjs.size() >= NODE_CAPACITY;
}

bool QuadTreeNode::InsideTree(std::vector<GameObject*>::iterator it, QuadTreeNode* node)
{
	bool ret = true;
	if ((*it)->static_obj != true)
	{
		return ret;
	}
	else
	{
		if ((*it)->Get_GO_Mesh() != nullptr)
		{
			AABB temp_aabb = (*it)->Get_GO_Mesh()->Copy_aabb_using;
			if (node->bounds.Intersects(temp_aabb))
			{
				node->Insert((*it));
			}
		}

		if (node->Full() && (node->IsSmall() != true))
		{
			return false;
		}
		//check problem
		for (std::vector<GameObject*>::iterator it2 = (*it)->Childrens_GameObject_Vect.begin(); it2 != (*it)->Childrens_GameObject_Vect.end(); it2++)
		{
			ret = InsideTree(it2, node);
			if (ret == false || (node->IsSmall() == true))
			{

				break;
			}
		}

	}


	return ret;
}

bool QuadTreeNode::IsSmall()
{
	float3 boundsmin = bounds.minPoint;
	float3 boundsmax = bounds.maxPoint;
	float3 boundstemp = (boundsmax - boundsmin).Abs();
	float boundslength = boundstemp.Length();
	float minlength = boundstemp2.Length();
	return (boundslength <= minlength);
}

void QuadTreeNode::DebugDraw()
{
	for (uint i = 0; i < 12; i++)
	{
		
		glVertex3f(bounds.Edge(i).a.x, bounds.Edge(i).a.y, bounds.Edge(i).a.z);
		glVertex3f(bounds.Edge(i).b.x, bounds.Edge(i).b.y, bounds.Edge(i).b.z);
	}

	if (children.size()>0)
	{
		for (uint i = 0; i < children.size(); i++)
		{
			children[i]->DebugDraw();
		}

	}

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
	root->Clear();
	root->Fill();

}

void QuadTreeZ::SetBoundaries(const AABB * bounds)
{
	root = new QuadTreeNode((AABB*)bounds);
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

void QuadTreeZ::DebugDraw()
{
	glBegin(GL_LINES);
	glLineWidth(3.0f);
	glColor4f(1.00f, 0.761f, 0.00f, 1.0f);

	if (root != nullptr)
	{
		root->DebugDraw();
	}

	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}