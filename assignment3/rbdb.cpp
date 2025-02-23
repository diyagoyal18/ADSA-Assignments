// Name: Diya Goyal
// Roll no: 102215255
// Question: Use RB tree to manage a student database, i.e. allow search, insert and delete operations.     Each node of the RB tree will store a record containing information about a single student (Roll number, Name, CGPA). Use 'Roll number' as a primary key. The program will read a text file containing student information, and build an initial RB tree containing nodes for     those students. Next, the program will take student information from the user to perform any of the allowed operations. Compare this RB tree implementation with that done using AVL tree during Lab Assignment 2 in terms of number of rotations performed.
// Acknowledgement: took help from GitHub Copilot 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

struct Student {
    int rollNo;
    string name;
    float CGPA;
};

struct RBNode {
    Student data;
    Color color;
    RBNode *left, *right, *parent;
    RBNode(Student s) : data(s), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    RBNode* root;
    int rotationCount;

    void leftRotate(RBNode* x) {
        rotationCount++;
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBNode* x) {
        rotationCount++;
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(RBNode* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right;
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
                RBNode* y = z->parent->parent->left;
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

    RBNode* minNode(RBNode* x) {
        while (x->left) x = x->left;
        return x;
    }

    void fixDelete(RBNode* x) {
        while (x != root && (!x || x->color == BLACK)) {
            if (x == x->parent->left) {
                RBNode* sib = x->parent->right;
                if (sib->color == RED) {
                    sib->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    sib = x->parent->right;
                }
                if ((!sib->left || sib->left->color == BLACK) &&
                    (!sib->right || sib->right->color == BLACK)) {
                    sib->color = RED;
                    x = x->parent;
                } else {
                    if (!sib->right || sib->right->color == BLACK) {
                        if (sib->left) sib->left->color = BLACK;
                        sib->color = RED;
                        rightRotate(sib);
                        sib = x->parent->right;
                    }
                    sib->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sib->right) sib->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                RBNode* sib = x->parent->left;
                if (sib->color == RED) {
                    sib->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    sib = x->parent->left;
                }
                if ((!sib->left || sib->left->color == BLACK) &&
                    (!sib->right || sib->right->color == BLACK)) {
                    sib->color = RED;
                    x = x->parent;
                } else {
                    if (!sib->left || sib->left->color == BLACK) {
                        if (sib->right) sib->right->color = BLACK;
                        sib->color = RED;
                        leftRotate(sib);
                        sib = x->parent->left;
                    }
                    sib->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (sib->left) sib->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x) x->color = BLACK;
    }

    void rbTransplant(RBNode* u, RBNode* v) {
        if (!u->parent) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    RBNode* deleteNode(RBNode* root, int key) {
        RBNode* z = search(key);
        if (!z) return root;
        RBNode* y = z;
        RBNode* x = nullptr;
        Color yOrigColor = y->color;
        if (!z->left) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (!z->right) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minNode(z->right);
            yOrigColor = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x) x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOrigColor == BLACK) fixDelete(x);
        return root;
    }

    RBNode* searchRec(RBNode* node, int key) {
        if (!node || node->data.rollNo == key) return node;
        if (key < node->data.rollNo) return searchRec(node->left, key);
        return searchRec(node->right, key);
    }

    void inorderHelp(RBNode* node) {
        if (!node) return;
        inorderHelp(node->left);
        cout << node->data.rollNo << " " << node->data.name << " " << node->data.CGPA 
             << (node->color == RED ? " (R)\n" : " (B)\n");
        inorderHelp(node->right);
    }

public:
    RBTree() : root(nullptr), rotationCount(0) {}

    void insertStudent(Student s) {
        if (!root) {
            root = new RBNode(s);
            root->color = BLACK;
            return;
        }
        RBNode* temp = root;
        RBNode* parent = nullptr;
        while (temp) {
            parent = temp;
            if (s.rollNo < temp->data.rollNo) temp = temp->left;
            else if (s.rollNo > temp->data.rollNo) temp = temp->right;
            else return;
        }
        RBNode* newNode = new RBNode(s);
        newNode->parent = parent;
        if (s.rollNo < parent->data.rollNo) parent->left = newNode;
        else parent->right = newNode;
        fixInsert(newNode);
    }

    void deleteStudent(int roll) {
        root = deleteNode(root, roll);
    }

    RBNode* search(int key) {
        return searchRec(root, key);
    }

    void inorder() {
        inorderHelp(root);
    }

    int getRotationCount() {
        return rotationCount;
    }
};

int main() {
    RBTree rb;
    ifstream fin("students.txt");
    if (fin) {
        int roll; string name; float cgpa;
        while (fin >> roll >> name >> cgpa) {
            Student s{roll, name, cgpa};
            rb.insertStudent(s);
        }
        fin.close();
    }
    while (true) {
        cout << "\n1. Insert\n2. Delete\n3. Search\n4. Print\n5. Rotations\n6. Exit\nChoice: ";
        int ch; cin >> ch;
        if (ch == 1) {
            Student s; cout << "Roll: "; cin >> s.rollNo;
            cout << "Name: "; cin >> s.name;
            cout << "CGPA: "; cin >> s.CGPA;
            rb.insertStudent(s);
        } else if (ch == 2) {
            cout << "Enter roll to delete: ";
            int r; cin >> r;
            rb.deleteStudent(r);
        } else if (ch == 3) {
            cout << "Enter roll to search: ";
            int r; cin >> r;
            auto found = rb.search(r);
            if (!found) cout << "Not found\n"; 
            else cout << "Found: " << found->data.name << "\n";
        } else if (ch == 4) {
            rb.inorder();
        } else if (ch == 5) {
            cout << "Rotations: " << rb.getRotationCount() << "\n";
        } else break;
    }
    return 0;
}