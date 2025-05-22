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

// Построение кучи
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

// HeapSort
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

// Вывод таблицы
void PrintTable() {
    cout << "+------+----------------+-------+-------+-------+" << endl;
    cout << "|  N   | M+C теоретич.  | Убыв. | Случ. | Возр. |" << endl;
    cout << "+------+----------------+-------+-------+-------+" << endl;

    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        int* A = new int[n];

        // Убывающий массив
        FillDec(A, n);
        int heap_comparisons_dec = 0, heap_swaps_dec = 0;
        HeapSort(A, n, heap_comparisons_dec, heap_swaps_dec);
        int total_heap_dec = heap_comparisons_dec + heap_swaps_dec;

        // Случайный массив
        FillRand(A, n);
        int heap_comparisons_rand = 0, heap_swaps_rand = 0;
        HeapSort(A, n, heap_comparisons_rand, heap_swaps_rand);
        int total_heap_rand = heap_comparisons_rand + heap_swaps_rand;

        // Возрастающий массив
        FillInc(A, n);
        int heap_comparisons_inc = 0, heap_swaps_inc = 0;
        HeapSort(A, n, heap_comparisons_inc, heap_swaps_inc);
        int total_heap_inc = heap_comparisons_inc + heap_swaps_inc;

        // Теоретическая трудоёмкость
        int theoretical_avg = static_cast<int>(n * log2(n) + 6.5 * n - 4);

        // Вывод строки таблицы
        cout << "| " << setw(4) << n << " | "
             << setw(14) << theoretical_avg << " | "
             << setw(5) << total_heap_dec << " | "
             << setw(5) << total_heap_rand << " | "
             << setw(5) << total_heap_inc << " |" << endl;
        cout << "+------+----------------+-------+-------+-------+" << endl;

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
