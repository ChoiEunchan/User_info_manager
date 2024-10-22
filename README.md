# Basic data structure implementation
### There may be errors when running in a Windows or other environment so LINUX environment is recommended.
- This project is implementation of Binary Search Tree(BST) & various data structures, such as linked list and queue.\
Member information is including `name`, `age`, `collection date` and `type`.\
The data format and conditions are as follows.
    ```
    1. The member's name consists of lowercase letters without spaces, and is no more than 20 characters long.
       In addition, there are no duplicate member names.
    2. Age is entered in the form of a natural number and is limited to the range of 10~99 years old.
    3. The date of collection of personal information is entered in the format XXXX-XX-XX.
    4. The terms and conditions are entered in one of the capital letters A, B, C, and D.
       A: 6 month, B: 1 year, C: 2 years, D: 3 years
    5. The arguments in each data are all separated by space characters.
    6. Each member information is written by line and is divided by a new character.
    ```

- User info manager is worked some commands, `LOAD`, `ADD`, `QPOP`, `SEARCH`, `PRINT`, `DELETE` and `EXIT`.\
Each commands are explained in following table.

    <table>
        <tr>
            <th colspan='4'> <h2>Command Workout</h2></td>
        </tr>
        <tr>
            <th> Command </td>
            <th> Work </td>
            <th> Error code </td>
            <th> Example </td>
        </tr>
        <tr>
            <td> LOAD </td>
            <td> 1. Load data from text file.<br/>
                2. Save member information to "Member_Queue".<br/>
            </td>
            <td> 100 </td>
            <td> LOAD </td>
        </tr>
        <tr>
            <td> ADD </td>
            <td> Add member data into "Member_Queue". </td>
            <td> 200 </td>
            <td> ADD chan 50 2024-10-21 C </td>
        </tr>
        <tr>
            <td> QPOP </td>
            <td> 1. Pop out datas from "Member_Queue"<br/>
                2. Build "Terms_list", "Terms_BST" and "Name_BST" with data from the Queue.</td>
            <td> 300 </td>
            <td> QPOP </td>
        </tr>
        <tr>
            <td> SEARCH </td>
            <td> Prints member information corresponding to the entered name. </td>
            <td> 400 </td>
            <td> SEARCH chan </td>
        </tr>
        <tr>
            <td> PRINT </td>
            <td> Print all the data saved in BST with following format.<br/>
                name/age/collection date/type<br/>
                If type(A or B or C or D) is entered, print data from "Terms_BST"<br/>
                If "NAME" is entered, print "Name_BST".
            </td>
            <td> 500 </td>
            <td> PRINT B<br/>PRINT NAME </td>
        </tr>
        <tr>
            <td> DELETE </td>
            <td> Delete member information from list & BSTs. Date or name must be delivered.<br/>
                If "DATE XXXX-XX-XX" is entered, delete all members with an expiration date earlier than that date<br/>
                will be removed from all Terms_BST.<br/>
                If "NAME xxxxx" is entered, delete the member if member information for the entered name exists.<br/>
                Member data must be deleted from all of list and BSTS, "Terms_List", "Terms_BST" and "Name_BST".
            </td>
            <td> 600 </td>
            <td>  DELETE DATE 2024-10-21<br/>
                DELETE NAME chan
            </td>
        </tr>
        <tr>
            <td> EXIT </td>
            <td> Free the program from memory and terminate the program. </td>
            <td> 700 </td>
            <td> EXIT </td>
        </tr>
    </table>

    <table>
        <tr>
            <th colspan='2'> <h2>Error condition</h2></td>
        </tr>
        <tr>
            <th> Command </td>
            <th> Situation that error's occured </td>
        </tr>
        <tr>
            <td> LOAD </td>
            <td> 1. Data file does not exist.<br/>
                2. Any member information is in "Member_Queue".<br/>
            </td>
        </tr>
        <tr>
            <td> ADD </td>
            <td> Data format is not fit. </td>
        </tr>
        <tr>
            <td> QPOP </td>
            <td> There's no data in "Member_Queue"</td>
        </tr>
        <tr>
            <td> SEARCH </td>
            <td> No names match. </td>
        </tr>
        <tr>
            <td> PRINT </td>
            <td> There's no data in BST.</td>
        </tr>
        <tr>
            <td> DELETE </td>
            <td> 1. If the member information you want to delete does not exist. <br/>
                2. If there is no data in the data structure, Terms_List and BSTs.
            </td>
            </td>
        </tr>
    </table>

- After run this program, log file `log.txt` is remained and there are result of each command.
- Run following codes when you run this program. Current directory must be the root directory of this project.
    ``` bash
    make
    ./run
    ```

Reference : https://github.com/KIMMINTAE98/2023_Kwangwoon_Univ_CE_DS_Project_1