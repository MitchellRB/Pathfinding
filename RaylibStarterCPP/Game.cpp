#include "Game.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

namespace rl = raylib;

Game::Game()
{

}

Game::~Game()
{

}

void Game::Initalise()
{
	window = new rl::Window(screenWidth, screenHeight, "Graph");

	window->SetTargetFPS(60);
}

void Game::Run()
{
	//Create grid

	GenerateGraph();

	//Main loop
	while (!window->ShouldClose())
	{
		Update(GetFrameTime());

		Draw();
	}
}

void Game::Update(float deltaTime)
{
	if (!pathQueue.empty() && advanceTimer == 0)
	{
		colouredNodes.push_back(pathQueue.front());
		pathQueue.pop_front();
		advanceTimer = 2;
	}
	else if (!pathQueue.empty())
	{
		advanceTimer--;
	}

	if (IsKeyPressed(KEY_Q))
	{
		pathQueue.clear();
		colouredNodes.clear();
	}

	if (pathQueue.empty())
	{
		if (IsKeyPressed(KEY_ONE))
		{
			RunDepth();
		}
		else if (IsKeyPressed(KEY_TWO))
		{
			RunBreadth();
		}
		else if (IsKeyPressed(KEY_THREE))
		{
			RunDij();
		}
		else if (IsKeyPressed(KEY_FOUR))
		{
			RunAStar();
		}
		else if (IsKeyPressed(KEY_R))
		{
			graph.ClearGraph();
			GenerateGraph();
			colouredNodes.clear();
		}


		/*colouredNodes.clear();
		GenerateGraph();
		RunDepth();*/
	}

	//Function keys
	if (IsKeyPressed(KEY_F1))
	{
		showLinks = !showLinks;
	}
	if (IsKeyPressed(KEY_F2))
	{
		showData = !showData;
	}

	//Select node with mouse
	if (pathQueue.empty())
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			for (auto& n : *graph.GetNodeList())
			{
				if (graph.IsTouchingNode(GetMousePosition(), n) && first != n && last != n)
				{
					first = n;
					break;
				}
			}
		}
		else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			for (auto& n : *graph.GetNodeList())
			{
				if (graph.IsTouchingNode(GetMousePosition(), n) && first != n && last != n)
				{
					last = n;
					break;
				}
			}
		}
	}
}

void Game::RunDepth()
{
	colouredNodes = std::list<NodeBack>();
	pathQueue = pathfinder->DepthFirstFill(first);
}

void Game::RunBreadth()
{
	colouredNodes = std::list<NodeBack>();
	pathQueue = pathfinder->BreadthFirstFill(first);
}

void Game::RunDij()
{
	colouredNodes = std::list<NodeBack>();
	pathQueue = pathfinder->DijkstasFind(first, last);
}

void Game::RunAStar()
{
	colouredNodes = std::list<NodeBack>();
	pathQueue = pathfinder->AStar(first, last);
}

void Game::GenerateGraph()
{
	first = nullptr;
	last = nullptr;

	graph.ClearGraph();

	first = CreateNode();

	for (int i = 0; i < nodesAmount - 2; i++)
	{
		Node* newNode = CreateNode();
		if (newNode == nullptr)
		{
			i--;
		}
	}

	do
	{
		last = CreateNode();
	} while (last == nullptr);
}

Node* Game::CreateNode()
{
	Node* newNode = graph.AddNode({ (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0,screenHeight) }, GetRandomValue(1, 1));
	for (auto& n : *graph.GetNodeList())
	{
		float distance = newNode->position.Distance(n->position);
		if (distance < minDistance && newNode != n)
		{
			graph.DeleteNode(newNode);
			return nullptr;
		}
		else if (distance < maxDistance)
		{
			graph.AddEdge(newNode, n, distance);
			graph.AddEdge(n, newNode, distance);
		}
	}
	return newNode;
}

void Game::Draw()
{
	window->BeginDrawing();

	bgColour.ClearBackground();


	std::list<Node*> coloured;
	for (auto& n : colouredNodes)
	{
		coloured.push_back(n.node);
	}
	graph.DrawNodes(coloured, showData, showLinks);

	graph.DrawNode(first, false, YELLOW);
	graph.DrawNode(last, showData, GREEN);

	if (!colouredNodes.empty())
		graph.DrawPath(colouredNodes);


	window->EndDrawing();
}

void Game::Close()
{
	delete window;
	delete pathfinder;
}
