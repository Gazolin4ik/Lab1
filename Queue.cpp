#include <iostream>
#include <fstream>
#include "Queue.h"
 
// Инициализация пустой очереди
void initQueue(Queue& q) {
    q.front = nullptr;  // Указатель front указывает на nullptr (очередь пуста)
    q.rear = nullptr;   // Указатель rear также указывает на nullptr
}
 
// Добавление элемента в конец очереди
void push(Queue& q, const string& value) {
    QNode* newNode = new QNode;   // Создаем новый узел для очереди
    newNode->data = value;        // Присваиваем узлу значение value
    newNode->next = nullptr;      // Новый узел будет последним, поэтому next указывает на nullptr
    newNode->prev = q.rear;       // Новый узел указывает на текущий rear как на предыдущий узел
 
    if (q.rear == nullptr) {      // Если очередь пуста (rear равен nullptr)
        q.front = q.rear = newNode;  // Новый узел становится и front, и rear
    } else {
        q.rear->next = newNode;   // Связываем текущий rear с новым узлом
        q.rear = newNode;         // Новый узел становится новым rear
    }
}
 
// Удаление элемента из начала очереди
void pop(Queue& q) {
    if (q.front == nullptr) {     // Проверяем, пуста ли очередь
        throw runtime_error("Queue is empty. Cannot pop.");  // Исключение, если очередь пуста
    }
 
    QNode* temp = q.front;        // Временный указатель на текущий front
    q.front = q.front->next;      // Передвигаем front на следующий узел
 
    if (q.front != nullptr) {     // Если очередь не пуста после удаления
        q.front->prev = nullptr;  // Устанавливаем prev нового front в nullptr
    } else {
        q.rear = nullptr;         // Если очередь стала пустой, rear также указывает на nullptr
    }
 
    delete temp;                  // Удаляем старый front
}
 
// Чтение всех элементов очереди начиная с front
void read_queue(Queue& q) {
    if (q.front == nullptr) {     // Проверяем, пуста ли очередь
        cout << "Queue is empty." << endl;
        return;
    }
 
    QNode* current = q.front;     // Инициализация текущего узла как front
    while (current != nullptr) {  // Проход по очереди до конца
        cout << current->data << " -> ";  // Вывод данных узла
        current = current->next;          // Переход к следующему узлу
    }
    cout << "null" << endl;               // Вывод окончания очереди
}
 
// Сохранение очереди в файл
void saveQueue(ofstream& outFile, Queue q) {
    outFile << "Queue" << endl;           // Запись заголовка для очереди
    QNode* current = q.front;             // Инициализация текущего узла как front
    while (current != nullptr) {          // Проход по очереди до конца
        outFile << current->data << " ";  // Запись данных узла в файл
        current = current->next;          // Переход к следующему узлу
    }
    outFile << endl;                      // Завершаем строку в файле
}
 
// Загрузка очереди из файла
void loadQueue(ifstream& inFile, Queue& q) {
    string value;                         // Переменная для хранения значения узла
    while (inFile >> value && value != "Stack") {  // Читаем файл до ключевого слова "Stack"
        push(q, value);                   // Добавляем элемент в очередь
    }
}
 