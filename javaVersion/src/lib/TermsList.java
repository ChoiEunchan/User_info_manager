package lib;

public class TermsList extends TermsListNode {
    private TermsListNode head;

    public TermsList() { head = null; }

    public TermsListNode getHead() { return head; }
    public void insert(char subtype, TermsBST bst) {
        if (head == null) {
            head = new TermsListNode(subtype, bst);
            return;
        }
        TermsListNode it = head, temp = null;

        while (it != null) {
            if (it.getSubscriptionType() == subtype) {
                it.updateNumberOfMembers(1);
                return;
            }
            temp = it;
            it = it.getNext();
        }
        if (subtype >= 'A' && subtype <= 'D') {
            it = new TermsListNode(subtype, bst);
            temp.setNext(it);
        }
    }
    public TermsListNode search(char subtype) {
        TermsListNode it = head;
        while (it != null) {
            if (it.getSubscriptionType() == subtype) return it;
            it = it.getNext();
        }
        return it;
    }
    public void remove(char subtype) {
        TermsListNode it = head;
        TermsListNode prev = null;
        while (it != null) {
            if (it.getSubscriptionType() == subtype) {
                if (it == head) head = head.getNext();
                else if (it.getNext() != null) prev.setNext(it.getNext());
                else prev.setNext(null);
                it = null;
                return;
            }
            prev = it;
            it = it.getNext();
        }
        return;
    }
}
