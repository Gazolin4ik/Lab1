#pragma once
#include <string>
using namespace std;

void push_back(string* &arr, int &size, const string value);
void addArr(string* &arr, int &size, int &index, const string value);
void getAt(string* &arr, int &size, int &index);
void delArr(string* &arr, int &size, int &index);
void replaceArr(string* &arr, int &size, int &index,const string value);
void readArr(string* &arr, int &size);
void saveArray(ofstream& outFile, string* arr, int size);
void loadArray(ifstream& inFile, string*& arr, int& size);
