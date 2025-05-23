#include <iostream>
#include <iomanip>
using namespace std;

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void InsertSort(int A[], int n, int& M, int& C) {
    M = 0;
    C = 0;
    for (int i = 1; i < n; i++) {
        int key = A[i];
        M++;
        int j = i - 1;
        while (j >= 0 && (++C, A[j] > key)) {
            A[j + 1] = A[j];
            M++;
            j--;
        }
        A[j + 1] = key;
        M++;
    }
}

// Shell по Кнуту
void ShellSort_Knut(int A[], int n, int& C, int& M) {
    C = 0;
    M = 0;
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int key = A[i];
            M++;
            int j = i;
            while (j >= h && (++C, A[j - h] > key)) {
                A[j] = A[j - h];
                M++;
                j -= h;
            }
            A[j] = key;
            M++;
        }
        h = (h - 1) / 3;
    }
}

// Shell из C-кода: шаги h = 1, 3, 7, 15, ...
void ShellSort_C(int A[], int n, int& C, int& M) {
    C = 0;
    M = 0;
    int B[30], l = 1;
    B[0] = 1;
    while (B[l - 1] < n / 2) {
        B[l] = B[l - 1] * 2 + 1;
        l++;
    }
    for (int s = l - 1; s >= 0; s--) {
        int k = B[s];
        for (int i = k; i < n; i++) {
            int t = A[i];
            M++;
            int j = i - k;
            while (j >= 0 && (++C, t < A[j])) {
                A[j + k] = A[j];
                M++;
                j -= k;
            }
            A[j + k] = t;
            M++;
        }
    }
}

void PrintTableHeader() {
    cout << "+------+------------------------+------------------------+------------------------+" << endl;
    cout << "|  N   | Shell (Кнут) M+С       | InsertSort M+С         | Shell M+С              |" << endl;
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
    int sizes[] = {100, 200, 300, 400, 500};

    PrintTableHeader();
    for (int i = 0; i < 5; i++) {
        int n = sizes[i];
        int* A = new int[n];
        int M, C;

        // Shell по Кнуту (возрастающий)
        FillInc(A, n);
        ShellSort_Knut(A, n, C, M);
        int shell1_total = C + M;

        // Вставками (убывающий)
        FillDec(A, n);
        InsertSort(A, n, M, C);
        int insert_total = C + M;

        // Shell из C-кода (возрастающий)
        FillInc(A, n);
        ShellSort_C(A, n, C, M);
        int shell2_total = C + M;

        PrintTableRow(n, shell1_total, insert_total, shell2_total);
        delete[] A;
    }

    return 0;
}
