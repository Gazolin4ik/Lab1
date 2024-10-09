#pragma once
#include <string>
using namespace std;

struct QNode {
    string data;
    QNode* next;
    QNode* prev;
};
 
struct Queue {
    QNode* front;  
    QNode* rear;   
};

void initQueue(Queue& q);
void push(Queue& q, const string& value);
void pop(Queue& q);
void read_queue(Queue& q);
void saveQueue(ofstream& outFile, Queue q);
void loadQueue(ifstream& inFile, Queue& q);