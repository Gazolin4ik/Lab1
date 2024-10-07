#include <iostream>
#include <string>
using namespace std;

// structure node DLL
struct Node {
    string data;
    Node* next;
    Node* prev;
};
 
// Structure for storage queue
struct Queue {
    Node* front;  // Pointer to beginning queue
    Node* rear;   // Pointer to end queue
};
 
// Initialization empty queue
void initQueue(Queue& q) {
    q.front = nullptr;
    q.rear = nullptr;
}
 
// Adding element in end queue
void push(Queue& q, const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = q.rear;
 
    if (q.rear == nullptr) {  // If queue empty
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}
 
// Delete element from begin queue
void pop(Queue& q) {
    if (q.front == nullptr) {
        throw runtime_error("Queue is empty. Cannot pop.");
    }
 
    Node* temp = q.front;
    q.front = q.front->next;
 
    if (q.front != nullptr) {
        q.front->prev = nullptr;
    } else {
        q.rear = nullptr;  // If queue has become empty
    }
 
    delete temp;
}
 
// Read all queue from head
void read_queue(Queue& q) {
    if (q.front == nullptr) {
        cout << "Queue is empty." << endl;
        return;
    }
 
    Node* current = q.front;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "null" << endl;
}
 
int main() {
    Queue q;
    initQueue(q);  // Initialization empty queue
    string command;
 
    while (true) {
        try {
            cout << "Enter command (QPUSH, QPOP, QGET, exit): ";
            cin >> command;
 
            if (command == "exit") {
                break;
            } else if (command == "QPUSH") {
                string value;
                cout << "Enter value to push: ";
                cin >> value;
                push(q, value);
            } else if (command == "QPOP") {
                pop(q);
            } else if (command == "QGET") {
                read_queue(q);
            } else {
                cout << "Invalid command." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    return 0;
}