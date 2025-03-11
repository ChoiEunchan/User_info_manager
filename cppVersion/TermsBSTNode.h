#pragma once
#include <iostream>
#include <string>

using namespace std;

class TermsBSTNode {
//Declare TermsBSTNode class which is a node that constitutes TermsBST class.
private:
/*	It has member variables containing member information such as the member's name, age,
	subscription date, and subscription end date,
	as well as the addresses of the left and right child and parent nodes of the tree.	*/
	string name;
	int age;
	string sub_date;
	string sub_end_date;
	TermsBSTNode* left;
	TermsBSTNode* right;
	TermsBSTNode* parent;

public:
	TermsBSTNode() {
	//Initialize the member variables.
		name = ".";
		age = 0;
		sub_date = ".";
		sub_end_date = ".";
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	TermsBSTNode(string name, int age, string sub_date, char subtype) {
	//Initialize the member variables with the given datas.
		this->name = name;
        this->age = age;
        this->sub_date = sub_date;
		this->sub_end_date = sub_date;
        this->left = nullptr;
        this->right = nullptr;
		this->parent = nullptr;
		
		int months = 0;
		months = stoi(sub_date.substr(5, 2));
		months += stoi(sub_date.substr(0, 4)) * 12;
		switch(subtype) {
			case 'A':
				months += 6;
                break;
			case 'B':
				months+=12;
                break;
			case 'C':
				months+=24;
                break;
			case 'D':
				months+=36;
                break;
		}
		sub_end_date.replace(0, 4, to_string(months/12));
		if (months%12 < 10)
			sub_end_date.replace(5, 2, "0" + to_string(months%12));
		else
        	sub_end_date.replace(5, 2, to_string(months%12));
		/*	Calculates the subscription period from the subscription type and start date
			and initializes the subscription end date. If the number of months
			in the subscription end date is a single digit, initialize it by adding 0. */
	}
	TermsBSTNode(string name, int age, string sub_date, string sub_end_date) {
	//Initialize the member variables with the given datas.
		this->name = name;
        this->age = age;
        this->sub_date = sub_date;
		this->sub_end_date = sub_end_date;
        this->left = nullptr;
        this->right = nullptr;
		this->parent = nullptr;
	}
	~TermsBSTNode() {
	//Changes the addresses of neighboring nodes of the current node to null value and free them.
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		delete left, right, parent;
	}

	TermsBSTNode* getLeft() { return left; }	//Returns the address of left child of this node.
	TermsBSTNode* getRight() { return right; }	//Returns the address of right child.
	string getName() { return name; }			//Returns the name.
	int getAge() { return age; }				//Returns the age.
	string getSubDate() { return sub_date; }	//Returns the subscription start date.
	string getSubEndDate() { return sub_end_date; }		//Returns the subscription end date.
	TermsBSTNode* getParent() { return parent; }		//Returns the address of parent node.
	char getSubType() {
		int subtype = stoi(sub_end_date.substr(0, 4))*12;
        subtype += stoi(sub_end_date.substr(5, 2));
        subtype -= stoi(sub_date.substr(0, 4))*12;
        subtype -= stoi(sub_date.substr(5, 2));
		if (subtype == 6)
			return 'A';
		else if (subtype == 12)
			return 'B';
		else if (subtype == 24)
			return 'C';
		else
			return 'D';
		//Calculate the subscription period and returns the type.
	}
	void setLeft (TermsBSTNode* left) { this->left = left; }	//Sets the left child.
	void setRight (TermsBSTNode* right)	{ this->right = right; }	//Sets the right child.
	void setParent (TermsBSTNode* parent) { this->parent = parent; }	//Sets the parent node.
};