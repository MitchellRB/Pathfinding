#include "Graph.h"

Node* Graph::AddNode(raylib::Vector2 pos, int data)
{
	Node* n = new Node();
	n->position = pos;
	n->value = data;
	m_nodes.push_back(n);
	return n;
}

void Graph::AddEdge(Node* nodeA, Node* nodeB, float data)
{
	//Stop edges with self
	if (nodeA != nodeB)
	{
		//Stop duplicate edges
		for (auto& e : nodeA->connections)
		{
			if (nodeB == e.to) return;
		}
		nodeA->connections.push_back(Edge{ nodeB, data });
	}
}

void Graph::DeleteNode(Node* node)
{
	for (auto& n : m_nodes)
	{
		n->connections.remove(Edge{ node } );
	}
	m_nodes.remove(node);
	delete node;
}

void Graph::DrawNodes(std::list<Node*> selected, bool showData, bool showLinks)
{
	for (auto& n : m_nodes)
	{
		if (showLinks)
		{
			for (auto& e : n->connections)
			{
				raylib::Vector2 start = n->position;
				raylib::Vector2 end = e.to->position;

				raylib::Vector2 dir = end - start;
				dir = dir.Normalize();


				start = start + dir.Scale(nodeRadius);
				end = end - dir.Scale(nodeRadius);

				DrawLineV(start, end, BLUE);
			}
		}

		//Check if node in the selected list
		if (std::find(selected.begin(), selected.end(), n) != selected.end())
		{
			n->position.DrawCircle(nodeRadius, MAROON);
		}
		else
		{
			n->position.DrawCircle(nodeRadius, DARKGRAY);
		}

		if (showData)
		{
			std::stringstream ss;
			ss << n->value;
			DrawText(ss.str().c_str(), n->position.x - 4, n->position.y - 4, 10, WHITE);
		}
	}
}

void Graph::DrawNode(Node* node, bool showData, raylib::Color c)
{
	node->position.DrawCircle(nodeRadius, c);

	if (showData)
	{
		std::stringstream ss;
		ss << node->value;
		DrawText(ss.str().c_str(), node->position.x - 4, node->position.y - 4, 10, WHITE);
	}
}

void Graph::DrawPath(std::list<NodeBack> nodes)
{
	for (auto& n : nodes)
	{
		if (n.back != nullptr)
			DrawLineEx(n.node->position, n.back->position, 3, WHITE);
	}
}

bool Graph::IsTouchingNode(raylib::Vector2 point, Node* node)
{
	return point.Distance(node->position) < nodeRadius;
}