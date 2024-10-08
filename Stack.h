#pragma once
#include <string>
using namespace std;

// Structure node stack
struct SNode {
    string data;
    SNode* next;
};
 
// Stack based on SLL
struct Stack {
    SNode* top;  // Pointer on top stack
};

void initStack(Stack& s);
void Spush(Stack& s, const string& value);
void Spop(Stack& s);
void read_stack(Stack& s);
