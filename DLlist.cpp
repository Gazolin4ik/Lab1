#include <iostream>
#include <string>
using namespace std;
 
// Structure node DLL
struct Node {
    string data;
    Node* next;
    Node* prev;
};
 
// Adding element in head list
void push_front(Node*& head, Node*& tail, const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
 
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode; // If list empty, new element it also becomes tail
    }
 
    head = newNode;
}
 
// Adding element in tail list
void push_back(Node*& head, Node*& tail, const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;
 
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        head = newNode; // If list empty, new element it also becomes head
    }
 
    tail = newNode;
}
 
// Delete element from head list
void pop_front(Node*& head, Node*& tail) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot pop from front.");
    }
 
    Node* temp = head;
    head = head->next;
 
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // if list become empty, tail should also be nullptr
    }
 
    delete temp;
}
 
// Delete element from tail list
void pop_back(Node*& head, Node*& tail) {
    if (tail == nullptr) {
        throw runtime_error("List is empty. Cannot pop from back.");
    }
 
    Node* temp = tail;
    tail = tail->prev;
 
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; // if list become empty, head should also be nullptr
    }
 
    delete temp;
}
 
// Delete element by value
void delete_value(Node*& head, Node*& tail, const string& value) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot delete value.");
    }
 
    Node* current = head;
    while (current != nullptr && current->data != value) {
        current = current->next;
    }
 
    if (current == nullptr) {
        throw runtime_error("Value not found in the list.");
    }
 
    if (current == head) {
        pop_front(head, tail);
    } else if (current == tail) {
        pop_back(head, tail);
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}
 
// Read all list from head
void read_list_from_head(Node* head) {
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
 
// Read all list from tail
void read_list_from_tail(Node* tail) {
    if (tail == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
 
    Node* current = tail;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->prev;
    }
    cout << "null" << endl;
}
 
int main() {
    Node* head = nullptr;
    Node* tail = nullptr;
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
                    push_front(head, tail, value);
                } else if (option == "tail") {
                    push_back(head, tail, value);
                } else {
                    cout << "Invalid option." << endl;
                }
            } else if (command == "LDEL") {
                string option;
                cout << "Delete from (head/tail/value): ";
                cin >> option;
 
                if (option == "head") {
                    pop_front(head, tail);
                } else if (option == "tail") {
                    pop_back(head, tail);
                } else if (option == "value") {
                    string value;
                    cout << "Enter value to delete: ";
                    cin >> value;
                    delete_value(head, tail, value);
                } else {
                    cout << "Invalid option." << endl;
                }
            } else if (command == "LGET") {
                string option;
                cout << "Read from (head/tail): ";
                cin >> option;
 
                if (option == "head") {
                    read_list_from_head(head);
                } else if (option == "tail") {
                    read_list_from_tail(tail);
                } else {
                    cout << "Invalid option." << endl;
                }
            } else {
                cout << "Invalid command." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    return 0;
}