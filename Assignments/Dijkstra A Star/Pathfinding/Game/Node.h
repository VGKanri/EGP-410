#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node :public Trackable
{
public:
	Node(const NODE_ID& id);
	Node();
	~Node();

	const NODE_ID& getId() const { return mId; };

	//Adding previous node ID getters and setters
	inline NODE_ID getPrevNodeId() const { return mPrevNodeId; };
	inline void setPrevNodeId(NODE_ID prevId) { mPrevNodeId = prevId; };

	Node* getPrevNode();

private:
	const NODE_ID mId;
	//Previous node storage
	NODE_ID mPrevNodeId;
};