// Name: Diya Goyal
// Roll no: 102215255
// Question: Extent the available function list for the following operations on a Splay tree: Split and Join.
// Acknowledgement: took help from GitHub Copilot 
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if(!root) return root;
    if(key < root->data) {
        if(!root->left) return root;
        if(key < root->left->data) {
            root->left->left = splay(root->left->left, key);
            root = rotateRight(root);
        } else if(key > root->left->data) {
            root->left->right = splay(root->left->right, key);
            if(root->left->right) root->left = rotateLeft(root->left);
        }
        return (root->left) ? rotateRight(root) : root;
    } else if(key > root->data) {
        if(!root->right) return root;
        if(key > root->right->data) {
            root->right->right = splay(root->right->right, key);
            root = rotateLeft(root);
        } else if(key < root->right->data) {
            root->right->left = splay(root->right->left, key);
            if(root->right->left) root->right = rotateRight(root->right);
        }
        return (root->right) ? rotateLeft(root) : root;
    }
    return root;
}

Node* joinTrees(Node* leftTree, Node* rightTree) {
    if(!leftTree) return rightTree;
    if(!rightTree) return leftTree;
    leftTree = splay(leftTree, 999999999);
    leftTree->right = rightTree;
    return leftTree;
}

pair<Node*,Node*> splitTree(Node* root, int key) {
    if(!root) return {nullptr, nullptr};
    root = splay(root, key);
    if(root->data <= key) {
        Node* rightPart = root->right;
        root->right = nullptr;
        return {root, rightPart};
    } else {
        Node* leftPart = root->left;
        root->left = nullptr;
        return {leftPart, root};
    }
}

void inorder(Node* root) {
    if(!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;

    auto insertBST = [&](int val) {
        if(!root) {
            root = new Node(val);
            return;
        }
        Node* cur = root;
        Node* prev = nullptr;
        while(cur) {
            prev = cur;
            if(val < cur->data) {
                cur = cur->left;
            } else if(val > cur->data) {
                cur = cur->right;
            } else {
                return; // no duplicates
            }
        }
        if(val < prev->data) prev->left = new Node(val);
        else prev->right = new Node(val);
    };

    insertBST(10);
    insertBST(20);
    insertBST(30);
    insertBST(40);
    insertBST(50);

    cout << "Original tree: ";
    inorder(root);
    cout << "\n";

    auto splitted = splitTree(root, 25);
    cout << "Left part: ";
    inorder(splitted.first);
    cout << "\n";

    cout << "Right part: ";
    inorder(splitted.second);
    cout << "\n";

    Node* joined = joinTrees(splitted.first, splitted.second);
    cout << "After join: ";
    inorder(joined);
    cout << "\n";
    return 0;
}