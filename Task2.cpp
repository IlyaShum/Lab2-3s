#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Структура для узла множества
struct SetNode {
    string data;
    SetNode* next;
};

// Структура для множества
struct Set {
    SetNode* head;
    
    // Конструктор
    Set() : head(nullptr) {}
    
    // Проверка наличия элемента
    bool contains(const string& value) {
        SetNode* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Добавление элемента
    bool add(const string& value) {
        if (contains(value)) {
            return false; // Элемент уже существует
        }
        
        SetNode* newNode = new SetNode;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        return true;
    }
    
    // Удаление элемента
    bool remove(const string& value) {
        SetNode* current = head;
        SetNode* prev = nullptr;
        
        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; // Элемент не найден
    }
    
    // Получение всех элементов
    void getElements(string* elements, int& count) {
        count = 0;
        SetNode* current = head;
        while (current != nullptr) {
            elements[count++] = current->data;
            current = current->next;
        }
    }
    
    // Очистка множества
    void clear() {
        while (head != nullptr) {
            SetNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Деструктор
    ~Set() {
        clear();
    }
};

// Функция для чтения множества из файла
void readSetFromFile(Set& set, const string& filename) {
    ifstream file(filename);
    string element;
    while (file >> element) {
        set.add(element);
    }
    file.close();
}

// Функция для записи множества в файл
void writeSetToFile(Set& set, const string& filename) {
    ofstream outfile(filename);
    
    // Получаем все элементы
    const int MAX_ELEMENTS = 1000;
    string elements[MAX_ELEMENTS];
    int count = 0;
    set.getElements(elements, count);
    
    for (int i = 0; i < count; i++) {
        outfile << elements[i] << endl;
    }
    outfile.close();
}

// Функция для обработки запросов к множеству
void processSetOperations(const string& filename, const string& query) {
    Set set;
    
    // Чтение существующих данных из файла
    readSetFromFile(set, filename);
    
    // Разделение запроса на операцию и значение
    size_t spacePos = query.find(' ');
    string operation = query.substr(0, spacePos);
    string value = query.substr(spacePos + 1);
    
    if (operation == "SETADD") {
        if (set.add(value)) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    else if (operation == "SETDEL") {
        if (set.remove(value)) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    else if (operation == "SET_AT") {
        if (set.contains(value)) {
            cout << "true" << endl;
        } else {
            cout << "false" << endl;
        }
    }
    else {
        cout << "Invalid operation" << endl;
        return;
    }
    
    // Запись обновленного множества обратно в файл
    writeSetToFile(set, filename);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " --file <filename> --query <operation>" << endl;
        cout << "Operations: SETADD <value>, SETDEL <value>, SET_AT <value>" << endl;
        return 1;
    }
    
    string filename, query;
    
    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        }
        else if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }
    
    if (filename.empty() || query.empty()) {
        cout << "Error: Missing filename or query" << endl;
        return 1;
    }
    
    processSetOperations(filename, query);
    return 0;
}
