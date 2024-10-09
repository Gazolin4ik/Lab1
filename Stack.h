#pragma once
#include <string>
using namespace std;

struct SNode {
    string data;
    SNode* next;
};
 
struct Stack {
    SNode* top;  
};

void initStack(Stack& s);
void Spush(Stack& s, const string& value);
void Spop(Stack& s);
void read_stack(Stack& s);
void saveStack(ofstream& outFile, Stack s);
void loadStack(ifstream& inFile, Stack& s);
