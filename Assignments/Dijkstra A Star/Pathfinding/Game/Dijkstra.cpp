#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

Dijkstra::Dijkstra(GridGraph* pGraph)
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

Dijkstra::~Dijkstra()
{
}

const Path& Dijkstra::findPath(Node* pFrom, Node* pTo)
{
	//Setting the performance tracker to check the performance of the algorithm
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	/*
	//Setting up list of nodes to visit
	std::list<Node*> nodesToVisit;
	nodesToVisit.push_front(pFrom);

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{

	}
	*/

	//Setting up the list of nodes
	std::queue<Node*> nodesToVisit;
	nodesToVisit.push(pFrom);

	std::vector<int> distance;
	std::vector<Node*> previous;

	//For each node in the graph
	for (int i = 0; i < mpGraph->getSize(); ++i)
	{
		distance.at(i) = INFINITY;
		previous.at(i) = mpGraph->getNode(i);

		nodesToVisit.push(mpGraph->getNode(i));
	}

	//Distance from the first node to the first node is 0
	distance.at(0) = 0;

	Node* current;

	//While the queue of nodes to visit isn't empty
	while (!nodesToVisit.empty())
	{
		current = nodesToVisit.front();
		nodesToVisit.pop();

		//For each of the current node's neightbors
		for (int i = 0; i < 4; ++i) //CHANGE THIS FROM 4 TO ACCOUNT FOR EDGE NODES
		{
			
		}
	}
	
}