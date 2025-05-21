#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

// Сортировка выбором
void SelectSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (A[j] < A[minIndex]) minIndex = j;
        }
        // Обмен элементами
        int temp = A[i];
        A[i] = A[minIndex];
        A[minIndex] = temp;
        moves += 3; // Записываем все перемещения
    }
}

// Пузырьковая сортировка
void BubbleSort(int A[], int n, int& M, int& C) {
    M = 0;
    C = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            C++; // сравнение
            if (A[j] > A[j + 1]) {
                std::swap(A[j], A[j + 1]);
                M += 3; // три пересылки при обмене
            }
        }
    }
}

// Шейкерная сортировка
void ShakerSort(int A[], int n, int& M, int& C) {
    int left = 0, right = n - 1;
    bool swapped = true;
    M = 0;
    C = 0;
    while (left < right && swapped) {
        swapped = false;
        for (int i = left; i < right; i++) {
            C++;
            if (A[i] > A[i + 1]) {
                std::swap(A[i], A[i + 1]);
                M += 3;
                swapped = true;
            }
        }
        right--;
        if (!swapped) break;
        swapped = false;
        for (int i = right; i > left; i--) {
            C++;
            if (A[i] < A[i - 1]) {
                std::swap(A[i], A[i - 1]);
                M += 3;
                swapped = true;
            }
        }
        left++;
    }
}

// Сортировка вставками
void InsertSort(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            comparisons++;
            A[j + 1] = A[j];
            swaps++;
            j--;
        }
        comparisons++;
        A[j + 1] = key;
        if (j + 1 != i) {
            swaps++;
        }
    }
}

// Вывод заголовка таблицы
void PrintTableHeader() {
    cout << "+------+----------------+----------------+----------------+----------------+" << endl;
    cout << "|  N   |     Select     |     Bubble     |     Shaker     |     Insert     |" << endl;
    cout << "|      | Mфакт+Сфакт    | Mфакт+Сфакт    | Mфакт+Сфакт    | Mфакт+Сфакт    |" << endl;
    cout << "+------+----------------+----------------+----------------+----------------+" << endl;
}

// Вывод строки таблицы
void PrintTableRow(int n, int select_total, int bubble_total, int shaker_total, int insert_total) {
    cout << "| " << setw(4) << n << " | "
         << setw(14) << select_total << " | "
         << setw(14) << bubble_total << " | "
         << setw(14) << shaker_total << " | "
         << setw(14) << insert_total << " |" << endl;
    cout << "+------+----------------+----------------+----------------+----------------+" << endl;
}

int main() {
    const int sizes[] = {100, 200, 300, 400, 500};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(static_cast<unsigned>(time(0)));
    PrintTableHeader();

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* A = new int[n];

        // Создаем случайный массив
        FillRand(A, n);

        // Сортировка выбором
        int select_comparisons, select_moves;
        SelectSort(A, n, select_comparisons, select_moves);
        int select_total = select_comparisons + select_moves;

        // Сортировка пузырьком
        FillRand(A, n); // Перезаполняем массив
        int bubble_M, bubble_C;
        BubbleSort(A, n, bubble_M, bubble_C);
        int bubble_total = bubble_M + bubble_C;

        // Шейкерная сортировка
        FillRand(A, n); // Перезаполняем массив
        int shaker_M, shaker_C;
        ShakerSort(A, n, shaker_M, shaker_C);
        int shaker_total = shaker_M + shaker_C;

        // Сортировка вставками
        FillRand(A, n); // Перезаполняем массив
        int insert_comparisons, insert_swaps;
        InsertSort(A, n, insert_comparisons, insert_swaps);
        int insert_total = insert_comparisons + insert_swaps;

        // Вывод результата
        PrintTableRow(n, select_total, bubble_total, shaker_total, insert_total);
        delete[] A;
    }
    return 0;
}
