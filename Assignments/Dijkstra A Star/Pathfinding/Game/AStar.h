#pragma once

#include "GridPathfinder.h"
#include <vector>

//Required Class declarations for a pathfinder
class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class AStar :public GridPathfinder
{
public:

	AStar(GridGraph* pGraph);
	~AStar();

	const Path& findPath(Node* pFrom, Node* pTo);
private:
	bool confirmHeuristic(Node* pTo, Node* pNext, Node* pCurrent) const;
};