#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Итеративная версия 
int BinarySearchIterative(int A[], int n, int key) {
    int comparisons = 0;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (A[mid] == key) {
            return comparisons + 1;
        } else if (A[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return comparisons + 1;
}

// Рекурсивная версия 
int BinarySearchRecursive(int A[], int left, int right, int key, int& comparisons) {
    if (left > right) return comparisons + 1; 
    int mid = left + (right - left) / 2;
    comparisons++;
    if (A[mid] == key) {
        return comparisons + 1;
    } else if (A[mid] < key) {
        return BinarySearchRecursive(A, mid + 1, right, key, comparisons);
    } else {
        return BinarySearchRecursive(A, left, mid - 1, key, comparisons);
    }
}

// Вывод таблицы 
void PrintTable() {
    cout << "+------+----------------+----------------+" << endl;
    cout << "|  N   | Сф I версия    | Сф II версия   |" << endl;
    cout << "+------+----------------+----------------+" << endl;
    for (int n = 100; n <= 1000; n += 100) {
        int* A = new int[n];
        for (int i = 0; i < n; i++) {
            A[i] = i;
        }

        int key = A[n / 2];
        int comp_iter = BinarySearchIterative(A, n, key);
        int comp_recur = 0;
        comp_recur = BinarySearchRecursive(A, 0, n - 1, key, comp_recur); 

        cout << "| " << setw(4) << n << " | "
             << setw(14) << comp_iter << " | "
             << setw(14) << comp_recur << " |" << endl;

        delete[] A;
    }
    cout << "+------+----------------+----------------+" << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
