package lib;
import java.io.*;

public class Manager {
    private BufferedReader command_reader;
    private BufferedWriter log_writer;
    private MemberQueue member_queue;
    private TermsList terms_list;
    private TermsBST[] terms_bst;
    private NameBST name_bst;
    private String log_content;

    public Manager() {
        command_reader = null;
        log_writer = null;
        member_queue = new MemberQueue();
        terms_list = new TermsList();
        name_bst = new NameBST();
        terms_bst = new TermsBST[4];
        log_content = "";
    }

    public void run(String command_file_name) {
        int status = 0, temp;
        String command = "", cmd_temp = "";
        openLogWriter(0);
        try {
            command_reader = new BufferedReader
                    (new FileReader(command_file_name));
        } catch (FileNotFoundException e) {
            try {
                log_writer.write(("Fail to open command file.\n"));
            } catch (IOException f) {
                System.out.println("Cannot open log file.");
                f.printStackTrace();
            }
            e.printStackTrace();
        }
        while (log_writer != null) {
            try {
                command = command_reader.readLine();
            } catch (IOException e) {
                printErrorCode(1000);
                e.printStackTrace();
            }
            temp = command.indexOf(" ");
            if (temp == -1) {
                if (command.compareTo("LOAD") == 0) {
                    status = load();
                    if (status != 0)
                        printErrorCode(status);
                }
                else if (command.compareTo("QPOP") == 0) {
                    status = popFromMemberQueue();
                    if (status != 0)
                        printErrorCode(status);
                    else
                        printSuccess(command);
                }
                else if (command.compareTo("EXIT") == 0) {
                    status = Exit();
                    break;
                }
                else printErrorCode(1000);
            }
            else if (temp == 6) {
                if (command.substring(0, 6).compareTo("SEARCH") == 0) {
                    cmd_temp = command.substring(7);
                    status = search(cmd_temp);
                    if (status != 0)
                        printErrorCode(status);
                }
                else if (command.substring(0, 6).compareTo("DELETE") == 0) {
                    cmd_temp = command.substring(7);
                    status = delete(cmd_temp);
                    if (status != 0)
                        printErrorCode(status);
                    else printSuccess("DELETE");
                }
                else printErrorCode(1000);

            }
            else {
                if (temp == 3 && command.substring(0, 3).equals("ADD")) {
                    cmd_temp = command.substring(4);
                    status = add(cmd_temp);
                    if (status != 0)
                        printErrorCode(status);
                }
                else if (temp == 5 && command.substring(0, 5).equals("PRINT")) {
                    cmd_temp = command.substring(6);
                    status = print(cmd_temp);
                    if (status != 0)
                        printErrorCode(status);
                }
                else printErrorCode(1000);
            }
        }
    }
    public void closeLogWriter() {
        try {
            log_writer.close();
        } catch (IOException e) {
            System.out.println("Error closing log file.");
            e.printStackTrace();
        }
    }
    public void openLogWriter(int append) {
        try {
            if (append == 0)
                log_writer = new BufferedWriter(new FileWriter("./log.txt"));
            else log_writer = new BufferedWriter(new FileWriter("./log.txt", true));
        } catch (IOException e) {
            System.out.println("Cannot open log file.");
            e.printStackTrace();
        }
    }
    public void printSuccess(String command) {
        log_content = log_content.concat("=====" + command + "=====\n");
        log_content = log_content.concat("Success\n");
        log_content = log_content.concat("=========================\n\n");
        writeToLogFile(log_content);
    }
    public void printErrorCode(int error_code) {
        log_content = "===== ERROR =====\n";
        log_content = log_content.concat(error_code + "\n");
        log_content = log_content.concat("=========================\n");
        writeToLogFile(log_content);
    }
    public int load() {
        String information = "", log_content = "";
        BufferedReader data_reader;
        int temp = 0;
        try {
            data_reader = new BufferedReader(new FileReader("./data.txt"));
        } catch (FileNotFoundException e) {
            return 100;
        }
        if (!member_queue.empty() || name_bst.getRoot() != null || terms_list.getHead() != null)
            return 100;
        log_content = "===== LOAD =====\n";
        while (true) {
            try {
                information = data_reader.readLine();
            } catch (IOException e) {
                break;
            }
            if (information == null) break;
            if (information.length() < 16)
                continue;
            for (int j = 0; j < information.length(); j++) {
                if (information.charAt(j) == ' ') {
//                    log_content = log_content.concat(information.substring(temp, j) + "/");
                    log_content += information.substring(temp, j) + "/";
                    temp = j+1;
                }
            }
            temp = 0;
//            log_content = log_content.concat(information.substring(information.length()-1) + "\n");
            log_content += information.substring(information.length()-1) + "\n";
            member_queue.push(information);
        }
        log_content = log_content.concat("======================\n\n");
        writeToLogFile(log_content);
        return 0;
    }
    public int add(String person_data) {
        int temp = 0, operation = member_queue.push(person_data);
        if (operation == 0) {
            log_content = "===== ADD =====\n";
            for (int j = 0; j < person_data.length(); j++) {
                if (person_data.charAt(j) == ' ') {
                    log_content = log_content.concat(person_data.substring(temp, j) + "/");
                    temp = j+1;
                }
            }
            log_content = log_content.concat(person_data.substring(person_data.length()-1) + "\n");
            log_content = log_content.concat("===================\n\n");
            writeToLogFile(log_content);
            return 0;
        }
        return 200;
    }
    public int popFromMemberQueue() {
        if (member_queue.empty())
            return 300;
        MemberQueueNode popped_queue_node;
        BSTNode temp_terms_node, temp_name_node;
        TermsListNode terms_list_it;
        String name, date;
        char subtype;
        int age, sub;

        while (!member_queue.empty()) {
            popped_queue_node = member_queue.pop();
            name = popped_queue_node.getName();
            date = popped_queue_node.getDate();
            subtype = popped_queue_node.getSubscriptionType();
            age = popped_queue_node.getAge();
            temp_terms_node = new BSTNode(name, age, date, subtype);
            sub = (int)subtype - 65;
            if (terms_bst[sub] == null)
                terms_bst[sub] = new TermsBST();
            terms_bst[sub].insert(temp_terms_node);
            terms_list.insert(subtype, terms_bst[sub]);
            temp_terms_node = null;
            temp_name_node = new BSTNode(name, age, date, subtype);
            name_bst.insert(temp_name_node);
            temp_name_node = null;
        }
        return 0;
    }
    public int search(String name) {
        BSTNode it = name_bst.search(name);
        if (it == null)
            return 400;
        log_content = "===== SEARCH =====\n";
        log_content = log_content.concat(it.getName() + "/" + it.getAge() + "/" +
                                            it.getSubDate() + "/" + it.getSubEndDate() + "\n");
        log_content = log_content.concat("======================\n\n");
        writeToLogFile(log_content);
        return 0;
    }
    public int print(String data_for_print) {
        int subtype = (int)data_for_print.charAt(0) - 65;
        if (data_for_print.equals("NAME")) {
            log_content = "===== PRINT =====\n";
            log_content = log_content.concat("\tName BST\n");
            writeToLogFile(log_content);
            closeLogWriter();
            name_bst.print(name_bst.getRoot());
            openLogWriter(1);
            log_content = "=================\n\n";
            writeToLogFile(log_content);
            return 0;
        }
        else if (subtype >= 0 && subtype <= 3) {
            closeLogWriter();
            terms_bst[subtype].print(terms_bst[subtype].getRoot(), (char)(subtype + 65));
            openLogWriter(1);
            writeToLogFile(log_content);
            return 0;
        }
        else
            return 500;

    }
    public int delete (String data_for_delete) {
        String bst_kind = data_for_delete.substring(0, 4);
        if (bst_kind.equals("DATE")) {
            data_for_delete = data_for_delete.substring(5);
            for (int i = 0; i < data_for_delete.length(); i++) {
                if ((i == 4 || i == 7) && (data_for_delete.charAt(i) != '-')) return 600;
                else if ((data_for_delete.charAt(i) != '-') &&
                        ((data_for_delete.charAt(i) < '0') || (data_for_delete.charAt(i) > '9'))) return 600;
            }
            deleteBySubdate(name_bst.getRoot(), data_for_delete);
        }
        else if (bst_kind.equals("NAME")) {
            data_for_delete = data_for_delete.substring(5);
            if (deleteByName(data_for_delete) == -1) return 600;
        }
        else return 600;

        for (int i = 0; i < 4; i++) {
            TermsListNode it = terms_list.search((char)(i+65));
            if ((it != null) && (it.getNumberOfMembers() == 0))
                terms_list.remove((char)(i+65));
        }
        return 0;
    }
    public void deleteBySubdate(BSTNode node, String sub_end_date) {
        if (node != null) {
            deleteBySubdate(node.getLeft(), sub_end_date);
            deleteBySubdate(node.getRight(), sub_end_date);
            int result = sub_end_date.compareTo(node.getSubEndDate()), subtype = node.getSubType() - 65;
            if (result >= 0) {
                BSTNode node2 = null;
                if (terms_bst[subtype].getRoot() != null) {
                    node2 = terms_bst[subtype].search(node.getName(), node.getSubEndDate());
                    terms_bst[subtype].remove(node2);
                }
                terms_list.search(node.getSubType()).updateNumberOfMembers(-1);
                name_bst.remove(node);
            }
        }
        return;
    }
    public int deleteByName(String name) {
        BSTNode it1 = name_bst.search(name);
        if (it1 == null)
            return -1;
        int subtype = (int)it1.getSubType() - 65;
        BSTNode it2;
        TermsListNode it3;
        it2 = terms_bst[subtype].search(name, it1.getSubEndDate());
        terms_bst[subtype].remove(it2);
        it3 = terms_list.search((char)(subtype + 65));
        it3.updateNumberOfMembers(-1);
        name_bst.remove(it1);
        return 0;
    }
    public int Exit() {
        try {
            log_writer.write("===== EXIT =====\nSuccess\n=============");
            log_writer.close();
            command_reader.close();
        } catch (IOException e) {
            System.out.println("Cannot close the log.");
            e.printStackTrace();
        }
        member_queue = null;
        terms_list = null;
        name_bst = null;
        terms_bst[0] = null;
        terms_bst[1] = null;
        terms_bst[2] = null;
        terms_bst[3] = null;
        terms_bst = null;
        return 0;
    }
    public void writeToLogFile (String content) {
        try {
            log_writer.write(content);
        } catch (IOException e) {
            System.out.println("Cannot write the log.");
            e.printStackTrace();
        }
        log_content = "";
    }
}
