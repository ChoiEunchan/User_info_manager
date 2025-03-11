#pragma once
#include "TermsList.h"
#include <iostream>

using namespace std;

TermsLIST::TermsLIST() { head = nullptr; }
//Initialize the head address to a nullptr value when creating TermsList.
TermsLIST::~TermsLIST() {
//Delete nodes in the list when the list is destroyed.
	char sub;
	while (head != nullptr) {
		sub = head->getSubType();
		remove(sub);
	}
}

TermsListNode* TermsLIST::getHead() { return head; }	//Return the address of the head which is start address of list.

void TermsLIST::insert(char subtype, TermsBST* bst) {
/*//////////////////////////////////////////////////////////////////////////
                function name : insert
        Input : char 		- subscription type of new node
				TermsBST*	- TermsBST address of new node that belonging to.
        Output : None
        Purpose : Insert a new node into the list.
				  If the node is already exist, update the number of members.
//////////////////////////////////////////////////////////////////////////*/
    if (head == nullptr) {
        head = new TermsListNode(subtype, bst);
        return;
	//If the list is empty, insert a new node as a head of the list and terminate the function.
    }
    TermsListNode* it = head;
	TermsListNode* temp;
	/*	Make TermsLIstNode pointer value to search the node that matches with entered subtype
		and to save the previous node address. */
	
    while (it != nullptr) {
	/*	Executes following codes until reach at the end of list.	*/
		if(it->getSubType() == subtype) {
		/*	If current node is matched with given subscription type then
			update the number of members and terminate the function.	*/
			it->updateNumMembers(1);
			return;
		}
		temp = it;
        it = it->getNext();
		//If not, move to next node and save the current node address.	*/
    }
	if ((int)subtype >= 65 && (int)subtype <= 68) {
    	it = new TermsListNode(subtype, bst);
		temp->setNext(it);
	}
    return;
	/*	If you exit the loop, it means there is no matching node, so add a new node if the subtype is A, B, C, or D.
		If not, terminate the function without making new node.	*/
}

TermsListNode* TermsLIST::search(char subtype) {
/*//////////////////////////////////////////////////////////////////////////
                function name : search
        Input : char	- subscription type of node
        Output : TermsListNode*		- address of the matching node
        Purpose : Finds a node that matches the input subtype
				  and returns the node's address.
//////////////////////////////////////////////////////////////////////////*/
	TermsListNode* current = head;
	//Get the address of the head.
	while (current!= nullptr) {
	/*	Executes following codes until reach at the end of list.	*/
		if (current->getSubType() == subtype) {
			return current;
        }
        current = current->getNext();
		/*	If current node is matched with given subscription type then
			return the address of current node. If not, move to next.	*/
    }
	return current;
	//If can't find the node, return nullptr.
}
void TermsLIST::remove(char subtype) {
/*//////////////////////////////////////////////////////////////////////////
                function name : remove
        Input : char	- subscription type of node
        Output : None
        Purpose : Delete the node matching with given subtype.
//////////////////////////////////////////////////////////////////////////*/
	TermsListNode* current = head;
	TermsListNode* prev = nullptr;
	//Declare the two node pointer that save the address of current and previous node.
	while (current!= nullptr) {
	//Executes follow codes if the current is not a nullptr value.
		if (current->getSubType() == subtype) {
			if (current == head)
				head = current->getNext();
			else if (current->getNext() != nullptr)
				prev->setNext(current->getNext());
			else
				prev->setNext(nullptr);
			delete current;
			current = nullptr;
			return;
			//If the current node's subtype and given one are same and current node's number of member is 0, delete the node.
			//Before the removing node, link the previous node and next node if the current node is not a head or end of list.
        }
        prev = current;
        current = current->getNext();
		//Two subtypes are different, move to next node.
    }
	return;
}