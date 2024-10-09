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
 
// g++ Main.cpp Arr.cpp AVL-Tree.cpp DLlist.cpp HashTable.cpp Queue.cpp SLlist.cpp Stack.cpp -o Main

int main() {
    string command, filename = "data.txt";
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

    // Загружаем данные из файла при старте программы
    ifstream inFile(filename);
    if (inFile) {
        // Загрузка данных для каждой структуры данных
        loadArray(inFile, arr, size);                // Загрузка массива
        loadSinglyLinkedList(inFile, slhead);        // Загрузка односвязного списка
        loadDoublyLinkedList(inFile, head, tail);// Загрузка двусвязного списка
        loadQueue(inFile, q);                        // Загрузка очереди
        loadStack(inFile, s);                        // Загрузка стека
        loadHashTable(inFile, ht);                   // Загрузка хэш-таблицы
        loadAVLTree(inFile, root);                   // Загрузка AVL-дерева
        inFile.close();
    }
 
    while (true) {
        try {
            cout << "Enter command (MPUSH, LDEL, QPOP, etc. or PRINT, exit): ";
            cin >> command;
 
            // Массив (M)
            if (command == "MPUSH") {
            try {
                cout << "Enter index (-1 to add at the end): ";
                string indexStr;
                cin >> indexStr;
 
                if (indexStr != "-1" && size != 0) {
                    try {
                        int index = stoi(indexStr);  // Пробуем преобразовать строку в число
                        if (index >= 0 && index < size) {
                            cout << "Replace existing value? [y/n]: ";
                            string response;
                            cin >> response;
                            if (response == "y") {
                                cout << "Enter new value: ";
                                string value;
                                cin >> value;
                                replaceArr(arr, size, index, value);  // Замена значения
                            } else if (response == "n") {
                                cout << "Enter new value: ";
                                string value;
                                cin >> value;
                                addArr(arr, size, index, value);  // Вставка нового значения
                            } else {
                                throw invalid_argument("Invalid option for MPUSH.");  // Неверная опция
                            }
                        } else {
                            throw out_of_range("Invalid index for MPUSH.");  // Индекс вне допустимых границ
                        }
                    } catch (const invalid_argument&) {  // Ловим ошибку преобразования в число
                        cerr << "Error during MPUSH: Invalid input, expected an integer." << endl;
                    } catch (const out_of_range&) {  // Ловим ошибку диапазона
                        cerr << "Error during MPUSH: Index out of range." << endl;
                    }
                } else {  // Добавление в конец массива
                    cout << "Enter value to push at the end: ";
                    string value;
                    cin >> value;
                    push_back(arr, size, value);  // Добавление в конец
                }
            } catch (const exception& e) {
                cerr << "Error during MPUSH: " << e.what() << endl;
            }
            }
 
            // Удаление из массива (MDEL)
            else if (command == "MDEL") {
            try {
                if (size == 0) {
                    throw runtime_error("Array is empty, nothing to delete.");
                } else {
                    cout << "Enter index to delete: ";
                    string indexStr;
                    cin >> indexStr;
 
                    try {
                        int index = stoi(indexStr);  // Пробуем преобразовать строку в число
                        delArr(arr, size, index);  // Удаление элемента по индексу
                    } catch (const invalid_argument&) {
                        cerr << "Error during MDEL: Invalid input." << endl;
                    } catch (const out_of_range&) {
                        cerr << "Error during MDEL: Index out of range." << endl;
                    }
                }
            } catch (const exception& e) {
                cerr << "Error during MDEL: " << e.what() << endl;
            }
            }
 
            // Получение элемента (MGET)
            else if (command == "MGET") {
            try {
                if (size == 0) {
                    throw runtime_error("Array is empty.");
                } else {
                    cout << "Enter index (or 'all' to get all elements): ";
                    string indexStr;
                    cin >> indexStr;
 
                    if (indexStr != "all") {
                        try {
                            int index = stoi(indexStr);  // Пробуем преобразовать строку в число
                            getAt(arr, size, index);  // Получаем элемент по индексу
                        } catch (const invalid_argument&) {
                            cerr << "Error during MGET: Invalid input." << endl;
                        } catch (const out_of_range&) {
                            cerr << "Error during MGET: Index out of range." << endl;
                        }
                    } else if (indexStr == "all") {
                        cout << "Array: ";
                        readArr(arr, size);  // Чтение всего массива
                        cout << "Array size: " << size << endl;
                    } else {
                        throw invalid_argument("Invalid option for MGET.");  // Неверная опция
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
                // Сохраняем данные в файл при завершении программы
                ofstream outFile(filename);
                if (outFile) {
                // Сохранение данных для каждой структуры данных
                    saveArray(outFile, arr, size);               // Сохранение массива
                    saveSinglyLinkedList(outFile, slhead);       // Сохранение односвязного списка
                    saveDoublyLinkedList(outFile, head);         // Сохранение двусвязного списка
                    saveQueue(outFile, q);                       // Сохранение очереди
                    saveStack(outFile, s);                       // Сохранение стека
                    saveHashTable(outFile, ht);                  // Сохранение хэш-таблицы
                    saveAVLTree(outFile, root);                  // Сохранение AVL-дерева
                    outFile.close();
                }
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
    
    delete[] arr;
    return 0;
}