#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Manager {
private:
	ifstream fcmd;		//File stream that will open command file.
	ofstream flog;		//File stream that will open log file.
	MemberQueue* Q;		//Member queue class pointer to store member information from "data.txt".
	TermsLIST* Tlist;	//TermsLIST class pointer to store the number of members by subscription terms and conditions.
//TermsBST class pointer that stores member information in order of subscription time according to subscription terms and condtions.
	TermsBST* TbstA;
	TermsBST* TbstB;
	TermsBST* TbstC;
	TermsBST* TbstD;
	NameBST* Nbst;		//NameBST class pointer that sotres member information in name order.

public:
	Manager();
	~Manager();
	void run(const char* command); 		//Execute the command from the "command.txt" file.
	void PrintSuccess(string cmd); 		//Write the success message to log file.
	void PrintErrorCode(int num); 		//Write the error message to log file.
	int Load(); 				 		//Save the member information in data file to the member queue class.
	int Add(string person_data);  		//Save the member information in command file to the member queue class.
	int Qpop();					  		//Pop the member information from the member queue and save it to the Terms list, Terms BST, and Name BST.
	int Search(const string name);		//Prints member information correspoding to the name entered in the command.
	int Print(string data_for_print);	//Print member information corresponding to the information passed as an argument.
	int Delete(string data_for_delete); //Deletes member information corresponding to the information passed as an argument.
	void DeleteBySubDate(NameBSTNode* node1, const string sub_end_date);
	//Deletes nodes whose subscriptions expire sooner than the date entered.
	int DeleteByName(const string name);
	//Delete the member information corresponding to the name.
	int Exit();							//Terminate the program.
};
