#pragma once
#include<string>
#include<iostream>

using namespace std;

class MemberQueueNode {
//Declare MemberQueueNode class that contains a member information.
private:
	string name;
	int age;
	string date;
	char subscription_type;

public:
    MemberQueueNode() {}
    MemberQueueNode(const string name, const int age, const string date, const char subscription_type) {
	//Initialize the member variables with the given datas.
		this->name = name;
        this->age = age;
        this->date = date;
        this->subscription_type = subscription_type;
		return;
	}
	~MemberQueueNode() { }

	inline string getName() { return name; }	//Return the name of the member.
	inline int getAge() { return age; }			//Return the age.
	inline string getDate() {  return date; }	//Return the date that started the subscription.
	inline char getSubType() { return subscription_type; }	//Return the subscription type.
};
