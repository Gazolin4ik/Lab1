#include <iostream>
#include <fstream>
#include "SLlist.h"
 
// Структура узла односвязного списка
struct SLNode {
    string data;    // Данные узла
    SLNode* next;   // Указатель на следующий узел
};
 
// Добавление элемента в начало списка
void push_front(SLNode*& head, const string& value) {
    SLNode* newNode = new SLNode;   // Создаем новый узел
    newNode->data = value;          // Присваиваем значение новому узлу
    newNode->next = head;           // Новый узел указывает на текущий head
    head = newNode;                 // Новый узел становится новым head
}
 
// Добавление элемента в конец списка
void push_back(SLNode*& head, const string& value) {
    SLNode* newNode = new SLNode;   // Создаем новый узел
    newNode->data = value;          // Присваиваем значение новому узлу
    newNode->next = nullptr;        // Новый узел будет последним, поэтому next указывает на nullptr
 
    if (head == nullptr) {          // Если список пуст
        head = newNode;             // Новый узел становится head
    } else {
        SLNode* current = head;     // Инициализируем указатель current как head
        while (current->next != nullptr) {  // Проходим по списку до последнего узла
            current = current->next;        // Переходим к следующему узлу
        }
        current->next = newNode;     // Связываем последний узел с новым
    }
}
 
// Удаление элемента из начала списка
void pop_front(SLNode*& head) {
    if (head == nullptr) {           // Проверяем, пуст ли список
        throw runtime_error("List is empty. Cannot pop from front.");  // Исключение, если список пуст
    }
    SLNode* temp = head;             // Временный указатель на текущий head
    head = head->next;               // Передвигаем head на следующий узел
    delete temp;                     // Удаляем старый head
}
 
// Удаление элемента с конца списка
void pop_back(SLNode*& head) {
    if (head == nullptr) {           // Проверяем, пуст ли список
        throw runtime_error("List is empty. Cannot pop from back.");  // Исключение, если список пуст
    }
 
    if (head->next == nullptr) {     // Если в списке только один элемент
        delete head;                 // Удаляем единственный элемент
        head = nullptr;              // Обнуляем указатель head
        return;
    }
 
    SLNode* current = head;          // Инициализируем указатель current как head
    while (current->next->next != nullptr) {  // Проходим по списку до предпоследнего узла
        current = current->next;     // Переходим к следующему узлу
    }
    delete current->next;            // Удаляем последний узел
    current->next = nullptr;         // Обнуляем указатель next предпоследнего узла
}
 
// Удаление элемента по значению
void delete_value(SLNode*& head, const string& value) {
    if (head == nullptr) {           // Проверяем, пуст ли список
        throw runtime_error("List is empty. Cannot delete value.");  // Исключение, если список пуст
    }
 
    // Если значение находится в первом узле
    if (head->data == value) {
        pop_front(head);             // Удаляем элемент из начала списка
        return;
    }
 
    SLNode* current = head;          // Инициализируем указатель current как head
    while (current->next != nullptr && current->next->data != value) {  // Проходим по списку, пока не найдем значение
        current = current->next;     // Переходим к следующему узлу
    }
 
    if (current->next == nullptr) {  // Если значение не найдено
        throw runtime_error("Value not found in the list.");  // Исключение, если значение не найдено
    }
 
    SLNode* temp = current->next;    // Временный указатель на узел с искомым значением
    current->next = current->next->next;  // Пропускаем узел с искомым значением
    delete temp;                     // Удаляем узел
}
 
// Чтение всех элементов списка
void read_list(SLNode* head) {
    if (head == nullptr) {           // Проверяем, пуст ли список
        cout << "List is empty." << endl;
        return;
    }
 
    SLNode* current = head;          // Инициализируем указатель current как head
    while (current != nullptr) {     // Проход по списку до конца
        cout << current->data << " -> ";  // Вывод данных узла
        current = current->next;     // Переход к следующему узлу
    }
    cout << "null" << endl;          // Вывод окончания списка
}
 
// Сохранение односвязного списка в файл
void saveSinglyLinkedList(ofstream& outFile, SLNode* head) {
    outFile << "SinglyLinkedList" << endl;  // Запись заголовка для односвязного списка
    SLNode* current = head;                 // Инициализация текущего узла как head
    while (current != nullptr) {            // Проход по списку до конца
        outFile << current->data << " ";    // Запись данных узла в файл
        current = current->next;            // Переход к следующему узлу
    }
    outFile << endl;                        // Завершаем строку в файле
}
 
// Загрузка односвязного списка из файла
void loadSinglyLinkedList(ifstream& inFile, SLNode*& head) {
    string value;                           // Переменная для хранения значения узла
    while (inFile >> value && value != "DoublyLinkedList") {  // Читаем файл до ключевого слова "SinglyLinkedList"
        push_back(head, value);             // Добавляем элемент в конец односвязного списка
    }
}
 