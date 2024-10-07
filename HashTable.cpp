#include <iostream>
#include <string>
using namespace std;
 
// Size hash-table (number of buckets)
const int TABLE_SIZE = 10;
 
// Structure node for chains in hash-table
struct HashNode {
    string key;
    string value;
    HashNode* next;
};
 
// Hash-table
struct HashTable {
    HashNode* table[TABLE_SIZE]; // Array pointers on chains
 
    // Initialization empty hash-table
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
};
 
// Simple hash-function for string
int hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % TABLE_SIZE;
}
 
// Adding element (key-value) in hash-table
void hset(HashTable& ht, const string& key, const string& value) {
    int index = hashFunction(key);
    HashNode* newNode = new HashNode{key, value, nullptr};
 
    // If bucket empty, add node
    if (ht.table[index] == nullptr) {
        ht.table[index] = newNode;
    } else {
        // If bucket not empty, find existing key or add in end chain
        HashNode* current = ht.table[index];
        while (current != nullptr) {
            if (current->key == key) {
                // If key already exists, update value
                current->value = value;
                delete newNode; // Delete created node, he not needed
                return;
            }
            if (current->next == nullptr) {
                current->next = newNode;
                return;
            }
            current = current->next;
        }
    }
}
 
// Get value by key
string hget_by_key(HashTable& ht, const string& key) {
    int index = hashFunction(key);
    HashNode* current = ht.table[index];
 
    // Iteretion by chain, find key
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
 
    throw runtime_error("Key not found in hash table.");
}
 
// Get all value in hash-table
void hget_all(HashTable& ht) {
    bool isEmpty = true;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = ht.table[i];
        if (current != nullptr) {
            isEmpty = false;
            cout << "Bucket " << i << ": ";
            while (current != nullptr) {
                cout << "[" << current->key << ": " << current->value << "] ";
                current = current->next;
            }
            cout << endl;
        }
    }
    if (isEmpty) {
        cout << "Hash table is empty." << endl;
    }
}
 
// Delete element by key
void hdel(HashTable& ht, const string& key) {
    int index = hashFunction(key);
    HashNode* current = ht.table[index];
    HashNode* prev = nullptr;
 
    // Iterated by chain, find and delete node with given key
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                ht.table[index] = current->next; // Delete head chain
            } else {
                prev->next = current->next; // Delete node in chain
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
 
    throw runtime_error("Key not found in hash table.");
}
 
// Read all hash-table
void printHashTable(const HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        cout << "Bucket " << i << ": ";
        HashNode* current = ht.table[i];
        while (current != nullptr) {
            cout << "[" << current->key << ": " << current->value << "] ";
            current = current->next;
        }
        cout << endl;
    }
}
 
int main() {
    HashTable ht;  // Created hash-table
    string command;
 
    while (true) {
        try {
            cout << "Enter command (HSET, HGET, HDEL, exit): ";
            cin >> command;
 
            if (command == "exit") {
                break;
            } else if (command == "HSET") {
                string key, value;
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                hset(ht, key, value);
            } else if (command == "HGET") {
                string option;
                cout << "Get (all/key): ";
                cin >> option;
                if (option == "key") {
                    string key;
                    cout << "Enter key: ";
                    cin >> key;
                    cout << "Value: " << hget_by_key(ht, key) << endl;
                } else if (option == "all") {
                    hget_all(ht);
                } else {
                    cout << "Invalid option." << endl;
                }
            } else if (command == "HDEL") {
                string key;
                cout << "Enter key: ";
                cin >> key;
                hdel(ht, key);
            } else {
                cout << "Invalid command." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    return 0;
}