#include <iostream>
#include <stdexcept> 
#include "Arr.h"
 
// add end array
void push_back(string* &arr, int &size, const string value) {
    string *newArr = new string[size + 1];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    newArr[size] = value;
    delete[] arr;
    arr = newArr;
    size++;
}
 
// add index array
void addArr(string* &arr, int &size, int &index, const string value) {
    if (index < 0 || index >= size) {
        throw out_of_range("Invalid index for adding value.");
    }
    string *newArr = new string[size + 1];
    for (int i = 0; i < index; ++i) {
        newArr[i] = arr[i];
    }
    newArr[index] = value;
    for (int i = index; i < size; ++i) {
        newArr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size++;
}
 
// get element by index
void getAt(string* &arr, int &size, int &index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Invalid index for getting value.");
    }
    cout << arr[index] << endl;
}
 
// delete element by index
void delArr(string* &arr, int &size, int &index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Invalid index for deleting value.");
    }
    
    string* newArr = new string[size - 1];
    
    for (int i = 0; i < index; ++i) {
        newArr[i] = arr[i];
    }
    
    for (int i = index + 1; i < size; ++i) {
        newArr[i - 1] = arr[i];
    }
    
    delete[] arr;
    arr = newArr;
    size--;
}
 
// replace element by index
void replaceArr(string* &arr, int &size, int &index,const string value) {
    if (index < 0 || index >= size) {
        throw out_of_range("Invalid index for replacing value.");
    }
    arr[index] = value;
}
 
// read array
void readArr(string* &arr, int &size) {
    if (size == 0) {
        throw runtime_error("Array is empty.");
    }
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
 
/*int main() {
    int size = 0;
    string *arr = nullptr;
 
    string command;
    while (true) {
        try {
            cout << "Enter command (MPUSH, MDEL, MGET, exit): ";
            getline(cin, command);
 
            if (command == "exit") {
                break;
            }
 
            if (command == "MPUSH") {
                cout << "Enter index (or press Enter to add at the end): ";
                string indexStr;
                getline(cin, indexStr);
 
                if (!indexStr.empty()) {
                    int index = stoi(indexStr);
                    if (index >= 0 && index < size) {
                        cout << "Replace existing value? [y/n]: ";
                        string response;
                        getline(cin, response);
                        if (response == "y") {
                            cout << "Enter new value: ";
                            string value;
                            getline(cin, value);
                            replaceArr(arr, size, index, value);
                        } else {
                            cout << "Enter new value: ";
                            string value;
                            getline(cin, value);
                            addArr(arr, size, index, value);
                        }
                    } else {
                        throw out_of_range("Invalid index for MPUSH.");
                    }
                } else {
                    cout << "Enter value to push at the end: ";
                    string value;
                    getline(cin, value);
                    push_back(arr, size, value);
                }
            } else if (command == "MDEL") {
                if (size == 0) {
                    throw runtime_error("Array is empty, nothing to delete.");
                } else {
                    cout << "Enter index to delete: ";
                    string indexStr;
                    getline(cin, indexStr);
                    if (!indexStr.empty()) {
                        int index = stoi(indexStr);
                        delArr(arr, size, index);
                    } else {
                        throw invalid_argument("Invalid input for MDEL.");
                    }
                }
            } else if (command == "MGET") {
                if (size == 0) {
                    throw runtime_error("Array is empty.");
                } else {
                    cout << "Enter index (or press Enter to get all): ";
                    string indexStr;
                    getline(cin, indexStr);
 
                    if (!indexStr.empty()) {
                        int index = stoi(indexStr);
                        getAt(arr, size, index);
                    } else {
                        cout << "Array: ";
                        readArr(arr, size);
                        cout << "Array size: " << size << endl;
                    }
                }
            } else {
                throw invalid_argument("Unknown command. Try again.");
            }
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 
    delete[] arr;
    return 0;
}*/