#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

// Функции заполнения массива
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

// Построение кучи с подсчётом сравнений и обменов
void heapify(int A[], int n, int i, int& comparisons, int& swaps) {
    int x = A[i];
    swaps++;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    while (true) {
        int j = 2 * largest + 1;
        if (j >= n)
            break;

        comparisons++;
        if (j + 1 < n && A[j + 1] > A[j]) {
            j++;
        }

        comparisons++;
        if (x >= A[j])
            break;

        A[largest] = A[j];
        swaps++;
        largest = j;
    }

    if (largest != i) {
        swaps++;
    }
    A[largest] = x;
    swaps++;
}

// Построение кучи
void BuildHeap(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, comparisons, swaps);
    }
}

// Полная сортировка кучей
void HeapSort(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, comparisons, swaps);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = A[0]; swaps++;
        A[0] = A[i]; swaps++;
        A[i] = temp; swaps++;

        heapify(A, i, 0, comparisons, swaps);
    }
}

int TheoreticalBuild(int n) {
    return static_cast<int>(log2(n) + 2 + 2 * log2(n) + 1);
}

int TheoreticalSort(int n) {
    return static_cast<int>(n * log2(n) + 6.5 * n - 4 + 2 * n * log2(n) + n + 2);
}

// Таблица построения кучи
void PrintBuildHeapTable() {
    cout << "Таблица 1: Трудоёмкость построения кучи (BuildHeap)\n";
    cout << "+------+--------------+--------+--------+--------+\n";
    cout << "|  N   | Теоретич.   | Убыв.  | Случ.  | Возр.  |\n";
    cout << "+------+--------------+--------+--------+--------+\n";

    int sizes[] = {100, 200, 300, 400, 500};

    for (int n : sizes) {
        int* A = new int[n];

        int comp = 0, swp = 0;

        FillDec(A, n);
        BuildHeap(A, n, comp, swp);
        int total_dec = comp + swp;

        FillRand(A, n);
        BuildHeap(A, n, comp, swp);
        int total_rand = comp + swp;

        FillInc(A, n);
        BuildHeap(A, n, comp, swp);
        int total_inc = comp + swp;

        int theoretical = static_cast<int>(log2(n) + 2 + 2 * log2(n) + 1);

        cout << "| " << setw(4) << n << " | "
             << setw(12) << theoretical << " | "
             << setw(6) << total_dec << " | "
             << setw(6) << total_rand << " | "
             << setw(6) << total_inc << " |\n";
        cout << "+------+--------------+--------+--------+--------+\n";

        delete[] A;
    }
}

// Таблица полной сортировки
void PrintHeapSortTable() {
    cout << "\nТаблица 2: Трудоёмкость полной сортировки (HeapSort)\n";
    cout << "+------+--------------+--------+--------+--------+\n";
    cout << "|  N   | Теоретич.   | Убыв.  | Случ.  | Возр.  |\n";
    cout << "+------+--------------+--------+--------+--------+\n";

    int sizes[] = {100, 200, 300, 400, 500};

    for (int n : sizes) {
        int* A = new int[n];

        int comp = 0, swp = 0;

        FillDec(A, n);
        HeapSort(A, n, comp, swp);
        int total_dec = comp + swp;

        FillRand(A, n);
        HeapSort(A, n, comp, swp);
        int total_rand = comp + swp;

        FillInc(A, n);
        HeapSort(A, n, comp, swp);
        int total_inc = comp + swp;

        int theoretical = static_cast<int>(n * log2(n) + 6.5 * n - 4 + 2 * n * log2(n) + n + 2);

        cout << "| " << setw(4) << n << " | "
             << setw(12) << theoretical << " | "
             << setw(6) << total_dec << " | "
             << setw(6) << total_rand << " | "
             << setw(6) << total_inc << " |\n";
        cout << "+------+--------------+--------+--------+--------+\n";

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    PrintBuildHeapTable();
    PrintHeapSortTable();

    return 0;
}
