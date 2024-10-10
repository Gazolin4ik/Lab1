#include <iostream>
#include <fstream>
#include <stdexcept>  // for using exceptions
#include "AVL-Tree.h"
 
// Структура узла AVL-дерева
struct AVLNode {
    int key;              // Ключ узла
    AVLNode* left;        // Указатель на левое поддерево
    AVLNode* right;       // Указатель на правое поддерево
    int height;           // Высота узла
 
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {} // Конструктор узла
};
 
// Функция для получения высоты узла
int height(AVLNode* node) {
    return node ? node->height : 0;  // Если узел существует, возвращаем его высоту, иначе 0
}
 
// Рассчитываем балансирующий фактор узла
int getBalance(AVLNode* node) {
    if (!node) return 0;  // Если узел пустой, баланс 0
    return height(node->left) - height(node->right);  // Разница высот левого и правого поддерева
}
 
// Правый поворот
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;  // x — левый ребенок y
    AVLNode* T2 = x->right;  // T2 — правое поддерево x
 
    // Выполняем правый поворот
    x->right = y;
    y->left = T2;
 
    // Обновляем высоты
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
 
    return x;  // Возвращаем новый корень поддерева
}
 
// Левый поворот
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;  // y — правый ребенок x
    AVLNode* T2 = y->left;  // T2 — левое поддерево y
 
    // Выполняем левый поворот
    y->left = x;
    x->right = T2;
 
    // Обновляем высоты
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
 
    return y;  // Возвращаем новый корень поддерева
}
 
// Вставка узла в AVL-дерево
AVLNode* insert(AVLNode* node, int key) {
    // 1. Выполняем стандартную вставку как в бинарном дереве поиска
    if (!node) return new AVLNode(key);  // Если узел пуст, создаем новый узел
 
    if (key < node->key) {               // Если ключ меньше текущего узла
        node->left = insert(node->left, key);  // Вставляем в левое поддерево
    } else if (key > node->key) {        // Если ключ больше текущего узла
        node->right = insert(node->right, key);  // Вставляем в правое поддерево
    } else {
        throw invalid_argument("Duplicate keys are not allowed in AVL tree.");  // Дубликаты ключей не разрешены
    }
 
    // 2. Обновляем высоту текущего узла
    node->height = 1 + max(height(node->left), height(node->right));
 
    // 3. Получаем балансирующий фактор узла
    int balance = getBalance(node);
 
    // 4. Выполняем балансировку дерева, если оно разбалансировано
 
    // Случай левый-левый
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);  // Выполняем правый поворот
    }
 
    // Случай правый-правый
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);  // Выполняем левый поворот
    }
 
    // Случай левый-правый
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);  // Сначала левый поворот
        return rotateRight(node);             // Затем правый поворот
    }
 
    // Случай правый-левый
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);  // Сначала правый поворот
        return rotateLeft(node);                 // Затем левый поворот
    }
 
    return node;  // Возвращаем неизмененный узел
}
 
// Поиск узла с минимальным ключом (используется при удалении)
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;               // Начинаем с текущего узла
    while (current->left != nullptr)       // Спускаемся в самое левое поддерево
        current = current->left;
    return current;                        // Возвращаем узел с минимальным ключом
}
 
// Удаление узла из AVL-дерева
AVLNode* remove(AVLNode* root, int key) {
    // 1. Выполняем стандартное удаление как в бинарном дереве поиска
    if (!root) throw runtime_error("Key not found in AVL tree.");  // Если узел не найден
 
    if (key < root->key) {                 // Если ключ меньше текущего узла
        root->left = remove(root->left, key);  // Удаляем из левого поддерева
    } else if (key > root->key) {          // Если ключ больше текущего узла
        root->right = remove(root->right, key);  // Удаляем из правого поддерева
    } else {                               // Если ключ совпадает
        // Узел с одним ребенком или без детей
        if (!root->left || !root->right) {  // Если у узла один или ноль детей
            AVLNode* temp = root->left ? root->left : root->right;  // Выбираем не-null ребенка
 
            if (!temp) {                    // Если у узла нет детей
                temp = root;
                root = nullptr;             // Удаляем узел
            } else {
                *root = *temp;              // Копируем данные ребенка в узел
            }
 
            delete temp;                    // Удаляем временный узел
        } else {
            // Узел с двумя детьми
            AVLNode* temp = minValueNode(root->right);  // Находим узел с минимальным ключом в правом поддереве
            root->key = temp->key;           // Копируем ключ
            root->right = remove(root->right, temp->key);  // Удаляем узел с минимальным ключом
        }
    }
 
    if (!root) return root;  // Если дерево пустое после удаления, возвращаем nullptr
 
    // 2. Обновляем высоту текущего узла
    root->height = 1 + max(height(root->left), height(root->right));
 
    // 3. Получаем балансирующий фактор узла
    int balance = getBalance(root);
 
    // 4. Балансируем дерево, если оно разбалансировано
 
    // Случай левый-левый
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);  // Выполняем правый поворот
    }
 
    // Случай левый-правый
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);  // Сначала левый поворот
        return rotateRight(root);             // Затем правый поворот
    }
 
    // Случай правый-правый
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);  // Выполняем левый поворот
    }
 
    // Случай правый-левый
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);  // Сначала правый поворот
        return rotateLeft(root);                 // Затем левый поворот
    }
 
    return root;  // Возвращаем текущий корень
}
 
// Поиск элемента в AVL-дереве
bool search(AVLNode* root, int key) {
    if (!root) return false;               // Если узел не найден, возвращаем false
    if (key == root->key) return true;     // Если ключ совпадает, возвращаем true
    if (key < root->key) return search(root->left, key);  // Ищем в левом поддереве
    return search(root->right, key);       // Ищем в правом поддереве
}

// Функция для печати дерева
void printAVLTree(string& result, AVLNode* tree, int depth, string prefix) {
    if (tree == nullptr) {
        return;
    }
 
    // Выводим правое поддерево (расположено выше в консоли)
    if (tree->right != nullptr) {
        printAVLTree(result, tree->right, depth + 1, prefix + "\t");
    }
 
    // Выводим текущий узел с отступом
    result += prefix;
    if (depth > 0) {
        result += "└──";
    }
    result += "[" + to_string(tree->key) + "]\n";  // Изменено на tree->key для работы с AVLNode
 
    // Выводим левое поддерево (расположено ниже в консоли)
    if (tree->left != nullptr) {
        printAVLTree(result, tree->left, depth + 1, prefix + "\t");
    }
}
 
// Сохранение симметричного обхода в файл
void saveInOrder(ofstream& outFile, AVLNode* node) {
    if (node == nullptr) return;           // Если узел пуст, ничего не делаем
    saveInOrder(outFile, node->left);      // Сохраняем левое поддерево
    outFile << node->key << " ";           // Сохраняем ключ узла
    saveInOrder(outFile, node->right);     // Сохраняем правое поддерево
}
 
// Сохранение AVL-дерева в файл
void saveAVLTree(ofstream& outFile, AVLNode* root) {
    outFile << "AVLTree" << endl;          // Запись заголовка для AVL-дерева
    saveInOrder(outFile, root);            // Сохранение дерева в порядке симметричного обхода
    outFile << endl;
}
 
// Загрузка AVL-дерева из файла
void loadAVLTree(ifstream& inFile, AVLNode*& root) {
    int key;                               // Переменная для хранения ключа
    while (inFile >> key) {                // Продолжаем чтение ключей до конца строки
        root = insert(root, key);          // Вставляем ключ в AVL-дерево
    }
}
 
