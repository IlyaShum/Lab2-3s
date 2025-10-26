#include <iostream>
#include <cstring>

using namespace std;

struct HashEntry {
    char key;
    int value;
};

struct HashMap {
    static const int TABLE_SIZE = 256;
    HashEntry table[TABLE_SIZE];
    
    HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].key = '\0';
            table[i].value = -1;
        }
    }
};

int hashFunction(char c) {
    return (unsigned char)c;
}

void put(HashMap& map, char key, int value) {
    int index = hashFunction(key);
    map.table[index].key = key;
    map.table[index].value = value;
}

int get(const HashMap& map, char key) {
    int index = hashFunction(key);
    if (map.table[index].key == key) {
        return map.table[index].value;
    }
    return -1;
}

int lengthOfLongestSubstring(const string& s) {
    HashMap lastSeen;
    int maxLength = 0;
    int left = 0;

    for (int right = 0; right < s.size(); ++right) {
        char currentChar = s[right];

        if (get(lastSeen, currentChar) != -1 && get(lastSeen, currentChar) >= left) {
            left = get(lastSeen, currentChar) + 1;
        }

        put(lastSeen, currentChar, right);

        int currentLength = right - left + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }

    return maxLength;
}

int main() {
    string s;
    cout << "Введите строку: ";
    cin >> s;

    int result = lengthOfLongestSubstring(s);
    cout << "Максимальная длина подстроки без повторяющихся символов: " << result << endl;

    return 0;
}

