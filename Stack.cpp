#include <iostream>
#include <string>
using namespace std;
 
// Structure node stack
struct Node {
    string data;
    Node* next;
};
 
// Stack based on SLL
struct Stack {
    Node* top;  // Pointer on top stack
};
 
// Initialization empty stack
void initStack(Stack& s) {
    s.top = nullptr;
}
 
// Adding element on top stack
void push(Stack& s, const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = s.top;
    s.top = newNode;
}
 
// Delete element from top stack
void pop(Stack& s) {
    if (s.top == nullptr) {
        throw runtime_error("Stack is empty. Cannot pop.");
    }
 
    Node* temp = s.top;
    s.top = s.top->next;
    delete temp;
}
 
// Read all stack
void read_stack(Stack& s) {
    if (s.top == nullptr) {
        cout << "Stack is empty." << endl;
        return;
    }
 
    Node* current = s.top;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "null" << endl;
}
 
int main() {
    Stack s;
    initStack(s);  // Initialization empty stack
    string command;
 
    while (true) {
        try {
            cout << "Enter command (SPUSH, SPOP, SGET, exit): ";
            cin >> command;
 
            if (command == "exit") {
                break;
            } else if (command == "SPUSH") {
                string value;
                cout << "Enter value to push: ";
                cin >> value;
                push(s, value);
            } else if (command == "SPOP") {
                pop(s);
            } else if (command == "SGET") {
                read_stack(s);
            } else {
                cout << "Invalid command." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    return 0;
}