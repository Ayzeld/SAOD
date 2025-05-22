#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

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

void ShellSort_Knut(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int key = A[i];
            int j = i;
            while (j >= h && A[j - h] > key) {
                comparisons++;
                A[j] = A[j - h];
                swaps++;
                j -= h;
            }
            comparisons++;
            A[j] = key;
            if (j != i) swaps++;
        }
        h = (h - 1) / 3;
    }
}

void PrintTableHeader() {
    cout << "+------+------------------------+------------------------+------------------------+" << endl;
    cout << "|  N   | Shell (Кнут) M+С       | InsertSort M+С         | Shell M+С повторно     |" << endl;
    cout << "+------+------------------------+------------------------+------------------------+" << endl;
}

void PrintTableRow(int n, int shell1_total, int insert_total, int shell2_total) {
    cout << "| " << setw(4) << n << " | "
         << setw(22) << shell1_total << " | "
         << setw(22) << insert_total << " | "
         << setw(22) << shell2_total << " |" << endl;
    cout << "+------+------------------------+------------------------+------------------------+" << endl;
}

int main() {
    const int sizes[] = {100, 200, 300, 400, 500};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(static_cast<unsigned>(time(0)));

    PrintTableHeader();

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* A = new int[n];

        // ShellSort (по Кнуту, первый раз)
        FillRand(A, n);
        int shell1_comp, shell1_swaps;
        ShellSort_Knut(A, n, shell1_comp, shell1_swaps);
        int shell1_total = shell1_comp + shell1_swaps;

        // InsertSort
        FillRand(A, n);
        int insert_comp, insert_swaps;
        InsertSort(A, n, insert_comp, insert_swaps);
        int insert_total = insert_comp + insert_swaps;

        // ShellSort (повторно)
        FillRand(A, n);
        int shell2_comp, shell2_swaps;
        ShellSort_Knut(A, n, shell2_comp, shell2_swaps);
        int shell2_total = shell2_comp + shell2_swaps;

        PrintTableRow(n, shell1_total, insert_total, shell2_total);

        delete[] A;
    }

    return 0;
}
 
