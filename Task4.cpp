#include <iostream>
#include <cmath>

using namespace std;

struct IntArray {
    int* data;
    int size;
    
    IntArray() : data(nullptr), size(0) {}
};

void createArray(IntArray& arr, int size) {
    arr.data = new int[size];
    arr.size = size;
}

void printArray(const IntArray& arr) {
    cout << "{";
    for (int i = 0; i < arr.size; i++) {
        cout << (char)arr.data[i]; // Выводим как символ
        if (i < arr.size - 1) {
            cout << ", ";
        }
    }
    cout << "}";
}

void generateSubarrays(const IntArray& input, IntArray*& result, int& resultSize) {
    int n = input.size;
    int totalSubsets = 1 << n; // 2^n
    
    result = new IntArray[totalSubsets];
    resultSize = totalSubsets;
    
    for (int i = 0; i < totalSubsets; i++) {
        createArray(result[i], 0);
        
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                // Расширяем массив
                int newSize = result[i].size + 1;
                int* newData = new int[newSize];
                
                for (int k = 0; k < result[i].size; k++) {
                    newData[k] = result[i].data[k];
                }
                newData[result[i].size] = input.data[j];
                
                delete[] result[i].data;
                result[i].data = newData;
                result[i].size = newSize;
            }
        }
    }
}

void freeArray(IntArray& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    IntArray input;
    createArray(input, n);
    
    cout << "Введите элементы массива (символы): ";
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        input.data[i] = ch;
    }
    
    cout << "Исходный массив: ";
    printArray(input);
    cout << endl;
    
    IntArray* subarrays;
    int subarraysCount;
    generateSubarrays(input, subarrays, subarraysCount);
    
    cout << "Все различные подмассивы (" << subarraysCount << " штук):" << endl;
    cout << "[";
    for (int i = 0; i < subarraysCount; i++) {
        printArray(subarrays[i]);
        if (i < subarraysCount - 1) {
            cout << ", ";
        }
        freeArray(subarrays[i]);
    }
    cout << "]" << endl;
    
    delete[] subarrays;
    freeArray(input);
    
    return 0;
}
