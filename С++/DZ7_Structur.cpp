#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Структура записи справочника
struct Contact {
    string name;
    string phone;
    string email;
    string address;
    void print() const {
        cout << "Name: " << name << ", Phone: " << phone << ", Email: " << email << ", Address: " << address << endl;
    }
};

// Функция сравнения по сложному ключу (например, по имени и фамилии)
bool compareByName(const Contact& a, const Contact& b) {
    return a.name < b.name;
}

// Вывод справочника
void printDirectory(const vector<Contact>& directory) {
    for (const auto& contact : directory) {
        contact.print();
    }
}

int main() {
    // Исходный справочник
    vector<Contact> directory = {
        {"Alice Smith", "7-913-456-7890", "alice2000@yandex.com", "123 Main St"},
        {"Bob Johnson", "7-234-567-8901", "bobaaa@gmail.com", "456 Elm St"},
        {"Charlie Brown", "7-345-678-9012", "charlie@example.com", "789 Oak St"},
        {"David Lee", "7-900-7897--0123", "david228@gmal.com", "101 Pine St"}
    };
    cout << "Исходный справочник:" << endl;
    printDirectory(directory);

    // Сортировка по имени
    sort(directory.begin(), directory.end(), compareByName);
    cout << "\nОтсортированный справочник по имени:" << endl;
    printDirectory(directory);
    return 0;
}
