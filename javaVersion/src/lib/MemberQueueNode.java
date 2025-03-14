package lib;

public class MemberQueueNode {
    private String name;
    private int age;
    private String date;
    private char subscription_type;

    public MemberQueueNode() {}
    public MemberQueueNode(String name, int age, String date, char subscription_type) {
        this.name = name;
        this.age = age;
        this.date = date;
        this.subscription_type = subscription_type;
    }
    public String getName() { return name; }
    public int getAge() { return age; }
    public String getDate() { return date; }
    public char getSubscriptionType() { return subscription_type; }
}
