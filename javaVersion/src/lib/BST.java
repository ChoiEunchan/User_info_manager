package lib;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;

public abstract class BST {
    private BSTNode root;

    public BST() {root = null;}
    public abstract BSTNode getRoot();
    public abstract void insert(BSTNode node);
    public void print(BSTNode node) {
        if (node.getLeft() != null)
            print(node.getLeft());
        String contents = node.getName() + "/" + node.getAge() + "/" + node.getSubDate() + "/" + node.getSubEndDate() + "\n";
        try {
            BufferedWriter br = new BufferedWriter(new FileWriter("./log.txt", true));
            br.write(contents);
            br.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error writing to log file");
            e.printStackTrace();
        }
        if (node.getRight() != null)
            print(node.getRight());
    }
    public void remove(BSTNode node) {
        if (node == null) return;

        BSTNode it = null, temp, node_left_child = node.getLeft(), node_right_child = node.getRight();
        int degree = 0;
        if (node_left_child != null) degree++;
        if (node_right_child != null) degree++;

        if (degree == 2) {
            it = node.getRight();
            degree = 0;
            while (it.getLeft() != null) {
                it = it.getLeft();
                degree++;
            }
            // 삭제할 노드의 오른쪽 서브트리에서 키값이 가장 작은 자식으로 이동.
            temp = new BSTNode(it.getName(), it.getAge(), it.getSubDate(), it.getSubEndDate());
            temp.setLeft(node.getLeft());
            node.getLeft().setParent(temp);
            // 삭제할 노드의 왼쪽 자식과 대체할 노드를 연결.
            if (degree > 1) {
                temp.setRight(node.getRight());
                node.getRight().setParent(temp);
            }
            // 오른쪽 서브트리의 height 가 2 이상일 때 대체할 노드와 서브트리의 루트를 연결.
            if (it.getRight() != null) {
                it.getParent().setLeft(it.getRight());
                it.getRight().setParent(it);
            }
            // 대체할 노드에 오른쪽 자식이 있다면 대체 노드의 원래 부모와 자식을 연결.
            it = node.getParent();
            if (it == null) root = temp;
            else {
                if (it.getLeft() == node) it.setLeft(temp);
                else it.setRight(temp);
                temp.setParent(it);
            }
            // 삭제할 노드가 루트라면 대체할 노드를 루트로 설정, 아니라면 삭제할 노드의 부모와 자신을 연결.
        }
        else if (degree == 1) {
            // degree = 1
            if (node_left_child != null) it = node.getLeft();
            else it = node.getRight();

            it.setParent(node.getParent());
            if (node == root) root = it;
            else if (node.getParent().getLeft() == node) node.getParent().setLeft(it);
            else node.getParent().setRight(it);

        }
        else { // degree = 0
            it = node.getParent();
            if (it != null) {
                if (node == it.getLeft()) it.setLeft(null);
                else it.setRight(null);
            }
            else root = null;
        }
        node = null;
        return;
    }

}
