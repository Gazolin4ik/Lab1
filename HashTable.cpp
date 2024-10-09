#include <iostream>
#include <fstream>
#include "HashTable.h"
 
// Простая хеш-функция для строки
int hashFunction(const string& key) {
    int hash = 0;                  // Инициализация переменной hash значением 0
    for (char ch : key) {           // Проход по каждому символу строки (ключа)
        hash += ch;                 // Добавление ASCII-кода символа к переменной hash
    }
    return hash % TABLE_SIZE;       // Возвращаем хеш по модулю TABLE_SIZE (размер таблицы)
}
 
// Добавление элемента (ключ-значение) в хеш-таблицу
void hset(HashTable& ht, const string& key, const string& value) {
    int index = hashFunction(key);  // Вычисление индекса с помощью хеш-функции
    HashNode* newNode = new HashNode{key, value, nullptr}; // Создание нового узла с ключом и значением
 
    // Если бакет пуст, добавляем узел
    if (ht.table[index] == nullptr) {
        ht.table[index] = newNode;  // Если бакет пустой, добавляем новый узел
    } else {
        // Если бакет не пуст, ищем существующий ключ или добавляем в конец цепочки
        HashNode* current = ht.table[index]; // Получение первого узла в цепочке
        while (current != nullptr) {         // Проход по цепочке узлов
            if (current->key == key) {       // Если ключ уже существует
                current->value = value;      // Обновляем значение узла
                delete newNode;              // Удаляем новый узел, так как он больше не нужен
                return;                     
            }
            if (current->next == nullptr) {  // Если достигли конца цепочки
                current->next = newNode;     // Добавляем новый узел в конец цепочки
                return;                      
            }
            current = current->next;         // Переход к следующему узлу
        }
    }
}
 
// Получение значения по ключу
string hget_by_key(HashTable& ht, const string& key) {
    int index = hashFunction(key);           // Вычисление индекса для ключа
    HashNode* current = ht.table[index];     // Получение первого узла в бакете
 
    // Проход по цепочке узлов, чтобы найти ключ
    while (current != nullptr) {
        if (current->key == key) {           // Если ключ найден
            return current->value;           // Возвращаем значение
        }
        current = current->next;             // Переход к следующему узлу
    }
 
    throw runtime_error("Key not found in hash table.");  // Если ключ не найден, выбрасываем исключение
}
 
// Получение всех значений из хеш-таблицы
void hget_all(HashTable& ht) {
    bool isEmpty = true;                     // Флаг для проверки, пуста ли таблица
    for (int i = 0; i < TABLE_SIZE; ++i) {   // Проход по каждому бакету
        HashNode* current = ht.table[i];     // Получение первого узла в бакете
        if (current != nullptr) {            // Если бакет не пуст
            isEmpty = false;                 // Сбрасываем флаг, что таблица не пуста
            cout << "Bucket " << i << ": ";
            while (current != nullptr) {     // Проход по цепочке узлов
                cout << "[" << current->key << ": " << current->value << "] "; // Вывод ключа и значения
                current = current->next;     // Переход к следующему узлу
            }
            cout << endl;
        }
    }
    if (isEmpty) {                           // Если все бакеты пусты
        cout << "Hash table is empty." << endl;
    }
}
 
// Удаление элемента по ключу
void hdel(HashTable& ht, const string& key) {
    int index = hashFunction(key);           // Вычисление индекса для ключа
    HashNode* current = ht.table[index];     // Получение первого узла в бакете
    HashNode* prev = nullptr;                // Указатель на предыдущий узел для корректного удаления
 
    // Проход по цепочке узлов, чтобы найти и удалить узел с данным ключом
    while (current != nullptr) {
        if (current->key == key) {           // Если ключ найден
            if (prev == nullptr) {           // Если узел первый в цепочке
                ht.table[index] = current->next; // Удаляем первый узел, сдвигаем цепочку
            } else {
                prev->next = current->next;  // Удаление узла в середине или конце цепочки
            }
            delete current;                  // Удаляем узел из памяти
            return;                          
        }
        prev = current;                      // Сохраняем текущий узел как предыдущий
        current = current->next;             // Переход к следующему узлу
    }
 
    throw runtime_error("Key not found in hash table.");  // Если ключ не найден, выбрасываем исключение
}
 
// Вывод всей хеш-таблицы
void printHashTable(const HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {   // Проход по каждому бакету
        cout << "Bucket " << i << ": ";
        HashNode* current = ht.table[i];     // Получение первого узла в бакете
        while (current != nullptr) {         // Проход по цепочке узлов
            cout << "[" << current->key << ": " << current->value << "] "; // Вывод ключа и значения
            current = current->next;         // Переход к следующему узлу
        }
        cout << endl;
    }
}
 
// Сохранение хеш-таблицы в файл
void saveHashTable(ofstream& outFile, HashTable& ht) {
    outFile << "HashTable" << endl;          // Записываем заголовок для хеш-таблицы
    for (int i = 0; i < TABLE_SIZE; ++i) {   // Проход по каждому бакету
        HashNode* current = ht.table[i];     // Получение первого узла в бакете
        while (current != nullptr) {         // Проход по цепочке узлов
            outFile << current->key << ":" << current->value << " "; // Записываем ключ и значение
            current = current->next;         // Переход к следующему узлу
        }
    }
    outFile << endl;                         // Переход на новую строку после записи всех данных
}
 
// Загрузка хеш-таблицы из файла
void loadHashTable(ifstream& inFile, HashTable& ht) {
    string pair;                             // Строка для хранения пары ключ-значение
    while (inFile >> pair && pair != "AVLTree") { // Чтение до тех пор, пока не встретится "AVLTree"
        size_t colonPos = pair.find(':');    // Поиск позиции двоеточия
        string key = pair.substr(0, colonPos);   // Извлечение ключа
        string value = pair.substr(colonPos + 1); // Извлечение значения
        hset(ht, key, value);                // Добавляем элемент в хеш-таблицу
    }
}