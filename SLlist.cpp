#include <iostream>
#include <string>
using namespace std;
 
// Structure node singly linked list
struct Node {
    string data;
    Node* next;
};
 
// Adding element in head list
void push_front(Node*& head, const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}
 
// Adding element in tail list
void push_back(Node*& head, const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
 
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}
 
// Delete element from head list
void pop_front(Node*& head) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot pop from front.");
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}
 
// Delete element from tail list
void pop_back(Node*& head) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot pop from back.");
    }
 
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
 
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}
 
// Delete element by value
void delete_value(Node*& head, const string& value) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot delete value.");
    }
 
    // If value in first node
    if (head->data == value) {
        pop_front(head);
        return;
    }
 
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }
 
    if (current->next == nullptr) {
        throw runtime_error("Value not found in the list.");
    }
 
    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
}
 
// Read all list
void read_list(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
 
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "null" << endl;
}
 
int main() {
    Node* head = nullptr;
    string command;
 
    while (true) {
        try {
            cout << "Enter command (LPUSH, LDEL, LGET, exit): ";
            cin >> command;
 
            if (command == "exit") {
                break;
            } else if (command == "LPUSH") {
                string value, option;
                cout << "Enter value to push: ";
                cin >> value;
                cout << "Push to (head/tail): ";
                cin >> option;
 
                if (option == "head") {
                    push_front(head, value);
                } else if (option == "tail") {
                    push_back(head, value);
                } else {
                    cout << "Invalid option." << endl;
                }
            } else if (command == "LDEL") {
                string option;
                cout << "Delete from (head/tail/value): ";
                cin >> option;
 
                if (option == "head") {
                    pop_front(head);
                } else if (option == "tail") {
                    pop_back(head);
                } else if (option == "value") {
                    string value;
                    cout << "Enter value to delete: ";
                    cin >> value;
                    delete_value(head, value);
                } else {
                    cout << "Invalid option." << endl;
                }
            } else if (command == "LGET") {
                read_list(head);
            } else {
                cout << "Invalid command." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    return 0;
}