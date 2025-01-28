// Name: Diya Goyal
// Roll no: 102215255
// Question: Q4: Write a program to convert a binary search tree into a min- heap.
// Acknowledgement: took help from GitHub Copilot
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
class BST {
private:
    Node* root;
    
    Node* insertNode(Node* node, int val) {
        if(!node) return new Node(val);
        if(val < node->data) node->left = insertNode(node->left, val);
        else if(val > node->data) node->right = insertNode(node->right, val);
        return node;
    } 
    void inorderCollect(Node* node, vector<int> &vals) {
        if(!node) return;
        inorderCollect(node->left, vals);
        vals.push_back(node->data);
        inorderCollect(node->right, vals);
    }
    void levelOrderAssign(Node* node, vector<int> &vals, int &idx) {
        if(!node) return;
        queue<Node*>q;
        q.push(node);
        while(!q.empty()) {
            Node* curr = q.front();
            q.pop();
            curr->data = vals[idx++]; // assign next smallest
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
    }
    
public:
    BST(): root(nullptr) {}
    
    void insertVal(int val) {
        root = insertNode(root, val);
    }
    // Convert BST to Min Heap
    void convertToMinHeap() {
        vector<int> vals;
        inorderCollect(root, vals);     // gather sorted data
        int idx = 0;
        levelOrderAssign(root, vals, idx);
    }
    // Print level-order for checking
    void printLevelOrder() {
        if(!root) return;
        queue<Node*>q;
        q.push(root);
        while(!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->data << " ";
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }
        cout << endl;
    }
};
int main() {
    BST tree;
    tree.insertVal(50);
    tree.insertVal(30);
    tree.insertVal(70);
    tree.insertVal(20);
    tree.insertVal(40);
    tree.insertVal(60);
    tree.insertVal(80);
    cout << "BST level-order before conversion: ";
    tree.printLevelOrder();
    tree.convertToMinHeap();
    cout << "Min-Heap level-order after conversion: ";
    tree.printLevelOrder();
    return 0;
}