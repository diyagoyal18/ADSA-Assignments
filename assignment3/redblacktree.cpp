// Name: Diya Goyal
// Roll no: 102215255
// Question:  Write a program for Red-Black (RB) tree having functions for the following operations:
// Insert an element (no duplicates are allowed),
// Delete an existing element,                
// Traverse the RB (in- order, pre-order, and post-order),            
// Right rotation, and Left rotation.
// Acknowledgement: took help from GitHub Copilot and geeks for geeks


#include <iostream>
#include <memory>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsertion(Node* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorderHelper(Node* root) {
        if (!root) return;
        inorderHelper(root->left);
        cout << root->data << (root->color == RED ? "(R) " : "(B) ");
        inorderHelper(root->right);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        if (!root) {
            newNode->color = BLACK;
            root = newNode;
            return;
        }
        Node* temp = root;
        Node* parent = nullptr;
        while (temp) {
            parent = temp;
            if (newNode->data < temp->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        newNode->parent = parent;
        if (newNode->data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        fixInsertion(newNode);
    }

    void inorderTraversal() {
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree rbTree;
    rbTree.insert(10);
    rbTree.insert(18);
    rbTree.insert(7);
    rbTree.insert(15);
    rbTree.insert(16);
    rbTree.insert(30);
    rbTree.insert(25);
    rbTree.insert(40);
    cout << "In-order Traversal: ";
    rbTree.inorderTraversal();
    return 0;
}