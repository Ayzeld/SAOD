#include <iostream>
#include <cstdlib>
#include <ctime>
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

// Вывод таблицы
void PrintTableHeader() {
    cout << "+------+----------------+---------------------+" << endl;
    cout << "|  N   | M+C теоретич.  | Mфакт+Сфакт         |" << endl;
    cout << "|      |                | Убыв. | Случ. | Возр. |" << endl;
    cout << "+------+----------------+-------+-------+-------+" << endl;
}

void PrintTableRow(int n, int theoretical, int dec_fact, int rand_fact, int inc_fact) {
    cout << "| " << setw(4) << n << " | "
         << setw(14) << theoretical << " | "
         << setw(5) << dec_fact << " | "
         << setw(5) << rand_fact << " | "
         << setw(5) << inc_fact << " |" << endl;
    cout << "+------+----------------+-------+-------+-------+" << endl;
}

int main() {
    const int sizes[] = {100, 200, 300, 400, 500};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));
    PrintTableHeader();

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* A = new int[n];

        // Теоретическое значение
        int theoretical_min = 3 * (n - 1); // Для возрастающего массива
        int theoretical_max = n * n + n - 2; // Для убывающего массива
        int theoretical_avg = (n * n - n) / 2 + n - 1; // Для случайного массива

        // Для убывающего массива
        FillDec(A, n);
        int comparisons_dec, swaps_dec;
        InsertSort(A, n, comparisons_dec, swaps_dec);
        int fact_dec = comparisons_dec + swaps_dec;

        // Для случайного массива
        FillRand(A, n);
        int comparisons_rand, swaps_rand;
        InsertSort(A, n, comparisons_rand, swaps_rand);
        int fact_rand = comparisons_rand + swaps_rand;

        // Для возрастающего массива
        FillInc(A, n);
        int comparisons_inc, swaps_inc;
        InsertSort(A, n, comparisons_inc, swaps_inc);
        int fact_inc = comparisons_inc + swaps_inc;

        // Вывод строки таблицы
        PrintTableRow(n, theoretical_avg, fact_dec, fact_rand, fact_inc);
        delete[] A;
    }
    return 0;
}
