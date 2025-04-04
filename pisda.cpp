#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    
    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

    Node* insertHelper(Node* root, Node* node) {
        if (root == nullptr) {
            return node;
        }
        if (node->data < root->data) {
            root->left = insertHelper(root->left, node);
        } else {
            root->right = insertHelper(root->right, node);
        }
        return root;
    }

    void displayHelper(Node* root) {
        if (root != nullptr) {
            displayHelper(root->left);
            cout << root->data << " ";
            displayHelper(root->right);
        }
    }

    bool searchHelper(Node* root, int data) {
        if (root == nullptr) return false;
        if (root->data == data) return true;
        if (data < root->data) return searchHelper(root->left, data);
        return searchHelper(root->right, data);
    }

    Node* removeHelper(Node* root, int data) {
        if (root == nullptr) {
            return root;
        } else if (data < root->data) {
            root->left = removeHelper(root->left, data);
        } else if (data > root->data) {
            root->right = removeHelper(root->right, data);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            } else if (root->right != nullptr) {
                root->data = successor(root);
                root->right = removeHelper(root->right, root->data);
            } else {
                root->data = predecessor(root);
                root->left = removeHelper(root->left, root->data);
            }
        }
        return root;
    }

    int successor(Node* root) {
        root = root->right;
        while (root->left != nullptr) {
            root = root->left;
        }
        return root->data;
    }

    int predecessor(Node* root) {
        root = root->left;
        while (root->right != nullptr) {
            root = root->right;
        }
        return root->data;
    }
    
public:
    BinaryTree() { root = nullptr; }

    void insertNode(int data) {
        root = insertHelper(root, new Node(data));
    }

    void display() {
        displayHelper(root);
        cout << endl;
    }

    bool search(int data) {
        return searchHelper(root, data);
    }

    void remove(int data) {
        if (search(data)) {
            root = removeHelper(root, data);
        } else {
            cout << "Couldn't find the data." << endl;
        }
    }
};

int main() {
    BinaryTree tree;
    tree.insertNode(5);
    tree.insertNode(1);
    tree.insertNode(9);
    tree.insertNode(2);
    tree.insertNode(7);
    tree.insertNode(3);
    tree.insertNode(6);
    tree.insertNode(4);
    tree.insertNode(8);

    tree.remove(4);
    tree.display();
    cout << tree.search(4) << endl;

    return 0;
}
