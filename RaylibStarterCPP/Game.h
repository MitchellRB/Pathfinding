#pragma once

#include "raylib-cpp.hpp"

#include "Graph.h"
#include "Pathfinder.h"

namespace rl = raylib;

class Game
{
public:
	Game();
	~Game();

	void Initalise();

	void Run();

	void Update(float deltaTime);

	void Draw();

	void Close();

private:

	void RunDepth();
	void RunBreadth();
	void RunDij();
	void RunAStar();

	void GenerateGraph();

	Node* CreateNode();

	rl::Window* window;

	rl::Color bgColour = BLACK;

	unsigned int screenWidth = 1600;
	unsigned int screenHeight = 900;

	Graph graph;

	int nodesAmount = 650;
	int maxDistance = 65;
	int minDistance = 30;

	Node* first;
	Node* last;

	std::list<NodeBack> pathQueue;
	std::list<NodeBack> colouredNodes;
	int advanceTimer;

	Pathfinder* pathfinder;

	bool showLinks = true;
	bool showData = false;
};
