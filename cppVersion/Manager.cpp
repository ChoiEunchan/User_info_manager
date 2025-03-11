#pragma once
#include "Manager.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Manager::Manager() {
//Dynamically assign memeber queue, terms list, terms bsts, and name bst class.
    Q = new MemberQueue();
    Tlist = new TermsLIST();
    Nbst = new NameBST();
    TbstA = new TermsBST();
    TbstB = new TermsBST();
    TbstC = new TermsBST();
    TbstD = new TermsBST();
}
Manager::~Manager() { }

void Manager::run(const char* command_file_name) {
/*//////////////////////////////////////////////////////////////////////////
                function name : run
        Input : const char* - the name of command file
        Output : None
        Purpose : Execute the command.
//////////////////////////////////////////////////////////////////////////*/
    int status = 0;
    string command, cmd_temp;
    fcmd.open(command_file_name);   // Open command file named with "command.txt".
    if (!fcmd) {
        flog << "Fail to open command file" << endl;
        return;
    //If the command file does not exist, write the error message in log file and terminates the program.
    }
    flog.open("log.txt");       //Open log file named log.txt.
    while (fcmd) {  //Executes following codes if the command file exists.
        getline(fcmd, command);
        //Get a single line of commands.
        if (!command.compare("LOAD")) {
            if ((status = Load()) != 0)
                PrintErrorCode(status);
        }
        /*  If the command is "LOAD", executes the function Load.
            If the error occurs in the function, write the error message to the log file.  */
        else if (command.substr(0, 3) == "ADD") {
            cmd_temp = command.substr(4);   //Extract member information from the command.
            if ((status = Add(cmd_temp)) != 0)
                PrintErrorCode(status);
        }
        /*  If the command starts with "ADD", executes the function Add.
            If the error occurs in the function, write the error message to the log file.  */
        else if (!command.compare("QPOP")) {
            if ((status = Qpop()) == 0)
                PrintSuccess(command);
            else
                PrintErrorCode(status);
        }
        /*  If the command is "QPOP", executes the function Qpop.
            If the error occurs in the function, write the error message to the log file.
            If not, outputs the success message.  */
        else if (command.substr(0, 6) == "SEARCH") {
            cmd_temp = command.substr(7);   //Extract member name from the command.
            if ((status = Search(cmd_temp)) != 0)
                PrintErrorCode(status);
        }
        /*  If the command starts with "SEARCH", executes the function Search.
            If the error occurs in the function, write the error message to the log file.  */
        else if (command.substr(0, 5) == "PRINT") {
            cmd_temp = command.substr(6);   //Extract the print condition from the command.
            if ((status = Print(cmd_temp)) != 0)
                PrintErrorCode(status);
        }
        /*  If the command starts with "PRINT", executes the function Print.
            If the error occurs in the function, write the error message to the log file.  */
        else if (command.substr(0, 6) == "DELETE") {
            cmd_temp = command.substr(7);   //Extract deletion conditions.
            if ((status = Delete(cmd_temp)) == 0)
                PrintSuccess("DELETE");
            else
                PrintErrorCode(status);
        }
        /*  If the command starts with "DELETE", executes the function Delete.
            If the error occurs in the function, write the error message to the log file.  */
        else if (command == "EXIT") {
            if (status = Exit() == 0)
                PrintSuccess("EXIT");
            else
                PrintErrorCode(status);
            flog.close();
            break;
        }
        /*  If the command is "EXIT", Executes the function Exit.
            If the error occurs in the function, write the error message to the log file.
            If not, outputs the success code.
            After these actions, close the log file and exit from the loop.  */
        else 
            PrintErrorCode(1000);
        //If the wrong command is entered, write the error message.
    }
    return;
}

void Manager::PrintSuccess(string cmd) {
/*//////////////////////////////////////////////////////////////////////////
                function name : PrintSuccess
        Input : string - command that executed
        Output : None
        Purpose : Print the success message.
//////////////////////////////////////////////////////////////////////////*/
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}

void Manager::PrintErrorCode(int num) {
/*//////////////////////////////////////////////////////////////////////////
                function name : PrintErrorCode
        Input : int - command that executed
        Output : None
        Purpose : Print the success message.
//////////////////////////////////////////////////////////////////////////*/
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "=================" << endl << endl;
}

int Manager::Load() {
/*//////////////////////////////////////////////////////////////////////////
                function name : Load
        Input : None
        Output : int - 0    : Executes successfully
                     - 100  : Error occurs
        Purpose : Load datas into the Member Queue from data file named "data.txt".
//////////////////////////////////////////////////////////////////////////*/
    ifstream data;
    string information = ".";
    int temp = 0, i = 0;
    data.open("data.txt");  //Open the data file named "data.txt"
    if (!data || !Q->empty() || Nbst->getRoot() != nullptr || Tlist->getHead() != nullptr) 
        return 100;
    /*  If the data file does not exist or if there is even one piece of data
    in the Member Queue, Name BST, or Terms List, finish the function and returns error code.     */
    flog << "===== LOAD =====" << endl; //Print "LOAD" into the log file.
    while (!data.eof()) {
    //Executes following codes until the data file is reached at the end of file.
        getline(data, information); //Get a single line of information.
        if (information.length() < 16)
            continue;
        //If the line is too short, go to the beginning of the loop.
        i = 0; temp = 0;
        for (int j = 0; j < 3; j++) {
            temp = information.find(" ", i);
            flog << information.substr(i, temp-i) << "/";
            i = temp+1;
        }
        flog << information[information.length()-1] << endl;
        /*  Write the member information to log file.   */
        Q->push(information);   //Push the node composed of given information to the Member Queue 
    }
    flog << "================" << endl << endl;
    data.close();   //Close the data file.
    return 0;
}

int Manager::Add(string person_data) {
/*//////////////////////////////////////////////////////////////////////////
                function name : Add
        Input : string - Member information
        Output : int - 0    : Executes successfully
                     - 200  : Error occurs
        Purpose : Push the member data into member queue.
//////////////////////////////////////////////////////////////////////////*/
    int temp = 0;
    int operation = Q->push(person_data);   //Push the input data to the member queue.
    if (operation == 0) {
    //If the popping ends successfully, run the following codes.
        flog << "===== ADD =====" << endl;
        for (int j = 0; j < 3; j++) {
            operation = person_data.find(" ", temp);
            flog << person_data.substr(temp, operation - temp) << "/";
            temp = operation+1;
        }
        flog << person_data[person_data.length()-1] << endl;
        flog << "===============" << endl << endl;
        return 0;
        /*  Write the member information to log file and 
            signals that the function completed successfully.   */
    }
    else
        return 200;
    //Signals that the function completed unsuccessfully.
}
int Manager::Qpop() {
/*//////////////////////////////////////////////////////////////////////////
                function name : Qpop
        Input : None
        Output : int - 0    : Executes successfully
                     - 300  : Error occurs
        Purpose : Pop the all of member data in member queue.
                  With those data, push the data into the Terms BST, Name BST,
                  and update the Terms list.
//////////////////////////////////////////////////////////////////////////*/
    if (Q->empty())
        return 300;
    //If the queue is empty, there is no data for pop so returns error code.
    MemberQueueNode temp;
    TermsBSTNode* temp_terms_node;
    TermsListNode* it;
    NameBSTNode* temp_name_node;
    string name, date;
    char subtype;
    int age, sub = 0;

    while (!Q->empty()) {
        temp = Q->pop();    
        name = temp.getName();
        date = temp.getDate();
        subtype = temp.getSubType();
        age = temp.getAge();
        //Pop the data from member queue and get the datas.
        temp_terms_node = new TermsBSTNode(name, age,  date, subtype);
        //Make temporary node with the data that extracted from the popped Member Queue node.
        sub = (int)subtype - 65;    //Convert the subtype to integer.
        switch (sub) {
            case 0:
                TbstA->insert(temp_terms_node);
                Tlist->insert(subtype, TbstA);
                break;
            case 1:
                TbstB->insert(temp_terms_node);
                Tlist->insert(subtype, TbstB);
                break;
            case 2:
                TbstC->insert(temp_terms_node);
                Tlist->insert(subtype, TbstC);
                break;
            case 3:
                TbstD->insert(temp_terms_node);
                Tlist->insert(subtype, TbstD);
                break;
        }
        delete temp_terms_node;
        /*  Push the data extracted into BST matching subtype and initialize the BST
        if the BST information does not exist in the Terms list node.   */

        temp_name_node = new NameBSTNode(name, age,  date, subtype);
        Nbst->insert(temp_name_node);
        /*   Insert the new node in NameBST.   */
        delete temp_name_node;
    }
    return 0;
}
int Manager::Search(const string name) {
/*//////////////////////////////////////////////////////////////////////////
                function name : Search
        Input : string - Name of member data which is looking for.
        Output : int - 0    : Executes successfully
                     - 400  : Error occurs
        Purpose : Prints member information for the entered name.
//////////////////////////////////////////////////////////////////////////*/
    NameBSTNode* it = Nbst->search(name);
    if (it == nullptr)
        return 400;
    //If there is no member information for the entered name, deliver an error code.
    flog << "===== SEARCH =====" << endl;
    flog << it->getName() << "/" << it->getAge() << "/" << it->getSubDate() << "/" << it->getSubEndDate() << endl;
    flog << "==================" << endl << endl;
    return 0;
	//If not, print the information and return the success code.
}
int Manager::Print(string data_for_print) {
/*//////////////////////////////////////////////////////////////////////////
                function name : Print
        Input : string - type of bst to print
        Output : int - 0    : Executes successfully
                     - 500  : Error occurs
        Purpose : Prints member information in bst
                  that corresponds to the entered conditions
//////////////////////////////////////////////////////////////////////////*/
    if (data_for_print[0] == 'A') {
    //Execute follow codes if the printing condition is A.
        if (TbstA->getRoot() == nullptr)
            return 500;
        //Return the error value if Terms bst A does not exist.
        flog << "===== Print =====" << endl << "     Terms_BST A" << endl;
        flog.close();
        TbstA->print(TbstA->getRoot());
        flog.open("log.txt", ios::app);
        flog << "=================" << endl << endl;
        //Output member informations using an inorder traversal.
    }
    else if (data_for_print[0] == 'B') {
    //Execute follow codes if the printing condition is B.
        if (TbstB->getRoot() == nullptr)
            return 500;
        //Return the error value if Terms bst B does not exist.
        flog << "===== Print =====" << endl << "     Terms_BST B" << endl;
        flog.close();
        TbstB->print(TbstB->getRoot());
        flog.open("log.txt", ios::app);
        flog << "=================" << endl << endl;
        //Output member informations.
    }
    else if (data_for_print[0] == 'C') {
    //Execute follow codes if the printing condition is C.
        if (TbstC->getRoot() == nullptr)
            return 500;
        //Return the error value if Terms bst C does not exist.
        flog << "===== Print =====" << endl << "     Terms_BST C" << endl;
        flog.close();
        TbstC->print(TbstC->getRoot());
        flog.open("log.txt", ios::app);
        flog << "=================" << endl << endl;
        //Output member informations.
    }
    else if (data_for_print[0] == 'D') {
    //Execute follow codes if the printing condition is D.
        if (TbstD->getRoot() == nullptr)
            return 500;
        //Return the error value if Terms bst D does not exist.
        flog << "===== Print =====" << endl << "     Terms_BST D" << endl;
        flog.close();
        TbstD->print(TbstD->getRoot());
        flog.open("log.txt", ios::app);
        flog << "=================" << endl << endl;
        //Output member informations.
    }
    else if (data_for_print[0] == 'N') {
    //Execute follow codes if the printing condition is "NAME".
        if (Nbst->getRoot() == nullptr)
            return 500;
        //Return the error value if Name bst does not exist.
        flog << "===== Print =====" << endl << "     Name_BST" << endl;
        flog.close();
        Nbst->print(Nbst->getRoot());
        flog.open("log.txt", ios::app);
        flog << "=================" << endl << endl;
        //Output member informations.
    }
    else
        return 500;
    //If wrong condition is entered, return the error value.
    return 0;
    //Deliver the success cde if printing is successfully completed.
}
int Manager::Delete(string data_for_delete) {
/*//////////////////////////////////////////////////////////////////////////
                function name : Delete
        Input : string - Deletion condition
        Output : int - 0    : Executes successfully
                     - 600  : Error occurs
        Purpose : Delete member information according to conditions received
                  and update the data structure.
//////////////////////////////////////////////////////////////////////////*/
    //Declare iterators for Name bst, terms bst and terms list.
    if (data_for_delete.substr(0, 4) == "DATE") {
    //If the condition of deletion is Date, executes following codes.
        data_for_delete = data_for_delete.substr(5);
        //Extract the date to delete.
        for (int i = 0; i < data_for_delete.length(); i++) {
            if ((i == 4 || i == 7) && data_for_delete[i] != '-')
                return 600;
            else if ((data_for_delete[i] != '-') && (data_for_delete[i] < '0' || data_for_delete[i] > '9'))
                return 600;
        }
        //If the deletion condition is wrong format, return the error code.
        DeleteBySubDate(Nbst->getRoot(), data_for_delete);
        //Call the delete function.
    }
    else if (data_for_delete.substr(0, 4) == "NAME") {
    //Otherwise, if the condition of deletion is name, executes following codes.
        data_for_delete = data_for_delete.substr(5); //Extract the name to delete.
        if (DeleteByName(data_for_delete) == -1)
            return 600;
        /*  Execute the delete function. If there's no member named with given string
            in the tree, return the error code.     */
    }
    else
        return 600;
    //If the wrong condition to delete is entered, return the error code.
    if ( Tlist->search('A') != nullptr && Tlist->search('A')->getNumMembers() == 0) {
        Tlist->remove('A');
    }
    if ( Tlist->search('B') != nullptr && Tlist->search('B')->getNumMembers() == 0) {
        Tlist->remove('B');
    }
    if ( Tlist->search('C') != nullptr && Tlist->search('C')->getNumMembers() == 0) {
        Tlist->remove('C');
    }
    if ( Tlist->search('D') != nullptr && Tlist->search('D')->getNumMembers() == 0) {
        Tlist->remove('D');
    }
    return 0;
    //  If a node with 0 number of members exists in the list, remove the node.
}
void Manager::DeleteBySubDate(NameBSTNode* node1, const string sub_end_date) {
/*//////////////////////////////////////////////////////////////////////////
                function name : DeleteBySubDate
        Input :  NameBSTNode*   - address of the node to delete
                 string         - Deletion condition
        Output : None
        Purpose : Deletes nodes whose period expires before the entered date.
//////////////////////////////////////////////////////////////////////////*/
    if (node1 != nullptr) {
		DeleteBySubDate(node1->getLeft(), sub_end_date);
		DeleteBySubDate(node1->getRight(), sub_end_date);
        //Find the leaf node recursively.
		int result = sub_end_date.compare(node1->getSubEndDate());
        //Determines if the expiration date is earlier than the entered date.
		if (result >= 0) {
        //If so, executes following codes.
            TermsBSTNode* node2 = nullptr;
            switch (node1->getSubType()) {
                case 'A':
                    if (TbstA->getRoot() != nullptr) {
                        node2 = TbstA->search(node1->getName(), node1->getSubEndDate());
                        TbstA->remove(node2);
                    }
                    break;
                case 'B':
                    if (TbstB->getRoot() != nullptr) {
                        node2 = TbstB->search(node1->getName(), node1->getSubEndDate());
                        TbstB->remove(node2);
                    }
                    break;
                case 'C':
                    if (TbstC->getRoot() != nullptr) {
                        node2 = TbstC->search(node1->getName(), node1->getSubEndDate());
                        TbstC->remove(node2);
                    }
                    break;
                case 'D':
                    if (TbstD->getRoot() != nullptr) {
                        node2 = TbstD->search(node1->getName(), node1->getSubEndDate());
                        TbstD->remove(node2);
                    }
                    break;
            }
            //Get the subscription term of the node and remove it from the tree it belongs to.
            Tlist->search(node1->getSubType())->updateNumMembers(-1);
            //Update the node's number of members corresponding to subtype.
            Nbst->remove(node1);
            //Remove the node from the name bst.
        }
	}
	return;
}
int Manager::DeleteByName(const string name) {
/*//////////////////////////////////////////////////////////////////////////
                function name : DeleteByName
        Input :  string         - name that want to delete
        Output : None
        Purpose : Removes member information matching the entered name.
//////////////////////////////////////////////////////////////////////////*/
    NameBSTNode* it1 = Nbst->search(name);    //Find the node to delete.
    if (it1 == nullptr)
        return -1;
    //If no name matches, return the error code.
    char subtype = it1->getSubType();
    TermsBSTNode* it2;
    TermsListNode* it3;
    //if not, get the validity period.
    if (subtype == 'A') {
            it2 = TbstA->search(name, it1->getSubEndDate());
            TbstA->remove(it2);
            it3 = Tlist->search('A');
        }
        else if (subtype == 'B') {
            it2 = TbstB->search(name, it1->getSubEndDate());
            TbstB->remove(it2);
            it3 = Tlist->search('B');
        }
        else if (subtype == 'C') {
            it2 = TbstC->search(name, it1->getSubEndDate());
            TbstC->remove(it2);
            it3 = Tlist->search('C');
        }
        else {
            it2 = TbstD->search(name, it1->getSubEndDate());
            TbstD->remove(it2);
            it3 = Tlist->search('D');
        }
        //Get the subscription term of the node and remove it from the tree it belongs to.
        it3->updateNumMembers(-1);
        //Update the node's number of members corresponding to subtype.
        Nbst->remove(it1);  //Remove the node from the name bst.
        return 0;
    }
int Manager::Exit() {
    fcmd.close();
    //Close the command file.
    delete Q;
    delete Tlist;
    delete Nbst;
    delete TbstA;
    delete TbstB;
    delete TbstC;
    delete TbstD;
    //Free the all of data structures.
    return 0;
    //Finish the function.
}
