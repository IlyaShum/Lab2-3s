#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Структура для узла стека
struct StackNode {
    char data;
    StackNode* next;
};

// Структура для стека
struct Stack {
    StackNode* top;
    
    // Конструктор
    Stack() : top(nullptr) {}
    
    // Проверка на пустоту
    bool isEmpty() {
        return top == nullptr;
    }
    
    // Добавление элемента
    void push(char value) {
        StackNode* newNode = new StackNode;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }
    
    // Извлечение элемента
    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        StackNode* temp = top;
        char value = top->data;
        top = top->next;
        delete temp;
        return value;
    }
    
    // Просмотр верхнего элемента
    char peek() {
        if (isEmpty()) {
            return '\0';
        }
        return top->data;
    }
    
    // Деструктор
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// Функция для определения приоритета операторов
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Функция преобразования инфиксной записи в постфиксную
string infixToPostfix(const string& infix) {
    Stack st;
    string postfix = "";
    
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        
        // Пропускаем пробелы
        if (ch == ' ') continue;
        
        // Если операнд (буква или цифра), добавляем к результату
        if (isalnum(ch)) {
            postfix += ch;
        }
        // Если открывающая скобка, помещаем в стек
        else if (ch == '(') {
            st.push(ch);
        }
        // Если закрывающая скобка, извлекаем из стека до открывающей
        else if (ch == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                postfix += st.pop();
            }
            st.pop(); // Удаляем открывающую скобку
        }
        // Если оператор
        else {
            // Извлекаем операторы с higher или equal приоритетом
            while (!st.isEmpty() && getPriority(st.peek()) >= getPriority(ch)) {
                postfix += st.pop();
            }
            st.push(ch);
        }
    }
    
    // Извлекаем оставшиеся операторы из стека
    while (!st.isEmpty()) {
        postfix += st.pop();
    }
    
    return postfix;
}

int main() {
    string expression;
    
    cout << "Введите инфиксное выражение: ";
    getline(cin, expression);
    
    string result = infixToPostfix(expression);
    cout << "Постфиксная запись: " << result << endl;
    
   
    
    return 0;
}
