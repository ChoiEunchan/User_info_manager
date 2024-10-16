#pragma once
#include "TermsListNode.h"
#include <iostream>
using namespace std;

class TermsLIST : public TermsListNode {
/*	Declare a TermsLIST class that stores the number of members by subscription terms
	and conditions type and inherits TermsLISTNode.		*/
private:
	TermsListNode* head;
//Declare root of TermsList.
public:
	TermsLIST(); 
	TermsLIST(TermsListNode* node);
	//Create a list with the received node as the head.
	~TermsLIST();

	TermsListNode* getHead();					//Return the head.
	void insert(char subtype, TermsBST* bst);	//Insert new node that into the list
	TermsListNode* search(char subtype);
	/*	Insert a list node containing the receivedsubscription terms and conditions
		and the corresponding bst.		*/
	void remove(char subtype);
	//Remove nodes that match the received subscription terms and conditions from the list.
};
