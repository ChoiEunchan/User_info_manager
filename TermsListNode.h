#pragma once
#include "TermsBST.h"
#include <iostream>

using namespace std;

class TermsListNode {
//Declare TermsListNode class which is a node that constitutes TermsLIST class.
private:
/*	It has member variables containing information by subscription type
	such as the group type, number of members. And also have address of the tree
	that stores information of members of the same subscription type and address of next node in the list.	*/
	char subscription_type;
	int number_of_members;
	TermsBST* bst;
	TermsListNode* next;

public:
	TermsListNode() {
	//Initialize the member variables.
		this->subscription_type = '0';
        this->number_of_members = 0;
        bst = nullptr;
        next = nullptr;
	}
	TermsListNode(const char subscription_type) {
	//Make a node and initialize the member variables with the given subscription type.
		this->subscription_type = subscription_type;
        this->number_of_members = 1;
        bst = nullptr;
        next = nullptr;
	}
	TermsListNode(const char subscription_type, TermsBST* bst) {
	//Make a node and initialize the member variables with the given subscription type and bst pointer.
		this->subscription_type = subscription_type;
        this->number_of_members = 1;
        this->bst = bst;
        next = nullptr;
		return;
	}
	~TermsListNode() {
		bst = nullptr;
		next = nullptr;
		delete bst, next;
	}
	inline TermsListNode* getNext() { return next; }			//Returns the next node in the list.
	inline int getNumMembers()	{ return number_of_members; }	//Returns the number of members.
	inline char getSubType() { return subscription_type; }		//Returns the subscription type.
	inline TermsBST* getBST() { return bst; }					//Returns the address of BST.

	int updateNumMembers(int additional_members) {				//Update number of members with given integer.
		number_of_members += additional_members;
        return number_of_members;
	}
	void setNext(TermsListNode* node) {		//Set next node.
		next = node;
		return;
	}	
};