#include "Node.h"
#include "GameApp.h"
#include "GridGraph.h"

Node::Node()
:mId(BAD_NODE_ID)
{
}

Node::Node( const NODE_ID& id )
:mId(id)
{
}

Node::~Node()
{
}

Node* Node::getPrevNode()
{
	return gpGameApp->getGridGraph()->getNode(mPrevNodeId);
}