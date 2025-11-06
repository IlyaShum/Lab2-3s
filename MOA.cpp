#include <iostream>
#include <vector>

using namespace std;

class OpenAddressingHashTable {
private:
    vector<pair<int, int>> table;  // Вектор для хранения пар ключ-значение
    vector<bool> occupied;         // Вектор флагов занятости ячеек
    int capacity;                  // Общий размер таблицы
    int size;                      // Текущее количество элементов

    int hash(int key, int attempt) {
        return (key + attempt) % capacity; // Линейное пробирование: key + попытка
    }

public:
    OpenAddressingHashTable(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);           // Инициализируем вектор пар
        occupied.resize(capacity, false); // Инициализируем все ячейки как пустые
    }

    void insert(int key, int value) {
        if (size >= capacity) { // Проверяем, не заполнена ли таблица
            cout << "ОШИБКА: Таблица заполнена!" << endl;
            return;
        }

        for (int attempt = 0; attempt < capacity; attempt++) {
            int index = hash(key, attempt); // Вычисляем индекс с учетом номера попытки
            
            if (!occupied[index]) { // Если ячейка свободна
                table[index] = {key, value}; // Записываем пару ключ-значение
                occupied[index] = true;      // Помечаем ячейку как занятую
                size++;                      // Увеличиваем счетчик элементов
                cout << "Элемент помещен в ячейку " << index << " после " << attempt << " попыток" << endl;
                return; // Выходим из функции
            }
            
            if (occupied[index] && table[index].first == key) { // Если ключ уже существует
                table[index].second = value; // Обновляем значение
                cout << "Элемент обновлен в ячейке " << index << endl;
                return; // Выходим из функции
            }
        }
        
        cout << "ОШИБКА: Не удалось найти свободную ячейку!" << endl;
    }

    bool search(int key, int& value) {
        for (int attempt = 0; attempt < capacity; attempt++) {
            int index = hash(key, attempt); // Вычисляем индекс с учетом номера попытки
            
            if (occupied[index] && table[index].first == key) { // Если нашли нужный ключ
                value = table[index].second; // Записываем значение
                cout << "Элемент найден в ячейке " << index << " после " << attempt << " попыток" << endl;
                return true; // Возвращаем true - элемент найден
            }
            
            if (!occupied[index]) { // Если наткнулись на пустую ячейку
                break; // Прерываем поиск (элемента нет)
            }
        }
        cout << "Элемент не найден!" << endl;
        return false; // Возвращаем false - элемент не найден
    }

    bool remove(int key) {
        for (int attempt = 0; attempt < capacity; attempt++) {
            int index = hash(key, attempt); // Вычисляем индекс с учетом номера попытки
            
            if (occupied[index] && table[index].first == key) { // Если нашли нужный ключ
                occupied[index] = false; // Помечаем ячейку как свободную
                size--;                  // Уменьшаем счетчик элементов
                cout << "Элемент удален из ячейки " << index << endl;
                return true; // Возвращаем true - удаление успешно
            }
            
            if (!occupied[index]) { // Если наткнулись на пустую ячейку
                break; // Прерываем поиск
            }
        }
        cout << "Элемент для удаления не найден!" << endl;
        return false; // Возвращаем false - элемент не найден
    }

    void print() {
        for (int i = 0; i < capacity; i++) { // Проходим по всем ячейкам таблицы
            cout << "Ячейка " << i << ": ";  // Выводим номер ячейки
            if (occupied[i]) {               // Если ячейка занята
                cout << "[" << table[i].first << ":" << table[i].second << "]"; // Выводим ключ:значение
            } else {
                cout << "[ПУСТО]"; // Выводим标记 пустой ячейки
            }
            cout << endl; // Переход на новую строку
        }
        cout << "Всего элементов: " << size << "/" << capacity << endl; // Статистика заполнения
    }
};

int main() {
    int capacity;
    cout << "Введите размер хэш-таблицы: ";
    cin >> capacity;
    
    OpenAddressingHashTable ht(capacity);
    
    while (true) {
        cout << "1. Добавить элемент" << endl;
        cout << "2. Найти элемент" << endl;
        cout << "3. Удалить элемент" << endl;
        cout << "4. Показать таблицу" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int key, value;
                cout << "Введите ключ: ";
                cin >> key;
                cout << "Введите значение: ";
                cin >> value;
                ht.insert(key, value);
                break;
            }
            case 2: {
                int key, value;
                cout << "Введите ключ для поиска: ";
                cin >> key;
                if (ht.search(key, value)) {
                    cout << "Найден элемент: ключ=" << key << ", значение=" << value << endl;
                }
                break;
            }
            case 3: {
                int key;
                cout << "Введите ключ для удаления: ";
                cin >> key;
                ht.remove(key);
                break;
            }
            case 4: {
                ht.print();
                break;
            }
            case 5: {
                cout << "Выход из программы..." << endl;
                return 0;
            }
            default: {
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
            }
        }
    }
    
    return 0;
}
       
