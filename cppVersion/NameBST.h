#pragma once
#include "NameBSTNode.h"

class NameBST : public NameBSTNode {
/*	Declare NameBST class which stores member information
	in name order and inherits NameBSTNode.		*/
private:
	NameBSTNode* root;
//Declare root of NameBST.
public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();			//Returns the root address.
	void insert(NameBSTNode* node);	//Inserts a node with the passed information into the tree.
	void print(NameBSTNode* node);	//Prints all member information stored in the tree recursively.
	void remove(NameBSTNode* node);	//Removes the node passed as an parameter.
	NameBSTNode* search(const string name);	//Finds the node named by the given name.
};