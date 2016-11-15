#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "GameApp.h"
#include "Vector2D.h"
#include "Grid.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>
#include <xutility>

AStar::AStar(GridGraph* pGraph)
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

AStar::~AStar()
{

}

const Path& AStar::findPath(Node* pFrom, Node* pTo)
{
	//Setting the performance tracker to check the performance of the algorithm
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	//std::queue<Node*> nodesToVisit;
	std::list<Node*> nodesToVisit;
	pFrom->setPrevNodeId(pFrom->getId());
	nodesToVisit.push_front(pFrom);

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

				if (nodesToVisit.size() > 0 && confirmHeuristic(pTo, nodesToVisit.front(), tmpNode) == true)
				{
					nodesToVisit.push_front(tmpNode);
				}
				else
				{
					nodesToVisit.push_back(tmpNode);
				}

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

bool AStar::confirmHeuristic(Node* pTo, Node* pNext, Node* pCurrent) const
{
	//Setting up the vectors of node positions
	Vector2D toPos = gpGameApp->getGrid()->getULCornerOfSquare(pTo->getId());
	Vector2D nextPos = gpGameApp->getGrid()->getULCornerOfSquare(pNext->getId());
	Vector2D currentPos = gpGameApp->getGrid()->getULCornerOfSquare(pCurrent->getId());

	//Calculating euclidian distance between node and goal
	float currDistance = abs(sqrt(pow((toPos.getX() - currentPos.getX())
		,2) + pow((toPos.getY() - currentPos.getY()), 2)));

	float nextDistance = abs(sqrt(pow((toPos.getX() - nextPos.getX())
		, 2) + pow((toPos.getY() - currentPos.getY()), 2)));

	//Compare distance and return as needed
	if (currDistance <= nextDistance)
		return true;

	else
		return false;
}