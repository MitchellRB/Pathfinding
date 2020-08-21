#pragma once

#include "raylib-cpp.hpp"

#include <list>
#include <sstream>
#include <vector>
#include <algorithm>

struct Node;

struct Edge
{
	Node* to;
	float weight;
	bool operator== (const Edge& e) const { return to == e.to; }
	bool operator!= (const Edge& e) const { return !operator==(e); }
	bool operator< (const Edge& e) const { return weight < e.weight; }
	bool operator> (const Edge& e) const { return weight > e.weight; }
};

struct Node
{
	raylib::Vector2 position;
	int value;
	std::list<Edge> connections;
	bool operator== (const Node& n) const { return position.x == n.position.x && position.y == n.position.y && value == n.value; }
	bool operator!= (const Node& n) const { return !operator==(n); }
	bool operator< (const Node& n) const { return value < n.value; }
	bool operator> (const Node& n) const { return value > n.value; }
};

struct NodeBack
{
	Node* node = nullptr;
	Node* back = nullptr;
	bool operator== (const NodeBack& n) const { return *node == *n.node; }
	bool operator== (const Node& n) const { return *node == n; }
	bool operator!= (const NodeBack& n) const { return !operator==(n); }
	bool operator< (const NodeBack& n) const { return *node < *n.node; }
	bool operator> (const NodeBack& n) const { return *node > * n.node; }
};

class Graph
{
public:


public:

	Graph()
	{

	}

	~Graph()
	{
		m_nodes.clear();
	}

	std::list<Node*>* GetNodeList()
	{
		return &m_nodes;
	}

	Node* AddNode(raylib::Vector2 pos, int data);

	void AddEdge(Node* nodeA, Node* nodeB, float data);

	void RemoveEdge(Node* nodeA, Node* nodeB)
	{
		nodeA->connections.remove(Edge{ nodeB });
	}

	void MoveNode(Node* node, raylib::Vector2 newPos)
	{
		node->position = newPos;
	}

	void DeleteNode(Node* node);

	void ClearGraph()
	{
		m_nodes.clear();
	}

	void DrawNodes(std::list<Node*> selected = {}, bool showData = true, bool showLinks = true);

	void DrawNode(Node* node, bool showData, raylib::Color c);

	void DrawPath(std::list<NodeBack> nodes);

	bool IsTouchingNode(raylib::Vector2 point, Node* node);

protected:

	std::list<Node*> m_nodes;

private:

	int nodeRadius = 6;
};

