#pragma once

class Node
{
public:
	~Node();
	Node* left_child;
	Node* right_child;

	char character;
	int character_frequency;
};

inline Node::~Node()
{
	delete left_child;
	delete right_child;
}

