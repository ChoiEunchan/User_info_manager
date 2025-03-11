#pragma once
#include "TermsBST.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

TermsBST::TermsBST() { root = nullptr; }
TermsBST::~TermsBST() {
	while (root != nullptr)
		remove(root);
}

TermsBSTNode* TermsBST::getRoot() { return root; }		//Get the address of root.

void TermsBST::insert(TermsBSTNode* node) {
/*//////////////////////////////////////////////////////////////////////////
                function name : insert
        Input : TermsBSTNode* - the node wants to insert into the tree.
        Output : None.
        Purpose : Insert a node into the tree.
//////////////////////////////////////////////////////////////////////////*/
	if (root == nullptr)
		root = new TermsBSTNode(node->getName(), node->getAge(), node->getSubDate(), node->getSubEndDate());
	//If there's no node in the tree, make a new node and set it as a root.
	else {
	//If not, executes following codes.
		TermsBSTNode* prev;
		TermsBSTNode* it = root;
		int result = 0;
		while (it!= nullptr) {
			if ((result = it->getSubEndDate().compare(node->getSubEndDate())) == 0) {
			/*	If the name of the visited node and the name of the node passed
				as an argument are the same, execute the code below		*/
				if((node->getName().compare(it->getName())) == 0) {
					if (it->getAge() == node->getAge())
						return;
			//If all information on the visited node and the received node are the same, the function ends.
				}
			}
			else if (result > 0) {
				prev = it;
				it = it->getLeft();
			/*	If the name of the visited node is faster in lexicographic order,
				it moves to the left child of that node.
				And save the address of the parent node of the node you want to move.		*/
			}
			else {
				prev = it;
				it = it->getRight();
			/*	If the delivered one is slower, moves to the right child and save the parent node's address.		*/
			}
		}
		it = new TermsBSTNode(node->getName(), node->getAge(), node->getSubDate(), node->getSubEndDate());
		/*	Creates a node based on the input information.	*/
		it->setParent(prev);
		/*	Set the parent of new node.	*/
		if (result > 0)
			prev->setLeft(it);
		/*	If the name of the parent node is faster in lexicographic order,
			set the new node as a parent's left child.*/
		else
			prev->setRight(it);
		//If not, set it as a right child.
	}
	return;
}

void TermsBST::print(TermsBSTNode* node) {
/*//////////////////////////////////////////////////////////////////////////
                function name : print
        Input : TermsBSTNode* - the node wants to print.
        Output : None.
        Purpose : Prints all nodes in the tree recursively.
//////////////////////////////////////////////////////////////////////////*/
	if (node != nullptr) {
	//Executes following code if the delivered node is not a nullptr value.
		print(node->getLeft());
		//Call the other function for its left child.
		ofstream flog;
		flog.open("log.txt", ios::app);
		flog << node->getName() << "/" << node->getAge() << "/" << node->getSubDate() << "/" << node->getSubEndDate() << endl;
		flog.close();
		//If the node's left subtree's information is printed, print myself. 
		print(node->getRight());
		//Call the other function for its right child.
	}
	//Finally, all nodes in the tree are output in inorder.
	return;
}
void TermsBST::remove(TermsBSTNode* node) {
/*//////////////////////////////////////////////////////////////////////////
                function name : remove
        Input : TermsBSTNode* - the node wants to remove.
        Output : None.
        Purpose : Delete the node and restruct the tree.
//////////////////////////////////////////////////////////////////////////*/
	if (node == nullptr)
		return;	//If delivered nullptrptr, terminate the function.
	TermsBSTNode* it = nullptr;
	if (node->getLeft() != nullptr) {
		if (node->getRight() != nullptr) {
			it = node->getRight();
			while (it->getLeft() != nullptr)
				it = it->getLeft();
		}
		/*	If degree of node that want to delete is 2,
		Searches for the leftmost node in the right subtree of the node.	*/
		else
			it = node->getLeft();
		//If the node only has left chid, set the replacement node as the left child.
	}
	else {
		if (node->getRight() != nullptr)
			it = node->getRight();
		//If only has right, set it as the right child.
	}

	if (it == nullptr) {
		if (node != root) {
		//If the tree has more than two nodes, executes the following codes.
			if (node->getParent()->getLeft() == node)
				node->getParent()->setLeft(nullptr);
			else
				node->getParent()->setRight(nullptr);
		//	Determine which node the node is a child of.
			delete node;
		}
		else {
			delete node;
			root = nullptr;
		/*	If the tree has only one node, set root as nullptr value
		and terminate the function after delete the node.	*/
		}
		return;
		//	Terminate the function after delete the node.
	}
	else {
	//Check degree of node to delete and if the degree is over 0, executes following codes.
		if (it->getParent()->getLeft() == it)
			it->getParent()->setLeft(nullptr);
		else if (it->getParent()->getRight() == it)
			it->getParent()->setRight(nullptr);
		/*	Determine which child of the parent node the replacement node is,
			and change the corresponding node to a nullptr value.	*/
		if (node != root) {
			if (node->getParent()->getLeft() == node)
				node->getParent()->setLeft(it);
			else if (node->getParent()->getRight() == node)
				node->getParent()->setRight(it);
			it->setParent(node->getParent());
		/*	If the node wants to delete is not a root, determine which child of the parent node it is
			and replace that node with a replacement node "it".
			And set the "it"'s parent to the parent of the node wants to delete.	*/
		}
		else {
			if (it->getParent() == node->getLeft()) {
				if (node->getLeft()->getLeft() == it)
					node->getLeft()->setLeft(nullptr);
				else if (node->getLeft()->getRight() == it)
					node->getLeft()->setRight(nullptr);
			}
			/* If not, and if "it"'s parent and node's left child are same, determine the direction
				of "it", and change the node in the corresponding position to a nullptr value.*/
			else if (it->getParent() == node->getRight()) {
				if (node->getRight()->getLeft() == it)
					node->getRight()->setLeft(nullptr);
				else if (node->getRight()->getRight() == it)
					node->getRight()->setRight(nullptr);
			}
			/*	if "it"'s parent is a node's right child,
				determine and change the corresponding position in same way.	*/
			it->setParent(nullptr);
			root = it;
			//Set the "it" as a root.
		}
	}
	if (node->getLeft() != nullptr && node->getLeft() != it) {
		it->setLeft(node->getLeft());
		node->getLeft()->setParent(it);
	//	Change the left child of the node want to delete to the left child of "it".
	}
	if (node->getRight() != nullptr && node->getRight() != it) {
		it->setRight(node->getRight());
		node->getRight()->setParent(it);
	//	Change the "it"'s right child in the same way.
	}
	delete node;
	node = nullptr;
	return;
	//	Delete the node and exit the function.
}
TermsBSTNode* TermsBST::search(string name, string sub_end_date) {
/*//////////////////////////////////////////////////////////////////////////
                function name : search
        Input : const string	- Name wants to find.
        Output : TermsBSTNode* - address : Node corresponding to the entered name.
				 			  - nullptr 	: No node corresponding in the tree.
        Purpose : Find the node named with "name" in the tree.
//////////////////////////////////////////////////////////////////////////*/
	TermsBSTNode* it = root;
	//	Set the compare position of the tree as a root.
	int result = 0;
	while (it != nullptr) {
		result = sub_end_date.compare(it->getSubEndDate());
		//Compare the two names that are one for entered, and one for already existed in the tree.
		if (result == 0) {
			if ((result = name.compare(it->getName())) == 0)
				break;
			//  If two subscription end dates are same and two names are same, break out of the loop.
			else
				it = it->getRight();
			// If two names are different, move "it" to the right child.
		}
		else {
			if (result < 0)
				it = it->getLeft();
			/*  If the expiration date of the entered member is earlier,
				than move "it" to the left child.     */
			else
				it = it->getRight();
			//  If not, move "it" to the right child.
		}
	}
	return it;
	//Return the current address of it.
}