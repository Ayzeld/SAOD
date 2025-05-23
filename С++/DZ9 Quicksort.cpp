#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

int C = 0; // Счётчик сравнений
int M = 0; // Счётчик пересылок

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000;
    }
}

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    M += 3; // как в C-коде
}

int Partition(int A[], int L, int R) {
    int x = A[L];
    int i = L;
    int j = R;

    while (true) {
        while (A[i] < x) { C++; i++; }
        C++;
        while (A[j] > x) { C++; j--; }
        C++;

        if (i < j) {
            Swap(A[i], A[j]);
            i++;
            j--;
        } else {
            return j;
        }
    }
}

void QuickSort(int A[], int L, int R) {
    if (L < R) {
        int q = Partition(A, L, R);
        QuickSort(A, L, q);
        QuickSort(A, q + 1, R);
    }
}

void PrintTable() {
    cout << "|  N   | Убыв.   | Возр.   | Случ.           |" << endl;
    cout << "+------+---------+---------+------------------+" << endl;

    int sizes[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int* A = new int[n];
        int result_dec = 0, result_inc = 0, result_rand = 0;

        // Убывающий
        FillDec(A, n);
        C = M = 0;
        QuickSort(A, 0, n - 1);
        result_dec = C + M;

        // Возрастающий
        FillInc(A, n);
        C = M = 0;
        QuickSort(A, 0, n - 1);
        result_inc = C + M;

        // Случайный
        FillRand(A, n);
        C = M = 0;
        QuickSort(A, 0, n - 1);
        result_rand = C + M;

        // Печать строки
        cout << "| " << setw(4) << n << " | "
             << setw(7) << result_dec << " | "
             << setw(7) << result_inc << " | "
             << setw(16) << result_rand << " |" << endl;

        delete[] A;
    }
    cout << "+------+---------+---------+------------------+" << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
