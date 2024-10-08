#pragma once
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

int hashFunction(const string& key);
void hset(HashTable& ht, const string& key, const string& value);
string hget_by_key(HashTable& ht, const string& key);
void hget_all(HashTable& ht);
void hdel(HashTable& ht, const string& key);
void printHashTable(const HashTable& ht);