// red black tree
#include <iostream>     // Provides basic I/O functionality
#include <memory>       // Provides smart pointers if needed

using namespace std;    // Allows direct use of standard library objects

enum Color { RED, BLACK };  // Defines two node colors

struct Node {
    int data;                   // Stores the node's value
    Color color;                // Stores the node's color (RED or BLACK)
    Node* left;                 // Pointer to the left child
    Node* right;                // Pointer to the right child
    Node* parent;               // Pointer to the parent node

    Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    // Constructor initializes data and sets color as RED by default
};

class RedBlackTree {
private:
    Node* root; // Pointer to the root of the tree

    void leftRotate(Node* x) {
        Node* y = x->right;         // y is the right child of x
        x->right = y->left;         // Move y's left subtree to x's right
        if (y->left != nullptr) {
            y->left->parent = x;    // Update parent pointer
        }
        y->parent = x->parent;      // Link y to x's former parent
        if (x->parent == nullptr) {
            root = y;               // y becomes root if x was root
        } else if (x == x->parent->left) {
            x->parent->left = y;    // If x was a left child, update that link
        } else {
            x->parent->right = y;   // Otherwise update the right child link
        }
        y->left = x;                // Put x on y's left
        x->parent = y;             // Update x's parent
    }

    void rightRotate(Node* x) {
        Node* y = x->left;          // y is the left child of x
        x->left = y->right;         // Move y's right subtree to x's left
        if (y->right != nullptr) {
            y->right->parent = x;   // Update parent pointer
        }
        y->parent = x->parent;      // Link y to x's former parent
        if (x->parent == nullptr) {
            root = y;               // y becomes root if x was root
        } else if (x == x->parent->right) {
            x->parent->right = y;   // If x was a right child, update that link
        } else {
            x->parent->left = y;    // Otherwise update the left child link
        }
        y->right = x;               // Put x on y's right
        x->parent = y;             // Update x's parent
    }

    void fixInsertion(Node* z) {
        // While parent's color is RED, we need to fix violations
        while (z->parent && z->parent->color == RED) {
            // Check if parent is on the left side
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;  // Uncle is parent's sibling
                // Case 1: Uncle is RED
                if (y && y->color == RED) {
                    z->parent->color = BLACK;         // Recolor parent
                    y->color = BLACK;                 // Recolor uncle
                    z->parent->parent->color = RED;   // Recolor grandparent
                    z = z->parent->parent;            // Move z up
                } else {
                    // Case 2: Uncle is BLACK and z is a right child
                    if (z == z->parent->right) {
                        z = z->parent;                // Move z up
                        leftRotate(z);                // Rotate
                    }
                    // Case 3: z is a left child
                    z->parent->color = BLACK;         // Recolor parent
                    z->parent->parent->color = RED;   // Recolor grandparent
                    rightRotate(z->parent->parent);   // Rotate grandparent
                }
            } else {
                // Parent is on right side
                Node* y = z->parent->parent->left;   // Uncle is parent's sibling
                // Case 1: Uncle is RED
                if (y && y->color == RED) {
                    z->parent->color = BLACK;         // Recolor parent
                    y->color = BLACK;                 // Recolor uncle
                    z->parent->parent->color = RED;   // Recolor grandparent
                    z = z->parent->parent;            // Move z up
                } else {
                    // Case 2: Uncle is BLACK and z is a left child
                    if (z == z->parent->left) {
                        z = z->parent;                // Move z up
                        rightRotate(z);               // Rotate
                    }
                    // Case 3: z is a right child
                    z->parent->color = BLACK;         // Recolor parent
                    z->parent->parent->color = RED;   // Recolor grandparent
                    leftRotate(z->parent->parent);    // Rotate grandparent
                }
            }
        }
        root->color = BLACK; // Ensure root remains BLACK
    }

    void inorderHelper(Node* root) {
        // Recursively traverse the tree in-order
        if (!root) return;
        inorderHelper(root->left);
        cout << root->data << "(" << (root->color == RED ? "R" : "B") << ") ";
        inorderHelper(root->right);
    }

public:
    RedBlackTree() : root(nullptr) {} // Constructor initializes root to null

    void insert(int val) {
        Node* newNode = new Node(val); // Create a new node
        if (!root) {
            newNode->color = BLACK;    // Root is always BLACK
            root = newNode;            // Set new node as root
            return;
        }
        Node* temp = root;            // Start from root
        Node* parent = nullptr;       // Will track where new node should go

        // Standard BST insertion
        while (temp) {
            parent = temp;
            if (newNode->data < temp->data) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        newNode->parent = parent;     // Link new node to parent
        if (newNode->data < parent->data) {
            parent->left = newNode;   // Place new node as left child
        } else {
            parent->right = newNode;  // Place new node as right child
        }

        fixInsertion(newNode);        // Fix any red-black violations
    }

    void inorderTraversal() {
        inorderHelper(root); // Perform in-order traversal
        cout << endl;
    }
};

int main() {
    RedBlackTree rbTree;         // Create our red-black tree

    // Insert sample data
    rbTree.insert(10);
    rbTree.insert(18);
    rbTree.insert(7);
    rbTree.insert(15);
    rbTree.insert(16);
    rbTree.insert(30);
    rbTree.insert(25);
    rbTree.insert(40);

    cout << "In-order Traversal: ";
    rbTree.inorderTraversal();   // Print the tree in-order

    return 0;                    // End of program
}