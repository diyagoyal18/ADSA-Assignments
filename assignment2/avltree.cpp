//avl tree
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};
int getHeight(Node* node) {
    return node ? node->height : 0;
}
int getBalance(Node* node){
    return node ? getHeight(node->left)- getHeight(node->right) :0;
}
Node* rightRotate(Node* y) { //balance factor > 1
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}
Node* leftRotate(Node* x) { //balance factor < -1
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

Node* insertAVL(Node* node, int key){
    if(!node) return new Node(key);

    if(key<node->key) node->left= insertAVL(node->left,key);
    else if(key>node->key) node->right= insertAVL(node->right,key);
    else return node; 
    node->height= 1+max(getHeight(node->left),getHeight(node->right));
    int balance= getBalance(node);

    //left left case
    if(balance>1 && key<node->left->key)    return rightRotate(node);

    //right right case     
    if(balance<-1 && key>node->right->key)   return leftRotate(node);

    //left right case
    if(balance>1 && key>node->left->key){
        node->left= leftRotate(node->left);
        return rightRotate(node);
    }   

    //right left case
    if(balance<-1 && key<node->right->key){
        node->right= rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
Node* minValue(Node* node){
    Node* curr= node;
    while(curr->left)
        curr=curr->left;
    return curr;
}
Node* deleteAVL(Node* root, int key){
    if(!root) return root;
    if(key<root->key) root->left= deleteAVL(root->left,key);
    else if(key>root->key) root->right= deleteAVL(root->right,key);
    else{
        if(!root->left || !root->right){
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        //node with two children
        Node* temp = minValue(root->right);
        root->key= temp->key;
        root->right= deleteAVL(root->right,temp->key);
    }
    //update height
    root->height= 1+ max(getHeight(root->left), getHeight(root->right));

    int balance= getBalance(root);
    if(balance>1 && getBalance(root->left)>=0) return rightRotate(root);
    if(balance>1 && getBalance(root->left)<0){
        root->left= leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1 && getBalance(root->right)<=0) return leftRotate(root);
    if(balance<-1 && getBalance(root->right)>0){
        root->right= rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void preorder(Node* root) {
    if (!root) return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}
void inOrder(Node *root) { 
    if (root != nullptr) { 
        inOrder(root->left);     // Visit left subtree
        cout << root->key << " ";  // Visit root
        inOrder(root->right);    // Visit right subtree
    } 
} 
void postOrder(Node *root) { 
    if (root != nullptr) { 
        postOrder(root->left);    // Visit left subtree
        postOrder(root->right);   // Visit right subtree
        cout << root->key << " ";  // Visit root
    } 
}
int main() {
    Node* root = nullptr;
    root = insertAVL(root, 10);
    root = insertAVL(root, 20);
    root = insertAVL(root, 30);
    root = insertAVL(root, 40);
    root = insertAVL(root, 50);
    root = insertAVL(root, 25);
    cout << "Preorder traversal of the constructed AVL tree is \n";
    preorder(root);
    cout<< "\n inOrder traversal of the constructed AVL tree is \n";
    inOrder(root);
    cout<<"\n postOrder traversal of the constructed AVL tree is \n";
    postOrder(root);
    deleteAVL(root, 30);
    cout << "\nPreorder traversal after deletion of 30 \n";
    preorder(root);
    return 0;
}   