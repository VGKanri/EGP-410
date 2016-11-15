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
#include <xutility>

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

	//std::queue<Node*> nodesToVisit;
	std::list<Node*> nodesToVisit;
	pFrom->setPrevNodeId(pFrom->getId());
	nodesToVisit.push_back(pFrom);

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();
	mShortPath.clear();

	std::vector<int> distance;
	std::vector<Node*> previous;

	//Current node being processed
	Node* current = NULL;

	//Checking if the node that you are searching to has been added to the queue yet
	bool endNode = false;

	//While the queue of nodes to visit isn't empty
	while (nodesToVisit.size() > 0 && current != pTo)
	{
		//Process what the current node is and add it to the path.
		current = nodesToVisit.front();
		nodesToVisit.pop_front();
		mPath.addNode(current);

		//Getting the list of connections for the current node 
		std::vector<Connection*> connectionVector = mpGraph->getConnections(current->getId());

		//For each of the current node's neightbors
		for (int i = 0; i < connectionVector.size(); ++i) 
		{
			//Getting the current connection
			Connection* currentConnection = connectionVector[i];

			Node* tmpNode = connectionVector[i]->getToNode();

			if (!endNode && !mPath.containsNode(tmpNode)
				&& std::find(nodesToVisit.begin(), nodesToVisit.end(), tmpNode) == nodesToVisit.end())
			{
				//Setting the previous node ID
				tmpNode->setPrevNodeId(current->getId());

				nodesToVisit.push_back(tmpNode);
				if (tmpNode == pTo)
					endNode = true;

#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(tmpNode);
#endif
			}
		}

		//If the goal has been reached go backwards through the nodes and determine path taken
		if (endNode)
		{
			Node* tmpNode = pTo;
			bool done = false;
			mShortPath.clear();

			while (!done)
			{
				mShortPath.addNode(tmpNode);

				//If the start node is added, set up to break out of loop.
				if (tmpNode == pFrom)
					done = true;

				tmpNode = tmpNode->getPrevNode();
			}
		}
	}

	//Ending performance tracking and returning the path
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;
}