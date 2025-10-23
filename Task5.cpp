#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Структура для узла дерева
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

struct BinarySearchTree {
    TreeNode* root;
};

// Создание нового узла
TreeNode* createNode(int value) {
    TreeNode* newNode = new TreeNode;
    newNode->data = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Вставка элемента в дерево
void insertIterative(BinarySearchTree& tree, int value) {
    TreeNode* newNode = createNode(value);
    
    if (tree.root == nullptr) {
        tree.root = newNode;
        return;
    }
    
    TreeNode* current = tree.root;
    TreeNode* parent = nullptr;
    
    while (current != nullptr) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

// Проверка на лист
bool isLeaf(TreeNode* node) {
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}

// Сбор листьев в порядке возрастания
void collectLeaves(TreeNode* node, int* result, int& index) {
    if (node == nullptr) return;
    
    collectLeaves(node->left, result, index);
    
    if (isLeaf(node)) {
        result[index++] = node->data;
    }
    
    collectLeaves(node->right, result, index);
}

// Очистка дерева
void clearTree(TreeNode* node) {
    if (node == nullptr) return;
    
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    BinarySearchTree tree;
    tree.root = nullptr;
    
    cout << "Введите числа для построения бинарного дерева поиска через пробел: ";
    
    string input;
    getline(cin, input); // Читаем всю строку
    
    stringstream ss(input);
    int num;
    
    // Читаем все числа из строки
    while (ss >> num) {
        insertIterative(tree, num);
    }
    
    // Сбор листьев
    int leaves[100];
    int leafCount = 0;
    collectLeaves(tree.root, leaves, leafCount);
    
    // Вывод результата
    if (leafCount > 0) {
        cout << "Листья дерева в порядке возрастания: ";
        for (int i = 0; i < leafCount; i++) {
            cout << leaves[i];
            if (i < leafCount - 1) {
                cout << " ";
            }
        }
        cout << endl;
    } else {
        cout << "В дереве нет листьев" << endl;
    }
    
    // Очистка памяти
    clearTree(tree.root);
    
    return 0;
}
