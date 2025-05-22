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
        int temp = A[i];
        A[i] = A[minIndex];
        A[minIndex] = temp;
        moves += 3;
    }
}

// Пузырьковая сортировка
void BubbleSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
                moves += 3;
            }
        }
    }
}

// Шейкерная сортировка
void ShakerSort(int A[], int n, int& comparisons, int& moves) {
    int left = 0, right = n - 1;
    bool swapped = true;
    comparisons = 0;
    moves = 0;
    while (left < right && swapped) {
        swapped = false;
        for (int i = left; i < right; i++) {
            comparisons++;
            if (A[i] > A[i + 1]) {
                swap(A[i], A[i + 1]);
                moves += 3;
                swapped = true;
            }
        }
        right--;
        if (!swapped) break;
        swapped = false;
        for (int i = right; i > left; i--) {
            comparisons++;
            if (A[i] < A[i - 1]) {
                swap(A[i], A[i - 1]);
                moves += 3;
                swapped = true;
            }
        }
        left++;
    }
}

// Вывод таблицы 1
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

// Таблица 2: сравнение всех сортировок
void PrintSortsHeader() {
    cout << "\n+------+--------------------+--------------------+--------------------+--------------------+" << endl;
    cout << "|  N   |   SelectSort      |   BubbleSort       |   ShakerSort       |   InsertSort       |" << endl;
    cout << "|      |      Mф+Сф        |      Mф+Сф         |      Mф+Сф         |      Mф+Сф         |" << endl;
    cout << "+------+--------------------+--------------------+--------------------+--------------------+" << endl;
}

void PrintSortsRow(int n, int sel_total, int bub_total, int shak_total, int ins_total) {
    cout << "| " << setw(4) << n << " | "
         << setw(18) << sel_total << " | "
         << setw(18) << bub_total << " | "
         << setw(18) << shak_total << " | "
         << setw(18) << ins_total << " |" << endl;
    cout << "+------+--------------------+--------------------+--------------------+--------------------+" << endl;
}

int main() {
    const int sizes[] = {100, 200, 300, 400, 500};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));

    PrintTableHeader();
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* A = new int[n];

        int theoretical_avg = (n * n - n) / 2 + n - 1;

        FillDec(A, n);
        int comparisons_dec, swaps_dec;
        InsertSort(A, n, comparisons_dec, swaps_dec);
        int fact_dec = comparisons_dec + swaps_dec;

        FillRand(A, n);
        int comparisons_rand, swaps_rand;
        InsertSort(A, n, comparisons_rand, swaps_rand);
        int fact_rand = comparisons_rand + swaps_rand;

        FillInc(A, n);
        int comparisons_inc, swaps_inc;
        InsertSort(A, n, comparisons_inc, swaps_inc);
        int fact_inc = comparisons_inc + swaps_inc;

        PrintTableRow(n, theoretical_avg, fact_dec, fact_rand, fact_inc);

        delete[] A;
    }

    PrintSortsHeader();
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* A = new int[n];

        int comparisons, moves;

        FillRand(A, n);
        SelectSort(A, n, comparisons, moves);
        int select_total = comparisons + moves;

        FillRand(A, n);
        BubbleSort(A, n, comparisons, moves);
        int bubble_total = comparisons + moves;

        FillRand(A, n);
        ShakerSort(A, n, comparisons, moves);
        int shaker_total = comparisons + moves;

        FillRand(A, n);
        InsertSort(A, n, comparisons, moves);
        int insert_total = comparisons + moves;

        PrintSortsRow(n, select_total, bubble_total, shaker_total, insert_total);
        delete[] A;
    }
    return 0;
}
