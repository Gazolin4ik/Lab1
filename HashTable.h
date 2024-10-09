#pragma once
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

struct HashNode {
    string key;
    string value;
    HashNode* next;
};

struct HashTable {
    HashNode* table[TABLE_SIZE]; 

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
void saveHashTable(ofstream& outFile, HashTable& ht);
void loadHashTable(ifstream& inFile, HashTable& ht);