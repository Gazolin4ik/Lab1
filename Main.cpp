#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>  // for exception handling
using namespace std;
 
// Включаем заголовочные файлы всех структур данных
#include "Arr.h"       // Реализация массива
#include "SLlist.h" // Реализация односвязного списка
#include "DLlist.h" // Реализация двусвязного списка
#include "Queue.h"       // Реализация очереди
#include "Stack.h"       // Реализация стека
#include "HashTable.h"  // Реализация хэш-таблицы
#include "AVL-Tree.h"    // Реализация AVL-дерева
 
void saveToFile(const string& filename) {
    // Здесь будет реализована запись всех данных в файл
    cout << "Data saved to file: " << filename << endl;
}
 
void loadFromFile(const string& filename) {
    // Здесь будет реализована загрузка данных из файла
    cout << "Data loaded from file: " << filename << endl;
}
 
// g++ Main.cpp Arr.cpp AVL-Tree.cpp DLlist.cpp HashTable.cpp Queue.cpp SLlist.cpp Stack.cpp -o Main

int main() {
    string command, filename = "data.txt";
    loadFromFile(filename);  // Загружаем данные из файла

    int size = 0;
    string *arr = nullptr;

    DLNode* head = nullptr;
    DLNode* tail = nullptr;

    SLNode* slhead = nullptr;

    Queue q;
    initQueue(q);  // Initialization empty queue

    Stack s;
    initStack(s);  // Initialization empty stack

    HashTable ht;  // Created hash-table
    AVLNode* root = nullptr;
 
    while (true) {
        try {
            cout << "Enter command (MPUSH, LDEL, QPOP, etc. or PRINT, exit): ";
            getline(cin, command);
 
            // Массив (M)
            if (command == "MPUSH") {
                try {
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
                } catch (const exception& e) {
                    cerr << "Error during MPUSH: " << e.what() << endl;
                }
                 
            } else if (command == "MDEL") {
                try {
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
                } catch (const exception& e) {
                    cerr << "Error during MDEL: " << e.what() << endl;
                }
            } else if (command == "MGET") {
                try {
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
                } catch (const exception& e) {
                    cerr << "Error during MGET: " << e.what() << endl;
                }
            }
 
            // Односвязный список (SL)
            else if (command == "SLPUSH") {
                try {
                    string value, option;
                    cout << "Enter value to push: ";
                    cin >> value;
                    cout << "Push to (head/tail): ";
                    cin >> option;
 
                    if (option == "head") {
                        push_front(slhead, value);
                    } else if (option == "tail") {
                        push_back(slhead, value);
                    } else {
                        throw invalid_argument("Unknown option.");
                    }
                } catch (const exception& e) {
                    cerr << "Error during LPUSH: " << e.what() << endl;
                }
            } else if (command == "SLDEL") {
                try {
                    string option;
                    cout << "Delete from (head/tail/value): ";
                    cin >> option;
 
                    if (option == "head") {
                        pop_front(slhead);
                    } else if (option == "tail") {
                        pop_back(slhead);
                    } else if (option == "value") {
                        string value;
                        cout << "Enter value to delete: ";
                        cin >> value;
                        delete_value(slhead, value);
                    } else {
                        throw invalid_argument("Unknown option.");
                    }
                } catch (const exception& e) {
                    cerr << "Error during SLDEL: " << e.what() << endl;
                }
            } else if (command == "SLGET") {
                try {
                    read_list(slhead);
                } catch (const exception& e) {
                    cerr << "Error during SLGET: " << e.what() << endl;
                }
            }

            // Односвязный список (DL)
            else if (command == "DLPUSH") {
                try {
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
                        throw invalid_argument("Unknown option.");
                    }
                } catch (const exception& e) {
                    cerr << "Error during DLPUSH: " << e.what() << endl;
                }
            } else if (command == "DLDEL") {
                try {
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
                        throw invalid_argument("Unknown option.");
                    }
                } catch (const exception& e) {
                    cerr << "Error during DLDEL: " << e.what() << endl;
                }
            } else if (command == "DLGET") {
                try {
                    string option;
                    cout << "Read from (head/tail): ";
                    cin >> option;
 
                    if (option == "head") {
                        read_list_from_head(head);
                    } else if (option == "tail") {
                        read_list_from_tail(tail);
                    } else {
                        throw invalid_argument("Unknown option.");
                    }
                } catch (const exception& e) {
                    cerr << "Error during DLGET: " << e.what() << endl;
                }
            }
 
            // Очередь (Q)
            else if (command == "QPUSH") {
                try {
                    string value;
                    cout << "Enter value to push: ";
                    cin >> value;
                    push(q, value);
                } catch (const exception& e) {
                    cerr << "Error during QPUSH: " << e.what() << endl;
                }
            } else if (command == "QPOP") {
                try {
                    pop(q);
                } catch (const exception& e) {
                    cerr << "Error during QPOP: " << e.what() << endl;
                }
            } else if (command == "QGET") {
                try {
                    read_queue(q);
                } catch (const exception& e) {
                    cerr << "Error during QGET: " << e.what() << endl;
                }
            }
 
            // Стек (S)
            else if (command == "SPUSH") {
                try {
                    string value;
                    cout << "Enter value to push: ";
                    cin >> value;
                    Spush(s, value);
                } catch (const exception& e) {
                    cerr << "Error during SPUSH: " << e.what() << endl;
                }
            } else if (command == "SPOP") {
                try {
                    Spop(s);
                } catch (const exception& e) {
                    cerr << "Error during SPOP: " << e.what() << endl;
                }
            } else if (command == "SGET") {
                try {
                    read_stack(s);
                } catch (const exception& e) {
                    cerr << "Error during SGET: " << e.what() << endl;
                }
            }
 
            // Хэш-таблица (H)
            else if (command == "HSET") {
                try {
                    string key, value;
                    cout << "Enter key: ";
                    cin >> key;
                    cout << "Enter value: ";
                    cin >> value;
                    hset(ht, key, value);
                } catch (const exception& e) {
                    cerr << "Error during HSET: " << e.what() << endl;
                }
            } else if (command == "HDEL") {
                try {
                    string key;
                    cout << "Enter key: ";
                    cin >> key;
                    hdel(ht, key);
                } catch (const exception& e) {
                    cerr << "Error during HDEL: " << e.what() << endl;
                }
            } else if (command == "HGET") {
                try {
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
                        throw invalid_argument("Unknown option.");
                    }
                } catch (const exception& e) {
                    cerr << "Error during HGET: " << e.what() << endl;
                }
            }
 
            // AVL-дерево (T)
            else if (command == "TINSERT") {
                try {
                    cout << "Enter key: ";
                    int key;
                    cin >> key;
                    if (cin.fail()) {  // If input is not an integer
                        cin.clear();  // Clear the fail state
                        cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
                        throw invalid_argument("Invalid input. Key must be an integer.");
                    }
                    root = insert(root, key);
                } catch (const exception& e) {
                    cerr << "Error during TINSERT: " << e.what() << endl;
                }
            } else if (command == "TDEL") {
                try {
                    cout << "Enter key to delete: ";
                    int key;
                    cin >> key;
                    if (cin.fail()) {  // If input is not an integer
                        cin.clear();  // Clear the fail state
                        cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
                        throw invalid_argument("Invalid input. Key must be an integer.");
                    }
                    root = remove(root, key);
                } catch (const exception& e) {
                    cerr << "Error during TDEL: " << e.what() << endl;
                }
            } else if (command == "TGET") {
                try {
                    cout << "Search key (enter -1 to print all): ";
                    int key;
                    cin >> key;
                    if (cin.fail()) {  // If input is not an integer
                        cin.clear();  // Clear the fail state
                        cin.ignore(10000, '\n');  // Ignore the rest of the invalid input
                        throw invalid_argument("Invalid input. Key must be an integer.");
                    }
                    if (key == -1) {
                        inorder(root);
                        cout << endl;
                    } else {
                        if (search(root, key)) {
                            cout << "Key " << key << " found in the tree." << endl;
                        } else {
                            cout << "Key " << key << " not found." << endl;
                        }
                    }
                } catch (const exception& e) {
                    cerr << "Error during TGET: " << e.what() << endl;
                }
            }
 
            // Общая команда PRINT для вывода любой структуры данных
            else if (command == "PRINT") {
                try {
                    if (size == 0) {
                        throw runtime_error("Array is empty.");
                    } else {
                        readArr(arr, size);
                    }

                    read_list(slhead);

                    read_list_from_head(head);

                    read_queue(q);

                    read_stack(s);

                    hget_all(ht);

                    inorder(root);
                } catch (const exception& e) {
                    cerr << "Error during PRINT: " << e.what() << endl;
                }
            }
 
            // Завершение программы
            else if (command == "exit") {
                saveToFile(filename);  // Сохранение данных перед выходом
                cout << "Exiting the program." << endl;
                break;
            }
 
            // Неверная команда
            else {
                throw invalid_argument("Unknown command. Try again.");
            }
        } catch (const exception& e) {
            cerr << "Unhandled error: " << e.what() << endl;
        }
    }
 
    return 0;
}