// Name: Diya Goyal
// Roll no: 102215255
// Question: Write a program for binary search tree (BST) having functions for the following operations:
// Insert an element (no duplicates are allowed),
// Delete an existing element,
// Traverse the BST (in-order, pre-order, and post-order),
// Maximum depth, and Minimum depth.
// Acknowledgement: took help from GitHub Copilot


#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root(nullptr) {}

    void insert(int val) {
        root = insertNode(root, val);
    }

    void remove(int val) {
        root = deleteNode(root, val);
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }

    void preorder() {
        preorderTraversal(root);
        cout << endl;
    }

    void postorder() {
        postorderTraversal(root);
        cout << endl;
    }

    int maxDepth() {
        return findMaxDepth(root);
    }

    int minDepth() {
        return findMinDepth(root);
    }

private:
    Node* root;

    Node* insertNode(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insertNode(node->left, val);
        else if (val > node->data) node->right = insertNode(node->right, val);
        return node;
    }

    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = deleteNode(node->left, val);
        else if (val > node->data) node->right = deleteNode(node->right, val);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* succ = findMin(node->right);
                node->data = succ->data;
                node->right = deleteNode(node->right, succ->data);
            }
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void inorderTraversal(Node* node) {
        if (!node) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node* node) {
        if (!node) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }

    int findMaxDepth(Node* node) {
        if (!node) return 0;
        int leftDepth = findMaxDepth(node->left);
        int rightDepth = findMaxDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

    int findMinDepth(Node* node) {
        if (!node) return 0;
        int leftDepth = findMinDepth(node->left);
        int rightDepth = findMinDepth(node->right);
        if (!node->left || !node->right) return max(leftDepth, rightDepth) + 1;
        return min(leftDepth, rightDepth) + 1;
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder:   "; tree.inorder();
    cout << "Preorder:  "; tree.preorder();
    cout << "Postorder: "; tree.postorder();

    cout << "Max Depth: " << tree.maxDepth() << endl;
    cout << "Min Depth: " << tree.minDepth() << endl;

    tree.remove(20);
    tree.remove(70);

    cout << "Inorder after deletions: ";
    tree.inorder();

    return 0;
}