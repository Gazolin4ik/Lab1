#include <iostream>
#include <fstream>
#include "DLlist.h"
 
// Структура узла двусвязного списка
struct DLNode {
    string data;    // Данные узла
    DLNode* next;   // Указатель на следующий узел
    DLNode* prev;   // Указатель на предыдущий узел
};
 
// Добавление элемента в начало списка
void push_front(DLNode*& head, DLNode*& tail, const string& value) {
    DLNode* newNode = new DLNode;      // Создание нового узла
    newNode->data = value;             // Присваиваем значение новому узлу
    newNode->next = head;              // Новый узел указывает на текущий head
    newNode->prev = nullptr;           // Новый узел будет первым, поэтому prev указывает на nullptr
 
    if (head != nullptr) {             // Если список не пуст
        head->prev = newNode;          // Устанавливаем указатель prev текущего head на новый узел
    } else {
        tail = newNode;                // Если список пуст, новый узел становится также и tail
    }
 
    head = newNode;                    // Новый узел становится head
}
 
// Добавление элемента в конец списка
void push_back(DLNode*& head, DLNode*& tail, const string& value) {
    DLNode* newNode = new DLNode;      // Создание нового узла
    newNode->data = value;             // Присваиваем значение новому узлу
    newNode->next = nullptr;           // Новый узел будет последним, поэтому next указывает на nullptr
    newNode->prev = tail;              // Новый узел указывает на текущий tail
 
    if (tail != nullptr) {             // Если список не пуст
        tail->next = newNode;          // Устанавливаем указатель next текущего tail на новый узел
    } else {
        head = newNode;                // Если список пуст, новый узел становится также и head
    }
 
    tail = newNode;                    // Новый узел становится tail
}
 
// Удаление элемента из начала списка
void pop_front(DLNode*& head, DLNode*& tail) {
    if (head == nullptr) {             // Проверяем, пуст ли список
        throw runtime_error("List is empty. Cannot pop from front.");  // Исключение, если список пуст
    }
 
    DLNode* temp = head;               // Временный указатель на текущий head
    head = head->next;                 // Передвигаем head на следующий узел
 
    if (head != nullptr) {             // Если список не пуст после удаления
        head->prev = nullptr;          // Устанавливаем prev нового head в nullptr
    } else {
        tail = nullptr;                // Если список стал пустым, tail также должен стать nullptr
    }
 
    delete temp;                       // Удаляем старый head
}
 
// Удаление элемента с конца списка
void pop_back(DLNode*& head, DLNode*& tail) {
    if (tail == nullptr) {             // Проверяем, пуст ли список
        throw runtime_error("List is empty. Cannot pop from back.");  // Исключение, если список пуст
    }
 
    DLNode* temp = tail;               // Временный указатель на текущий tail
    tail = tail->prev;                 // Передвигаем tail на предыдущий узел
 
    if (tail != nullptr) {             // Если список не пуст после удаления
        tail->next = nullptr;          // Устанавливаем next нового tail в nullptr
    } else {
        head = nullptr;                // Если список стал пустым, head также должен стать nullptr
    }
 
    delete temp;                       // Удаляем старый tail
}
 
// Удаление элемента по значению
void delete_value(DLNode*& head, DLNode*& tail, const string& value) {
    if (head == nullptr) {             // Проверяем, пуст ли список
        throw runtime_error("List is empty. Cannot delete value.");  // Исключение, если список пуст
    }
 
    DLNode* current = head;            // Инициализация текущего узла как head
    while (current != nullptr && current->data != value) {  // Проход по списку, пока не найдем значение
        current = current->next;       // Переходим к следующему узлу
    }
 
    if (current == nullptr) {          // Если значение не найдено
        throw runtime_error("Value not found in the list.");  // Исключение, если значение не найдено
    }
 
    if (current == head) {             // Если узел с данным значением — это head
        pop_front(head, tail);         // Удаляем узел с начала
    } else if (current == tail) {      // Если узел с данным значением — это tail
        pop_back(head, tail);          // Удаляем узел с конца
    } else {                           // Если узел находится в середине списка
        current->prev->next = current->next;  // Связываем предыдущий узел с следующим
        current->next->prev = current->prev;  // Связываем следующий узел с предыдущим
        delete current;                // Удаляем текущий узел
    }
}
 
// Чтение всех элементов списка с начала
void read_list_from_head(DLNode* head) {
    if (head == nullptr) {             // Проверяем, пуст ли список
        cout << "List is empty." << endl;
        return;
    }
 
    DLNode* current = head;            // Инициализация текущего узла как head
    while (current != nullptr) {       // Проход по списку до конца
        cout << current->data << " -> ";  // Вывод данных узла
        current = current->next;       // Переход к следующему узлу
    }
    cout << "null" << endl;            // Вывод окончания списка
}
 
// Чтение всех элементов списка с конца
void read_list_from_tail(DLNode* tail) {
    if (tail == nullptr) {             // Проверяем, пуст ли список
        cout << "List is empty." << endl;
        return;
    }
 
    DLNode* current = tail;            // Инициализация текущего узла как tail
    while (current != nullptr) {       // Проход по списку до начала
        cout << current->data << " -> ";  // Вывод данных узла
        current = current->prev;       // Переход к предыдущему узлу
    }
    cout << "null" << endl;            // Вывод окончания списка
}
 
// Сохранение двусвязного списка в файл
void saveDoublyLinkedList(ofstream& outFile, DLNode* head) {
    outFile << "DoublyLinkedList" << endl;  // Запись заголовка для двусвязного списка
    DLNode* current = head;                 // Инициализация текущего узла как head
    while (current != nullptr) {            // Проход по списку до конца
        outFile << current->data << " ";    // Запись данных узла в файл
        current = current->next;            // Переход к следующему узлу
    }
    outFile << endl;                        // Завершаем строку в файле
}
 
// Загрузка двусвязного списка из файла
void loadDoublyLinkedList(ifstream& inFile, DLNode*& head, DLNode*& tail) {
    string value;                           // Переменная для хранения значения узла
    while (inFile >> value && value != "Queue") {  // Читаем файл до ключевого слова "Queue"
        push_back(head, tail, value);       // Добавляем элемент в конец двусвязного списка
    }
}