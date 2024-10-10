#include <iostream>
#include <fstream>
#include <stdexcept> 
#include "Arr.h"
 
// Добавление элемента в конец массива
void push_back(string* &arr, int &size, const string value) {
    string *newArr = new string[size + 1];  // Создаем новый массив размером на 1 больше
    for (int i = 0; i < size; i++) {         // Копируем элементы из старого массива в новый
        newArr[i] = arr[i];
    }
    newArr[size] = value;                    // Добавляем новый элемент в конец
    delete[] arr;                            // Освобождаем память старого массива
    arr = newArr;                            // Указываем arr на новый массив
    size++;                                   // Увеличиваем размер массива
}
 
// Добавление элемента по индексу
void addArr(string* &arr, int &size, int &index, const string value) {
    if (index < 0 || index >= size) {       // Проверяем корректность индекса
        throw out_of_range("Invalid index for adding value.");  // Исключение, если индекс неверный
    }
    string *newArr = new string[size + 1];  // Создаем новый массив размером на 1 больше
    for (int i = 0; i < index; ++i) {       // Копируем элементы до указанного индекса
        newArr[i] = arr[i];
    }
    newArr[index] = value;                  // Вставляем новое значение по индексу
    for (int i = index; i < size; ++i) {    // Копируем оставшиеся элементы
        newArr[i + 1] = arr[i];
    }
    delete[] arr;                            // Освобождаем память старого массива
    arr = newArr;                            // Указываем arr на новый массив
    size++;                                   // Увеличиваем размер массива
}
 
// Получение элемента по индексу
void getAt(string* &arr, int &size, int &index) {
    if (index < 0 || index >= size) {       // Проверяем корректность индекса
        throw out_of_range("Invalid index for getting value.");  // Исключение, если индекс неверный
    }
    cout << arr[index] << endl;              // Выводим значение элемента по индексу
}
 
// Удаление элемента по индексу
void delArr(string* &arr, int &size, int &index) {
    if (index < 0 || index >= size) {       // Проверяем корректность индекса
        throw out_of_range("Invalid index for deleting value.");  // Исключение, если индекс неверный
    }
 
    string* newArr = new string[size - 1];  // Создаем новый массив размером на 1 меньше
 
    for (int i = 0; i < index; ++i) {       // Копируем элементы до указанного индекса
        newArr[i] = arr[i];
    }
 
    for (int i = index + 1; i < size; ++i) {  // Копируем элементы после указанного индекса
        newArr[i - 1] = arr[i];
    }
 
    delete[] arr;                            // Освобождаем память старого массива
    arr = newArr;                            // Указываем arr на новый массив
    size--;                                   // Уменьшаем размер массива
}
 
// Замена элемента по индексу
void replaceArr(string* &arr, int &size, int &index, const string value) {
    if (index < 0 || index >= size) {       // Проверяем корректность индекса
        throw out_of_range("Invalid index for replacing value.");  // Исключение, если индекс неверный
    }
    arr[index] = value;                      // Заменяем значение элемента по индексу
}
 
// Чтение массива
void readArr(string* &arr, int &size) {
    if (size == 0) {                         // Проверяем, пуст ли массив
        throw runtime_error("Array is empty.");  // Исключение, если массив пуст
    }
    for (int i = 0; i < size; i++) {        // Проходим по всем элементам массива
        cout << arr[i] << " ";               // Выводим значения элементов
    }
    cout << endl;                            // Переводим на новую строку после вывода
}
 
// Сохранение массива в файл
void saveArray(ofstream& outFile, string* arr, int size) {
    outFile << "Array " << size << endl;    // Записываем заголовок с размером массива
    for (int i = 0; i < size; ++i) {        // Проходим по всем элементам массива
        outFile << arr[i] << " ";            // Записываем значения элементов в файл
    }
    outFile << endl;                        // Завершаем строку в файле
}
 
// Загрузка массива из файла
void loadArray(ifstream& inFile, string*& arr, int& size) {
    inFile >> size;                          // Читаем размер массива из файла
    arr = new string[size];                  // Выделяем память под новый массив
    for (int i = 0; i < size; ++i) {        // Проходим по всем элементам
        inFile >> arr[i];                    // Читаем значения элементов из файла
    }
}
 
