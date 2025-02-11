// Name: Diya Goyal
// Roll no: 102215255
// Question: Use AVL tree to manage a student database, i.e. allow search, insert and delete operations. Each node of the AVL tree will store a record containing information about a single student (Roll number, Name, CGPA). Use 'Roll number' as a primary key. The program will read a text file containing student information, and build an initial AVL tree containing nodes for those students. Next, the program will take student information from the user to perform any of the allowed operations.
// Acknowledgement: took help from GitHub Copilot

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float CGPA;
};

struct Node {
    Student data;
    Node* left;
    Node* right;
    int height;
    Node(Student s) : data(s), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Rotate right
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

// Rotate left
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

// Insert a new student record into the AVL tree
Node* insertNode(Node* root, Student s) {
    if (!root) return new Node(s);

    // Use rollNo as key
    if (s.rollNo < root->data.rollNo)
        root->left = insertNode(root->left, s);
    else if (s.rollNo > root->data.rollNo)
        root->right = insertNode(root->right, s);
    else
        return root; // no duplicates by rollNo

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Rebalance
    int balance = getBalance(root);

    // Left Left
    if (balance > 1 && s.rollNo < root->left->data.rollNo)
        return rightRotate(root);

    // Right Right
    if (balance < -1 && s.rollNo > root->right->data.rollNo)
        return leftRotate(root);

    // Left Right
    if (balance > 1 && s.rollNo > root->left->data.rollNo) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left
    if (balance < -1 && s.rollNo < root->right->data.rollNo) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find the node with the minimum rollNo in the subtree
Node* minValueNode(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Delete a student record by rollNo from the AVL tree
Node* deleteNode(Node* root, int rollNo) {
    if (!root) return root;

    if (rollNo < root->data.rollNo)
        root->left = deleteNode(root->left, rollNo);
    else if (rollNo > root->data.rollNo)
        root->right = deleteNode(root->right, rollNo);
    else {
        // Single child or no child
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        // Two children
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.rollNo);
    }

    if (!root) return root;

    // Update height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Rebalance
    int balance = getBalance(root);

    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

// Search for a student by rollNo
Node* searchNode(Node* root, int rollNo) {
    if (!root || root->data.rollNo == rollNo)
        return root;
    if (rollNo < root->data.rollNo)
        return searchNode(root->left, rollNo);
    else
        return searchNode(root->right, rollNo);
}

// Inorder traversal (for demonstration)
void inorderPrint(Node* root) {
    if (!root) return;
    inorderPrint(root->left);
    cout << root->data.rollNo << " | " << root->data.name
         << " | " << root->data.CGPA << endl;
    inorderPrint(root->right);
}

// Build initial tree from a file
Node* buildTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open file " << filename << endl;
        return nullptr;
    }
    Node* root = nullptr;
    int roll;
    string name;
    float cgpa;
    while (file >> roll >> ws && getline(file, name, ',') && file >> cgpa) {
        // Example input line format: 100 John,8.5
        // Adjust parsing logic if your file format differs
        Student s{roll, name, cgpa};
        root = insertNode(root, s);
    }
    file.close();
    return root;
}

int main() {
    // Build initial tree from file
    Node* root = buildTreeFromFile("students.txt");

    // Show initial records
    cout << "Initial records (inorder):" << endl;
    inorderPrint(root);

    // Insert new student
    {
        Student st{101, "Alice", 9.0};
        Student st1{104, "Joy", 8.0};
        Student st2{102, "Diya", 9.8};
        Student st3{56, "Prabgun", 9.1};
        Student st4{34, "Joel", 9.3};
        Student st5{200, "Eva", 9.2};
        Student st6{321, "Simar", 7.0};
        Student st7{100, "Harish", 10.0};
        root = insertNode(root, st);
        root = insertNode(root, st1);
        root = insertNode(root, st2);
        root = insertNode(root, st3);
        root = insertNode(root, st4);
        root = insertNode(root, st5);
        root = insertNode(root, st6);
        root = insertNode(root, st7);
    }

    // Delete a student by rollNo
    root = deleteNode(root, 100);

    // Search for a student
    Node* found = searchNode(root, 101);
    if (found) {
        cout << "\nFound: Roll No " << found->data.rollNo
             << ", Name " << found->data.name
             << ", CGPA " << found->data.CGPA << endl;
    } else {
        cout << "\nStudent not found." << endl;
    }

    cout << "\nRecords after modifications (inorder):" << endl;
    inorderPrint(root);

    return 0;
}