#include <iostream>
#include <stdexcept>  // for using exceptions
#include "AVL-Tree.h"
 
// Structure of the AVL tree node
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
 
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};
 
// Function to get the height of a node
int height(AVLNode* node) {
    return node ? node->height : 0;
}
 
// Calculate the balance factor of the node
int getBalance(AVLNode* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}
 
// Right rotation
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
 
    // Perform the rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
 
    return x;  // Return the new root
}
 
// Left rotation
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
 
    // Perform the rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
 
    return y;  // Return the new root
}
 
// Insert a node into the AVL tree
AVLNode* insert(AVLNode* node, int key) {
    // 1. Perform normal BST insertion
    if (!node) return new AVLNode(key);
 
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        throw invalid_argument("Duplicate keys are not allowed in AVL tree.");
    }
 
    // 2. Update the height of the current node
    node->height = 1 + max(height(node->left), height(node->right));
 
    // 3. Get the balance factor of this node to check if it is balanced
    int balance = getBalance(node);
 
    // 4. Balance the tree if it becomes unbalanced
 
    // Left Left case
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }
 
    // Right Right case
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
 
    // Left Right case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
 
    // Right Left case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
 
    return node;  // Return the unchanged node
}
 
// Find the node with the smallest key (used in deletion)
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}
 
// Remove a node from the AVL tree
AVLNode* remove(AVLNode* root, int key) {
    // 1. Perform standard BST deletion
    if (!root) throw runtime_error("Key not found in AVL tree.");
 
    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        // Node with one or no child
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
 
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
 
            delete temp;
        } else {
            // Node with two children
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
    }
 
    if (!root) return root;
 
    // 2. Update the height of the current node
    root->height = 1 + max(height(root->left), height(root->right));
 
    // 3. Get the balance factor of the node
    int balance = getBalance(root);
 
    // 4. Balance the tree if it becomes unbalanced
 
    // Left Left case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }
 
    // Left Right case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
 
    // Right Right case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }
 
    // Right Left case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
 
    return root;
}
 
// Search for an element in the AVL tree
bool search(AVLNode* root, int key) {
    if (!root) return false;
    if (key == root->key) return true;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}
 
// Inorder traversal (for printing the AVL tree in sorted order)
void inorder(AVLNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
 
/*int main() {
    AVLNode* root = nullptr;
    string command;
 
    while (true) {
        try {
            cout << "Enter command (TINSERT, TDEL, TGET, exit): ";
            cin >> command;
 
            if (command == "exit") {
                break;
            } else if (command == "TINSERT") {
                cout << "Enter key: ";
                int key;
                cin >> key;
                if (cin.fail()) {  // If input is not an integer
                    cin.clear();  // Clear the fail state
                    cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
                    throw invalid_argument("Invalid input. Key must be an integer.");
                }
                root = insert(root, key);
            } else if (command == "TDEL") {
                cout << "Enter key to delete: ";
                int key;
                cin >> key;
                if (cin.fail()) {  // If input is not an integer
                    cin.clear();  // Clear the fail state
                    cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
                    throw invalid_argument("Invalid input. Key must be an integer.");
                }
                root = remove(root, key);
            } else if (command == "TGET") {
                cout << "Search key (enter -1 to print all): ";
                int key;
                cin >> key;
                if (cin.fail()) {  // If input is not an integer
                    cin.clear();  // Clear the fail state
                    cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
                    throw invalid_argument("Invalid input. Key must be an integer.");
                }
                if (key == -1) {
                    inorder(root);
                    cout << endl;
                } else {
                    if (search(root, key)) {
                        cout << "Key " << key << " found in the tree." << endl;
                    } else {
                        cout << "Key " << key << " not found." << endl;
                    }
                }
            } else {
                cout << "Invalid command." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    return 0;
}*/