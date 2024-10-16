#pragma once
#include "MemberQueueNode.h"
#include <vector>

using namespace std;

class MemberQueue : public MemberQueueNode {
/*	Declare MemberQueue class that stores member information
	added by data file and command file and inherits MemberQueueNode.	*/
private:
	vector<MemberQueueNode> Q;
//Declare Q, a queue with MemberQueueNode class as the data type.
public:
	MemberQueue();
	~MemberQueue();
	bool empty();	//Check whether queue is empty or not.
	bool full();	//Check whether queue is full or not. Number of member is 100 if the queue is full.
	int push(string information);	//Add information to queue.
	MemberQueueNode pop();			//Remove information from queue.
};
