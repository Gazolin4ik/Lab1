#pragma once
using namespace std;

struct AVLNode;
int height(AVLNode* node);
int getBalance(AVLNode* node);
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
AVLNode* insert(AVLNode* node, int key);
AVLNode* minValueNode(AVLNode* node);
AVLNode* remove(AVLNode* root, int key);
bool search(AVLNode* root, int key);
void printAVLTree(string& result, AVLNode* tree, int depth = 0, string prefix = "");
void saveInOrder(ofstream& outFile, AVLNode* node);
void saveAVLTree(ofstream& outFile, AVLNode* root);
void loadAVLTree(ifstream& inFile, AVLNode*& root); 
