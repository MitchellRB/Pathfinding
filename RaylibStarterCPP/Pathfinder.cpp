#include "Pathfinder.h"
Pathfinder::Pathfinder()
{

}

Pathfinder::~Pathfinder()
{

}

bool Pathfinder::IsInList(Node* node, const std::list<NodeBack>& list)
{
	if (list.size() == 0)
		return false;

	for (auto& n : list)
	{
		if (*n.node == *node)
			return true;
	}

	return false;
}

bool Pathfinder::IsInList(Node* node, const std::list<PathingNode>& list)
{
	if (list.size() == 0)
		return false;

	for (auto& n : list)
	{
		if (*n.node == *node)
			return true;
	}

	return false;
}

PathingNode* Pathfinder::FindInList(Node* node, std::list<PathingNode>& list)
{
	if (list.size() == 0)
		return nullptr;

	for (auto& n : list)
	{
		if (*n.node == *node)
			return &n;
	}

	return nullptr;
}


std::list<NodeBack> Pathfinder::DepthFirstFill(Node* start)
{
	std::list<NodeBack> traversed;
	std::list<NodeBack> stack;

	stack.push_back({ start,nullptr });

	while (!stack.empty())
	{
		NodeBack current = stack.back();
		traversed.push_back(current);
		stack.pop_back();
		for (auto& e : current.node->connections)
		{
			if (!IsInList(e.to, traversed) && !IsInList(e.to, stack))
			{
				stack.push_back({ e.to, current.node });
			}
		}
	}

	return traversed;
}

std::list<NodeBack> Pathfinder::BreadthFirstFill(Node* start)
{
	std::list<NodeBack> traversed;
	std::list<NodeBack> queue;

	queue.push_back({ start, nullptr });

	while (!queue.empty())
	{
		NodeBack current = queue.front();
		traversed.push_back(current);
		queue.remove(queue.front());
		for (auto& e : current.node->connections)
		{
			if (!IsInList(e.to, traversed) && !IsInList(e.to, queue))
			{
				queue.push_back({ e.to, current.node });
			}
		}
	}

	return traversed;
}

std::list<NodeBack> Pathfinder::DijkstasFind(Node* start, Node* goal)
{
	if (start == nullptr || goal == nullptr)
	{
		return std::list<NodeBack>();
	}

	if (start == goal)
	{
		std::list<NodeBack> path;
		path.push_back({ start, nullptr });
		return path;
	}

	std::list<PathingNode> openList;
	std::list<PathingNode> closedList;

	openList.push_back({ start, nullptr, 0 });

	while (!openList.empty() && !IsInList(goal, closedList))
	{
		PathingNode* current = new PathingNode(openList.front());
		closedList.push_back(*current);
		openList.remove(openList.front());
		for (auto& e : current->node->connections)
		{
			PathingNode* n = FindInList(e.to, openList);
			if (n != nullptr && n->gScore > (int)e.weight + current->gScore)
			{
				n->gScore = (int)e.weight + current->gScore;
				n->parent = current;
			}
			else if (!IsInList(e.to, openList) && !IsInList(e.to, closedList))
			{
				openList.push_back(PathingNode{ e.to, current, (int)e.weight + current->gScore });
			}
		}
		//Sort openlist
		std::stable_sort(openList.begin(), openList.end());
	}


	//Generate path
	std::list<NodeBack> output;
	PathingNode* current = &closedList.back();

	output.push_front({ current->node, current->parent->node });
	current = current->parent;

	while (true)
	{
		if (current->parent == nullptr)
		{
			break;
		}
		output.push_front({ current->node, current->parent->node });
		current = current->parent;
	}


	return output;
}

std::list<NodeBack> Pathfinder::AStar(Node* start, Node* goal)
{
	if (start == nullptr || goal == nullptr)
	{
		return std::list<NodeBack>();
	}

	if (start == goal)
	{
		std::list<NodeBack> path;
		path.push_back({ start, nullptr });
		return path;
	}

	std::list<PathingNode> openList;
	std::list<PathingNode> closedList;

	openList.push_back({ start, nullptr, 0 });

	while (!openList.empty() && !IsInList(goal, closedList))
	{
		PathingNode* current = new PathingNode(openList.front());
		closedList.push_back(*current);
		openList.remove(openList.front());
		for (auto& e : current->node->connections)
		{
			PathingNode* n = FindInList(e.to, openList);
			if (n != nullptr && n->gScore > (int)e.weight + current->gScore)
			{
				n->gScore = (int)e.weight + current->gScore + AStarHeuristic(n, goal);
				n->parent = current;
			}
			else if (!IsInList(e.to, openList) && !IsInList(e.to, closedList))
			{
				int newFScore = (int)e.weight + current->gScore;
				newFScore += AStarHeuristic(current, goal);
				openList.push_back(PathingNode{ e.to, current, newFScore });
			}
		}
		//Sort openlist
		std::stable_sort(openList.begin(), openList.end());
	}


	//Generate path
	std::list<NodeBack> output;
	PathingNode* current = &closedList.back();

	output.push_front({ current->node, current->parent->node });
	current = current->parent;

	while (true)
	{
		if (current->parent == nullptr)
		{
			break;
		}
		output.push_front({ current->node, current->parent->node });
		current = current->parent;
	}


	return output;
}

int Pathfinder::AStarHeuristic(PathingNode* node, Node* goal)
{
	//if (node == nullptr) return 0;
	float distance = node->node->position.Distance(goal->position);
	return distance;
}
