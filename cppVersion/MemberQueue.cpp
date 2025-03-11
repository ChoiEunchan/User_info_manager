#pragma once
#include "MemberQueue.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

MemberQueue::MemberQueue() { }
MemberQueue::~MemberQueue() {
    Q.clear();
    vector<MemberQueueNode>().swap(Q);
}

bool MemberQueue::empty() { return Q.empty(); }
/*//////////////////////////////////////////////////////////////////////////
                function name : empty
        Input : None
        Output : bool - true    : The queue is empty.
                      - false   : the queue is not empty.
        Purpose : Check whether the queue is empty or not.
//////////////////////////////////////////////////////////////////////////*/
bool MemberQueue::full() { return (Q.size() == 100)? true : false; }
/*//////////////////////////////////////////////////////////////////////////
                function name : full
        Input : None
        Output : bool - true    : The queue is full. This means number of memebers is 100.
                      - false   : the queue is not full.
        Purpose : Check whether the queue is full or not.
//////////////////////////////////////////////////////////////////////////*/
int MemberQueue::push(string information) {
/*//////////////////////////////////////////////////////////////////////////
                function name : push
        Input : string  - Data which is contain a information of new member.
        Output : int  - 0    : Pushing is completed.
                      - -1   : Error occurs.
        Purpose : Push new member in the queue.
//////////////////////////////////////////////////////////////////////////*/
    if (full()) return -1;
    //If the queue is full, do not push anything and return the error code.
	string name, age, date;
    char subtype;
    int count = 0, temp = 0, num = 0;
    for (int j = 0; j < 3; j++) {
        temp = information.find(" ", count);
        if (temp == -1)
            break;
        //If can't find the blank character, exit the loop.
        if (j == 0) {
            name = information.substr(count, temp-count);   //Extract member name from the input string.
            if (name.length() > 20)
                break;
            /*  If the member name's length is more than 20 characters,
                return the error code.  */
            for (int i = 0; i < name.length(); i++) {
                if (name[i] < 'a' || name[i] > 'z') {
                    num--;
                    break;
                }
            }
            /*   If the name contains characters other than lowercase letters, exit the loop.   */
        }
        else if (j == 1) {
            age = information.substr(count, temp-count);
            //Extract member age.
            if (age.length() > 2 || stoi(age) > 100 || stoi(age) < 10)
                break;
            //If the age is greater than 100, less than 10, or the age is not a natural number, return -1.
        }
        else if (j == 2) {
            date = information.substr(count, temp-count);
            //Extract subscription start date.
            if (date.length() != 10)
                break;
            //If the date format does not match "XXXX-XX-XX", return -1.
            for (int k = 0; k < date.length(); k++) {
                if (date[k] < '0' || date[k] > '9') {
                    if ((k == 4 || k == 7) && date[k] == '-')
                            continue;
                    else {
                        num--;
                        break;
                        /*  If the date is not made up of numbers or the "-" is not in the desired position,
                            decrease the num value by 1.    */
                    }
                }
            }
        }
        count = temp+1;
        num++;
        //Update the position where the search for space characters begins and increase the numvalue by 1.
    }
    if (num < 3 || temp == -1)
        return -1;
    /*  If number of extracted informations is less than 3, or if the loop is exited
        without finding a space character, return  the error code and terminate the function.  */
    subtype = information[information.length() - 1];    //Get the subscription type.
    if (subtype < 'A' && subtype > 'D')
        return -1;
    //If the subscription type is not 'A', 'B', 'C', or 'D', return -1.
    MemberQueueNode tempnode(name, stoi(age), date, subtype);
    Q.push_back(tempnode);
    return 0;
}
MemberQueueNode MemberQueue::pop() {
/*//////////////////////////////////////////////////////////////////////////
                function name : pop
        Input : None
        Output : MemberQueueNode - member information poped.
        Purpose : Erase member information from the queue and return the information.
//////////////////////////////////////////////////////////////////////////*/
    string name, date;
    char subtype;
    int age = 0;
    vector<MemberQueueNode>::iterator it = Q.begin();
    //Declare iterator for find member that first entered.
    name = it->getName();
    age = it->getAge();
    date = it->getDate();
    subtype = it->getSubType();
    //Get the member information.
    MemberQueueNode temp(name, age, date, subtype);
    Q.erase(it);
    return temp;
    //Erase the node from member queue and return the information.
}