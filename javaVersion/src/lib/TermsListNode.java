package lib;

public class TermsListNode {
    private char subscription_type;
    private int number_of_members;
    private TermsBST bst;
    TermsListNode next;

    public TermsListNode() {
        subscription_type = '\0';
        bst = null;
        number_of_members = 1;
        next = null;
    }
    public TermsListNode(char subscription_type) {
        this.subscription_type = subscription_type;
        bst = null;
        number_of_members = 1;
        next = null;
    }
    public TermsListNode(TermsBST bst) {
        subscription_type = '\0';
        this.bst = bst;
        number_of_members = 1;
        next = null;
    }
    public TermsListNode(char subscription_type, TermsBST bst) {
        this.subscription_type = subscription_type;
        this.bst = bst;
        number_of_members = 1;
        next = null;
    }

    public TermsListNode getNext() { return next; }
    public int getNumberOfMembers() { return number_of_members; }
    public char getSubscriptionType() { return subscription_type; }
    public TermsBST getBST() { return bst; }

    public int updateNumberOfMembers(int additional_members) {
        number_of_members += additional_members;
        return number_of_members;
    }
    public void setNext(TermsListNode next) { this.next = next; }
}
