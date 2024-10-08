#pragma once
#include <string>
using namespace std;

// structure node DLL
struct QNode {
    string data;
    QNode* next;
    QNode* prev;
};
 
// Structure for storage queue
struct Queue {
    QNode* front;  // Pointer to beginning queue
    QNode* rear;   // Pointer to end queue
};

void initQueue(Queue& q);
void push(Queue& q, const string& value);
void pop(Queue& q);
void read_queue(Queue& q);