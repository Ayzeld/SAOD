#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath> // для log2

using namespace std;

// Прототип функции partition (обязательно, т.к. используется в quickSort)
int partition(int A[], int low, int high, int& comparisons, int& swaps);

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

// QuickSort
void quickSort(int A[], int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pi = partition(A, low, high, comparisons, swaps);
        quickSort(A, low, pi - 1, comparisons, swaps);
        quickSort(A, pi + 1, high, comparisons, swaps);
    }
}

int partition(int A[], int low, int high, int& comparisons, int& swaps) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        comparisons++;
        if (A[j] < pivot) {
            i++;
            std::swap(A[i], A[j]);
            swaps += 3; // считаем обмен как 3 пересылки
        }
    }
    std::swap(A[i + 1], A[high]);
    swaps += 3;
    return i + 1;
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
        int quick_comparisons_dec = 0, quick_swaps_dec = 0; // инициализация
        quickSort(A, 0, n - 1, quick_comparisons_dec, quick_swaps_dec);
        int total_quick_dec = quick_comparisons_dec + quick_swaps_dec;

        // Случайный массив
        FillRand(A, n);
        int quick_comparisons_rand = 0, quick_swaps_rand = 0;
        quickSort(A, 0, n - 1, quick_comparisons_rand, quick_swaps_rand);
        int total_quick_rand = quick_comparisons_rand + quick_swaps_rand;

        // Возрастающий массив
        FillInc(A, n);
        int quick_comparisons_inc = 0, quick_swaps_inc = 0;
        quickSort(A, 0, n - 1, quick_comparisons_inc, quick_swaps_inc);
        int total_quick_inc = quick_comparisons_inc + quick_swaps_inc;

        // Теоретическая трудоёмкость, округлённая
        int theoretical_avg = static_cast<int>(n * log2(n));

        // Вывод строки таблицы
        cout << "| " << setw(4) << n << " | "
             << setw(14) << theoretical_avg << " | "
             << setw(5) << total_quick_dec << " | "
             << setw(5) << total_quick_rand << " | "
             << setw(5) << total_quick_inc << " |" << endl;
        cout << "+------+----------------+-------+-------+-------+" << endl;

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
