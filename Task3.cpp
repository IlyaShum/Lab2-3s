#include <iostream>

using namespace std;

// Структура для узла множества
struct SetNode {
    int data;
    SetNode* next;
};

// Структура для множества
struct Set {
    SetNode* head;
    
    Set() : head(nullptr) {}
};

// Функция для проверки наличия элемента в множестве
bool contains(const Set& s, int value) {
    SetNode* current = s.head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Функция для добавления элемента в множество
void addToSet(Set& s, int value) {
    if (contains(s, value)) {
        return; // Элемент уже существует
    }
    
    SetNode* newNode = new SetNode;
    newNode->data = value;
    newNode->next = s.head;
    s.head = newNode;
}

// Функция для вывода элементов множества
void printSet(const Set& s) {
    SetNode* current = s.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Функция для объединения двух множеств
Set unionSets(const Set& set1, const Set& set2) {
    Set result;
    
    // Добавляем все элементы из первого множества
    SetNode* current = set1.head;
    while (current != nullptr) {
        addToSet(result, current->data);
        current = current->next;
    }
    
    // Добавляем все элементы из второго множества
    current = set2.head;
    while (current != nullptr) {
        addToSet(result, current->data);
        current = current->next;
    }
    
    return result;
}

// Функция для пересечения двух множеств
Set intersectSets(const Set& set1, const Set& set2) {
    Set result;
    
    SetNode* current = set1.head;
    while (current != nullptr) {
        if (contains(set2, current->data)) {
            addToSet(result, current->data);
        }
        current = current->next;
    }
    
    return result;
}

// Функция для разности двух множеств (set1 - set2)
Set differenceSets(const Set& set1, const Set& set2) {
    Set result;
    
    SetNode* current = set1.head;
    while (current != nullptr) {
        if (!contains(set2, current->data)) {
            addToSet(result, current->data);
        }
        current = current->next;
    }
    
    return result;
}

// Функция для ввода множества с клавиатуры
Set inputSet(const string& setName) {
    Set s;
    int n, value;
    cout << "Введите количество элементов множества " << setName << ": ";
    cin >> n;
    cout << "Введите элементы множества " << setName << " (через пробел): ";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        addToSet(s, value);
    }
    return s;
}

// Функция для очистки памяти
void clearSet(Set& s) {
    SetNode* current = s.head;
    while (current != nullptr) {
        SetNode* temp = current;
        current = current->next;
        delete temp;
    }
    s.head = nullptr;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    // Ввод множеств с клавиатуры
    Set set1 = inputSet("Set1");
    Set set2 = inputSet("Set2");

    // Выводим исходные множества
    cout << "Set 1: ";
    printSet(set1);
    cout << "Set 2: ";
    printSet(set2);

    // Объединение множеств
    Set unionResult = unionSets(set1, set2);
    cout << "Объединение: ";
    printSet(unionResult);

    // Пересечение множеств
    Set intersectResult = intersectSets(set1, set2);
    cout << "Пересечение: ";
    printSet(intersectResult);

    // Разность множеств (set1 - set2)
    Set differenceResult = differenceSets(set1, set2);
    cout << "Разность(Set1 - Set2): ";
    printSet(differenceResult);

    // Очистка памяти
    clearSet(set1);
    clearSet(set2);
    clearSet(unionResult);
    clearSet(intersectResult);
    clearSet(differenceResult);

    return 0;
}
