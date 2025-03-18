#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Заполнение массива возрастающими числами
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

// Заполнение массива убывающими числами
void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i - 1;
    }
}

// Заполнение массива случайными числами
void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

// Подсчёт контрольной суммы
int CheckSum(int A[], int n) {
    int summ = 0;
    for (int i = 0; i < n; i++) {
        summ += A[i];
    }
    return summ;
}

// Подсчёт количества серий
int RunNumber(int A[], int n) {
    if (n <= 1) {
        return n;
    }
    int series = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] != A[i - 1]) {
            series++;
        }
    }
    return series;
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

// Вывод массива
void PrintArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    const int n = 15;
    int A[n];
    int comparisons, swaps;
    srand(time(NULL));

    // Возрастающий массив
    cout << "Возрастающий массив: ";
    FillInc(A, n);
    PrintArray(A, n);
    InsertSort(A, n, comparisons, swaps);
    cout << "Отсортированный массив: ";
    PrintArray(A, n);
    cout << "Сравнения: " << comparisons << ", Пересылки: " << swaps << endl;
    cout << "Серия: " << RunNumber(A, n) << endl;
    cout << "Контрольная сумма: " << CheckSum(A, n) << endl;

    // Убывающий массив
    cout << "Убывающий массив: ";
    FillDec(A, n);
    PrintArray(A, n);
    InsertSort(A, n, comparisons, swaps);
    cout << "Отсортированный массив: ";
    PrintArray(A, n);
    cout << "Сравнения: " << comparisons << ", Пересылки: " << swaps << endl;
    cout << "Серия: " << RunNumber(A, n) << endl;
    cout << "Контрольная сумма: " << CheckSum(A, n) << endl;

    // Случайный массив
    cout << "Случайный массив: ";
    FillRand(A, n);
    PrintArray(A, n);
    InsertSort(A, n, comparisons, swaps);
    cout << "Отсортированный массив: ";
    PrintArray(A, n);
    cout << "Сравнения: " << comparisons << ", Пересылки: " << swaps << endl;
    cout << "Серия: " << RunNumber(A, n) << endl;
    cout << "Контрольная сумма: " << CheckSum(A, n) << endl;

    return 0;
}
