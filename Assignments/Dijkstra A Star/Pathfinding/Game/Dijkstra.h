#pragma once

#include "GridPathfinder.h"
#include <vector>

//Required Class declarations for a pathfinder
class Path;
class Graph;
class GraphicsBuffer;
class Grid;

//Class declaration for the Dijkstra pathfinding algorithm
class Dijkstra :public GridPathfinder
{
public:

	Dijkstra(GridGraph* pGraph);
	~Dijkstra();

	const Path& findPath(Node* pFrom, Node* pTo);
private:
};