#ifndef AVLTREE_H
#define AVLTREE_H

#include "item.h"


class AVLNode {
public:
    Item* data;
    AVLNode* left;
    AVLNode* right;
    int height;
    bool equiped;

    AVLNode(Item* d) : data(d), left(nullptr), right(nullptr), height(0), equiped(false) {}
};

class AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    bool isEmpty() {
        if (root)
            return false;
        return true;
    }

    int height(AVLNode* node) {
        if (node) {
            return node->height;
        }
        return -1;
    }

    AVLNode* leftRotation(AVLNode* n1) { //LL 
        AVLNode* n2 = n1->right;
        if (!n2) {
            return n1;
        }
        n1->right = n2->left;
        n2->left = n1;
        n1->height = max(height(n1->left), height(n1->right)) + 1;
        n2->height = max(height(n2->left), height(n2->right)) + 1;
        return n2;
    }

    AVLNode* rightRotation(AVLNode* n1) { //RR

        AVLNode* n2 = n1->left;
        if (!n2) {
            return n1;
        }
        n1->left = n2->right;
        n2->right = n1;
        n1->height = max(height(n1->left), height(n1->right)) + 1;
        n2->height = max(height(n2->left), height(n2->right)) + 1;
        return n2;
    }

    int balanceFactor(AVLNode* n) {
        if (n) {
            return height(n->left) - height(n->right);
        }
        return 0;
    }

    AVLNode* balancingTree(Item* value, AVLNode* node) {
        if (balanceFactor(node) > 1) {
            if (value < node->left->data) {
                return rightRotation(node);
            }
            else if (value > node->left->data) { //RL
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }
        else if (balanceFactor(node) < -1) {
            if (value > node->right->data) {//LL
                return leftRotation(node);
            }
            else if (value < node->right->data) {//LR
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
        }
        return node;
    }

    AVLNode* insert(Item* value, AVLNode* node) {
        if (!node) {
            return new AVLNode(value);
        }
        else if (value->name == node->data->name) {
            value->value += node->data->value/2;
        }
        else if (value < node->data) {
            node->left = insert(value, node->left);
        }
        else if (value > node->data) {
            node->right = insert(value, node->right);
        }


        node->height = max(height(node->left), height(node->right)) + 1;

        if (balanceFactor(node) > 1) {
            if (value < node->left->data) {
                return rightRotation(node);
            }
            else if (value > node->left->data) { //RL
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }
        else if (balanceFactor(node) < -1) {
            if (value > node->right->data) {//LL
                return leftRotation(node);
            }
            else if (value < node->right->data) {//LR
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
        }
        return node;
    }

    void insert(Item* value) {
        root = insert(value, root);
    }

    AVLNode* remove(Item* value, AVLNode* node) {
        if (!node) {
            return node;
        }
        if (value < node->data) {
            node->left = remove(value, node->left);
        }
        else if (value > node->data) {
            node->right = remove(value, node->right);
        }
        else {
            //one or no child
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            //2 children
            else {
                AVLNode* temp = node->left;
                while (temp->right)
                    temp = temp->right;

                node->data = temp->data;
                node->left = remove(temp->data, node->left);
            }
        }
        //balancing
        if (!node) {
            return node;
        }
        node->height = max(height(node->left), height(node->right)) + 1;

        return balancingTree(value, node);
    }

    void remove(Item* value) {
        if (root) {
            root = remove(value, root);
        }
    }

    AVLNode* search(AVLNode* node, Item*& data) {
        if (!node) {
            return nullptr;
        }
        else {
            if (data < node->data)
                return search(node->left, data);
            else if (data > node->data)
                return search(node->right, data);
            else if (data == node->data)
                return node;
        }
    }

    AVLNode* search(Item* data) {
        return search(root, data);
    }

    void inorderTraversal( string& str, AVLNode* node) {
        if (!node) {
            return;
        }

        inorderTraversal(str, node->left);
        str += node->data->name + "\n";
        inorderTraversal(str, node->right);
    }


    void inorderTraversal(string& str) {
        inorderTraversal(str, root);
    }
};


#endif // AVLTREE_H