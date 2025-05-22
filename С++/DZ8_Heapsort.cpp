#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath> // для log2

using namespace std;

// Функции заполнения массива
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i - 1;
    }
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

// Построение кучи с подсчётом сравнений и обменов
void heapify(int A[], int n, int i, int& comparisons, int& swaps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparisons++;
        if (A[left] > A[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        comparisons++;
        if (A[right] > A[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        std::swap(A[i], A[largest]);
        swaps += 3; // считаем обмен как 3 присваивания
        heapify(A, n, largest, comparisons, swaps);
    }
}

// Функция только построения кучи (трудоёмкость построения пирамиды)
void BuildHeap(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, comparisons, swaps);
    }
}

// Полная сортировка кучей (BuildHeap + сортировка)
void HeapSort(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    // Построение кучи
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, comparisons, swaps);
    }

    // Извлечение элементов из кучи
    for (int i = n - 1; i > 0; i--) {
        std::swap(A[0], A[i]);
        swaps += 3;
        heapify(A, i, 0, comparisons, swaps);
    }
}

// Вывод таблицы с построением кучи
void PrintBuildHeapTable() {
    cout << "Таблица 1: Трудоёмкость построения кучи (BuildHeap)\n";
    cout << "+------+--------------+-------+-------+-------+\n";
    cout << "|  N   |  Теоретич.  | Убыв. | Случ. | Возр. |\n";
    cout << "+------+--------------+-------+-------+-------+\n";

    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        int* A = new int[n];

        FillDec(A, n);
        int comp_dec = 0, swaps_dec = 0;
        BuildHeap(A, n, comp_dec, swaps_dec);
        int total_dec = comp_dec + swaps_dec;

        FillRand(A, n);
        int comp_rand = 0, swaps_rand = 0;
        BuildHeap(A, n, comp_rand, swaps_rand);
        int total_rand = comp_rand + swaps_rand;

        FillInc(A, n);
        int comp_inc = 0, swaps_inc = 0;
        BuildHeap(A, n, comp_inc, swaps_inc);
        int total_inc = comp_inc + swaps_inc;

        int theoretical = static_cast<int>(n * log2(n) + 6.5 * n - 4);

        cout << "| " << setw(4) << n << " | "
             << setw(12) << theoretical << " | "
             << setw(5) << total_dec << " | "
             << setw(5) << total_rand << " | "
             << setw(5) << total_inc << " |\n";
        cout << "+------+--------------+-------+-------+-------+\n";

        delete[] A;
    }
}

// Вывод таблицы с полной сортировкой
void PrintHeapSortTable() {
    cout << "\nТаблица 2: Трудоёмкость полной сортировки (HeapSort)\n";
    cout << "+------+--------------+-------+-------+-------+\n";
    cout << "|  N   |  Теоретич.  | Убыв. | Случ. | Возр. |\n";
    cout << "+------+--------------+-------+-------+-------+\n";

    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        int* A = new int[n];

        FillDec(A, n);
        int comp_dec = 0, swaps_dec = 0;
        HeapSort(A, n, comp_dec, swaps_dec);
        int total_dec = comp_dec + swaps_dec;

        FillRand(A, n);
        int comp_rand = 0, swaps_rand = 0;
        HeapSort(A, n, comp_rand, swaps_rand);
        int total_rand = comp_rand + swaps_rand;

        FillInc(A, n);
        int comp_inc = 0, swaps_inc = 0;
        HeapSort(A, n, comp_inc, swaps_inc);
        int total_inc = comp_inc + swaps_inc;

        int theoretical = static_cast<int>(n * log2(n) + 6.5 * n - 4);

        cout << "| " << setw(4) << n << " | "
             << setw(12) << theoretical << " | "
             << setw(5) << total_dec << " | "
             << setw(5) << total_rand << " | "
             << setw(5) << total_inc << " |\n";
        cout << "+------+--------------+-------+-------+-------+\n";

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    PrintBuildHeapTable();
    PrintHeapSortTable();

    return 0;
}
