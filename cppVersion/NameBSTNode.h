#pragma once
#include <iostream>
#include <string>

using namespace std;

class NameBSTNode {
//Declare TermsBSTNode class which is a node that constitutes NameBST class.
private:
/*	It has member variables containing member information such as the member's name, age,
	subscription date, and subscription end date,
	as well as the addresses of the left and right child and parent nodes of the tree.	*/
    string name;
	int age;
	string sub_date;
	string sub_end_date;
	NameBSTNode* left;
	NameBSTNode* right;
	NameBSTNode* parent;

public:
	NameBSTNode() {
	//Initialize the member variables.
		name = ".";
		age = 0;
		sub_date = ".";
		sub_end_date = ".";
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	NameBSTNode(string name, int age, string sub_date, char subtype) {
		//Initialize the member variables with the given datas.
		this->name = name;
        this->age = age;
        this->sub_date = sub_date;
		this->sub_end_date = sub_date;
        left = nullptr;
        right = nullptr;
		parent = nullptr;

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
	NameBSTNode(string name, int age, string sub_date, string sub_end_date) {
	//Initialize the member variables with the given datas.
		this->name = name;
        this->age = age;
        this->sub_date = sub_date;
		this->sub_end_date = sub_end_date;
        this->left = nullptr;
        this->right = nullptr;
		this->parent = nullptr;
	}
	~NameBSTNode() {
		//Changes the addresses of neighboring nodes of the current node to null value and free them.
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		delete left, right, parent;
	}

	string getName() { return name; }		//Return the name of the node.
	int getAge() { return age; }			//Return the age.
	string getSubDate() { return sub_date; }//Return the subscription start date.
	string getSubEndDate() { return sub_end_date; }	//Return the subscription end date.
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
	NameBSTNode* getLeft() { return left; }			//Return the address of the left child node.
	NameBSTNode* getRight() { return right; }		//Return the right child's address.
	NameBSTNode* getParent() { return parent; }		//Return the parent's address.

	void setLeft(NameBSTNode* left) { this->left = left; }			//Set left child with given address.
	void setRight(NameBSTNode* right) { this->right = right; }		//Set right child with given address.
	void setParent(NameBSTNode* parent) { this->parent = parent; }	//Set parent with given address.
};