package lib;
import java.util.Iterator;
import java.util.Vector;

public class MemberQueue extends MemberQueueNode{
    private Vector<MemberQueueNode> Q;

    public MemberQueue() { Q = new Vector<MemberQueueNode>(); }
    public boolean empty() { return Q.isEmpty(); }
    public boolean full() { return (Q.size() == 100); }

    public int push(String information) {
        if (full()) return -1;

        String name = null, age = null, date = null;
        char subtype;
        int count = 0, temp = 0, num = 0, age_to_int = 0;
        for (int j = 0; j < 3; j++) {
            temp = information.indexOf(" ", count);
            if (temp == -1) break;
            if (j == 0) {
                name = information.substring(count, temp);
                if (name.length() > 20) break;
                for (int i = 0; i < name.length(); i++) {
                    if (name.charAt(i) < 'a' || name.charAt(i) > 'z') {
                        num--;
                        break;
                    }
                }
            }
            else if (j == 1) {
                age = information.substring(count, temp);
                try {
                    age_to_int = Integer.parseInt(age);
                } catch (NumberFormatException e) {
                    break;
                }
                if (age.length() > 2 || age_to_int > 100 || age_to_int < 10) break;
            }
            else if (j == 2) {
                date = information.substring(count, temp);
                if (date.length() != 10) break;
                for (int k = 0; k < date.length(); k++) {
                    if (date.charAt(k) < '0' || date.charAt(k) > '9') {
                        if ((k == 4 || k == 7) && (date.charAt(k) == '-')) continue;
                        else {
                            num--;
                            break;
                        }

                    }
                }
            }
            count = temp+1;
            num++;
        }
        if (num < 3 || temp == -1)
            return -1;
        subtype = information.charAt(information.length()-1);
        if (subtype < 'A' || subtype > 'D') return -1;

        MemberQueueNode tempnode = new MemberQueueNode(name, age_to_int, date, subtype);
        Q.add(tempnode);
        return 0;
    }

    public MemberQueueNode pop() {
        String name, date;
        char subtype;
        int age = 0;;
        name = Q.firstElement().getName();
        date = Q.firstElement().getDate();
        age = Q.firstElement().getAge();
        subtype = Q.firstElement().getSubscriptionType();
        MemberQueueNode temp = new MemberQueueNode(name, age, date, subtype);
        Q.remove(Q.firstElement());
        return temp;
    }
}
