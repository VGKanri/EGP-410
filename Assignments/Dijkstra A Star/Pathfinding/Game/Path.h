#pragma once

#include <vector>
#include <Trackable.h>

class Node;

class Path:public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode( int index ) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode( Node* pNode ) const;
	int getNumNodes() const { return mNodes.size(); };

	void addNode( Node* pNode );
	void clear();//remove all nodes

	inline Node* getFirst() { return mNodes.at(0); };
	inline Node* getLast() { return mNodes.at(mNodes.size()); };

private:
	std::vector<Node*> mNodes;

};