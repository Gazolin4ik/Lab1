#include <iostream>
#include <fstream>
#include "DLlist.h"
 
// Structure node DLL
struct DLNode {
    string data;
    DLNode* next;
    DLNode* prev;
};
 
// Adding element in head list
void push_front(DLNode*& head, DLNode*& tail, const string& value) {
    DLNode* newNode = new DLNode;
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
void push_back(DLNode*& head, DLNode*& tail, const string& value) {
    DLNode* newNode = new DLNode;
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
void pop_front(DLNode*& head, DLNode*& tail) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot pop from front.");
    }
 
    DLNode* temp = head;
    head = head->next;
 
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // if list become empty, tail should also be nullptr
    }
 
    delete temp;
}
 
// Delete element from tail list
void pop_back(DLNode*& head, DLNode*& tail) {
    if (tail == nullptr) {
        throw runtime_error("List is empty. Cannot pop from back.");
    }
 
    DLNode* temp = tail;
    tail = tail->prev;
 
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; // if list become empty, head should also be nullptr
    }
 
    delete temp;
}
 
// Delete element by value
void delete_value(DLNode*& head, DLNode*& tail, const string& value) {
    if (head == nullptr) {
        throw runtime_error("List is empty. Cannot delete value.");
    }
 
    DLNode* current = head;
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
void read_list_from_head(DLNode* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
 
    DLNode* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "null" << endl;
}
 
// Read all list from tail
void read_list_from_tail(DLNode* tail) {
    if (tail == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
 
    DLNode* current = tail;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->prev;
    }
    cout << "null" << endl;
}

void saveDoublyLinkedList(ofstream& outFile, DLNode* head) {
    outFile << "DoublyLinkedList" << endl;
    DLNode* current = head;
    while (current != nullptr) {
        outFile << current->data << " ";
        current = current->next;
    }
    outFile << endl;
}
 
void loadDoublyLinkedList(ifstream& inFile, DLNode*& head, DLNode*& tail) {
    string value;
    while (inFile >> value && value != "Queue") {  // Останавливаемся, когда встречаем следующее ключевое слово
        push_back(head, tail, value);  // Добавляем элемент в конец двусвязного списка
    }
}
 
/*int main() {
    DLNode* head = nullptr;
    DLNode* tail = nullptr;
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
}*/