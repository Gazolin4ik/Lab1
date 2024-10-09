#include <iostream>
#include <fstream>
#include "Stack.h"
 
// Инициализация пустого стека
void initStack(Stack& s) {
    s.top = nullptr;  // Указатель top указывает на nullptr (стек пуст)
}
 
// Добавление элемента на вершину стека
void Spush(Stack& s, const string& value) {
    SNode* newNode = new SNode;   // Создаем новый узел стека
    newNode->data = value;        // Присваиваем узлу значение value
    newNode->next = s.top;        // Новый узел указывает на текущую вершину стека
    s.top = newNode;              // Новый узел становится вершиной стека
}
 
// Удаление элемента с вершины стека
void Spop(Stack& s) {
    if (s.top == nullptr) {       // Проверяем, пуст ли стек
        throw runtime_error("Stack is empty. Cannot pop.");  // Исключение, если стек пуст
    }
 
    SNode* temp = s.top;          // Временный указатель на текущую вершину стека
    s.top = s.top->next;          // Перемещаем указатель top на следующий элемент
    delete temp;                  // Удаляем старую вершину
}
 
// Чтение всех элементов стека
void read_stack(Stack& s) {
    if (s.top == nullptr) {       // Проверяем, пуст ли стек
        cout << "Stack is empty." << endl;
        return;
    }
 
    SNode* current = s.top;       // Инициализация указателя current как вершина стека
    while (current != nullptr) {  // Проход по стеку до конца
        cout << current->data << " -> ";  // Вывод данных узла
        current = current->next;  // Переход к следующему элементу
    }
    cout << "null" << endl;       // Вывод окончания стека
}
 
// Сохранение стека в файл
void saveStack(ofstream& outFile, Stack s) {
    outFile << "Stack" << endl;           // Запись заголовка для стека
    SNode* current = s.top;               // Инициализация текущего узла как вершина стека
    while (current != nullptr) {          // Проход по стеку до конца
        outFile << current->data << " ";  // Запись данных узла в файл
        current = current->next;          // Переход к следующему элементу
    }
    outFile << endl;                      // Завершаем строку в файле
}
 
// Загрузка стека из файла
void loadStack(ifstream& inFile, Stack& s) {
    string value;                         // Переменная для хранения значения узла
    while (inFile >> value && value != "HashTable") {  // Читаем файл до ключевого слова "HashTable"
        Spush(s, value);                  // Добавляем элемент в стек
    }
}