#pragma once

#include "Graph.h"
#include <list>

struct PathingNode
{
	Node* node = nullptr;
	PathingNode* parent = nullptr;
	int gScore = 0;
	bool operator== (const PathingNode& n) const { return *node == *n.node; }
	bool operator!= (const PathingNode& n) const { return !operator==(n); }
	bool operator< (const PathingNode& n) const { return gScore < n.gScore; }
	bool operator> (const PathingNode& n) const { return gScore > n.gScore; }
};

class Pathfinder
{
public:

	Pathfinder();
	~Pathfinder();

	bool IsInList(Node* node, const std::list<NodeBack>& list);
	bool IsInList(Node* node, const std::list<PathingNode>& list);

	PathingNode* FindInList(Node* node, std::list<PathingNode>& list);

	std::list<NodeBack> DepthFirstFill(Node* start);
	std::list<NodeBack> BreadthFirstFill(Node* start);

	std::list<NodeBack> DijkstasFind(Node* start, Node* goal);

	std::list<NodeBack> AStar(Node* start, Node* goal);
	int AStarHeuristic(PathingNode* node, Node* goal);

protected:

private:
};

