#pragma once
#include "TermsBSTNode.h"

class TermsBST : public TermsBSTNode {
/*	Declare a TermsBST class that stores information on members
	with the same subscription terms and conditions type and inherits TermsBSTNode.		*/
private:
	TermsBSTNode* root;
//Declare root of TermsBST.
public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();			//Returns the root address.
	void setRoot(TermsBSTNode* node);	//Sets the root address.
	void insert(TermsBSTNode* node);	//Inserts a node with the passed information into the tree.
	void print(TermsBSTNode* node);		//Prints all member information stored in the tree recursively.
	void remove(TermsBSTNode* node);	//Removes the node passed as an parameter.
	TermsBSTNode* search(string name, const string sub_end_date);
	//Find node that matches exactly with given name and subscription end date.
};