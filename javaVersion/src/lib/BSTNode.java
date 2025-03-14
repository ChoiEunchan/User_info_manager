package lib;

public class BSTNode {
    private String name;
    private int age;
    private String sub_date;
    private String sub_end_date;
    private BSTNode left;
    private BSTNode right;
    private BSTNode parent;

    public BSTNode() {
        name = ".";
        age = 0;
        sub_date = ".";
        sub_end_date = ".";
        left = null;
        right = null;
        parent = null;
    }

    public BSTNode(String name, int age, String sub_date, char subtype) {
        this.name = name;
        this.age = age;
        this.sub_date = sub_date;
        this.sub_end_date = "";
        left = null;
        right = null;
        parent = null;

        int months = 0;
        months = Integer.parseInt(sub_date.substring(5,7));
        months += Integer.parseInt(sub_date.substring(0,4)) * 12;
        switch(subtype) {
            case 'A': {
                months += 6;
                break;
            }
            case 'B': {
                months += 12;
                break;
            }
            case 'C': {
                months += 24;
                break;
            }
            case 'D': {
                months += 36;
                break;
            }
        }
        sub_end_date = Integer.toString(months/12);
        months %= 12;
        if (months < 10)
            sub_end_date = sub_end_date.concat("-0" + Integer.toString(months));
        else sub_end_date = sub_end_date.concat("-" + Integer.toString(months));
        sub_end_date = sub_end_date.concat(sub_date.substring(7));
    }
    public BSTNode(String name, int age, String sub_date, String sub_end_date) {
        //Initialize the member variables with the given datas.
        this.name = name;
        this.age = age;
        this.sub_date = sub_date;
        this.sub_end_date = sub_end_date;
        this.left = null;
        this.right = null;
        this.parent = null;
    }

    public String getName() { return name; }
    public int getAge() { return age; }
    public String getSubDate() { return sub_date; }
    public String getSubEndDate() { return sub_end_date; }
    public char getSubType() {
        int subtype = Integer.parseInt(sub_end_date.substring(0, 4))*12;
        subtype += Integer.parseInt(sub_end_date.substring(5, 7));
        subtype -= Integer.parseInt(sub_date.substring(0, 4))*12;
        subtype -= Integer.parseInt(sub_date.substring(5, 7));
        if (subtype == 6) return 'A';
        else if (subtype == 12) return 'B';
        else if (subtype == 24) return 'C';
        else return 'D';
    }

    public BSTNode getLeft() { return left; }
    public BSTNode getRight() { return right; }
    public BSTNode getParent() { return parent; }

    public void setLeft(BSTNode left) { this.left = left; }
    public void setRight(BSTNode right) { this.right = right; }
    public void setParent(BSTNode parent) {this.parent = parent;}
}
