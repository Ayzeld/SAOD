#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

int C = 0;
int M = 0;

int C_build = 0;
int M_build = 0;

void FillInc(int n, vector<int>& A) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int n, vector<int>& A) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int n, vector<int>& A) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000;
    }
}

int CheckSum(int n, const vector<int>& A) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

void PrintMas(int n, const vector<int>& A) {
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
}

double calculate_M(int n) {
    return n * log2(n) + 6.5 * n - 4;
}

double calculate_C(int n) {
    return 2 * n * log2(n) + n + 2;
}

double calculate_M_build(int n) {
    return log2(n) + 2;
}

double calculate_C_build(int n) {
    return 2 * log2(n) + 1;
}

void HeapBuild(vector<int>& A, int L, int R) {
    int x = A[L];
    M++;
    M_build++;
    int i = L;
    while (true) {
        int j = 2 * i + 1;
        if (j > R)
            break;

        C++;
        C_build++;
        if (j < R && A[j + 1] > A[j]) {
            j++;
        }

        C++;
        C_build++;
        if (x >= A[j])
            break;

        A[i] = A[j];
        M++;
        M_build++;
        i = j;
    }

    if (i != L) {
        M++;
        M_build++;
    }
    M++;
    M_build++;
    A[i] = x;
}

void HeapSort(vector<int>& A, int n) {
    for (int L = n / 2 - 1; L >= 0; L--) {
        HeapBuild(A, L, n - 1);
    }

    for (int R = n - 1; R > 0; R--) {
        swap(A[0], A[R]);
        M += 3;
        HeapBuild(A, 0, R - 1);
    }
}

void PrintTableHeader() {
    cout << "| " << setw(5) << left << "N"
         << " | " << setw(15) << "M+C теоретич."
         << " | " << setw(41) << "Исходный Mfact + Cfact" << " |\n";
    cout << "|       |               | Убыв.   | Случ.  | Возр.          |\n";
}

void PrintTableRow(int N, int M_C_theoretical, const vector<int>& Mf_Cf_original) {
    cout << "| " << setw(5) << left << N
         << " | " << setw(13) << M_C_theoretical
         << " | " << setw(7) << Mf_Cf_original[0]
         << " | " << setw(6) << Mf_Cf_original[1]
         << " | " << setw(14) << Mf_Cf_original[2] << " |\n";
}

void PrintTableHeader2() {
    cout << "| " << setw(5) << left << "N"
         << " | " << setw(41) << "Исходный Mfact + Cfact" << " |\n";
    cout << "|       | Убыв.   | Случ.  | Возр.          |\n";
}

void PrintTableRow2(int N, const vector<int>& Mf_Cf_original) {
    cout << "| " << setw(5) << left << N
         << " | " << setw(7) << Mf_Cf_original[0]
         << " | " << setw(6) << Mf_Cf_original[1]
         << " | " << setw(14) << Mf_Cf_original[2] << " |\n";
}

int main() {
    srand(time(nullptr));
    vector<int> sizes = {100, 200, 300, 400, 500};

    cout << "Таблица 1: Трудоемкость построения пирамиды\n";
    PrintTableHeader();

    for (int N : sizes) {
        int teor = static_cast<int>(calculate_M_build(N) + calculate_C_build(N));
        vector<int> Mf_Cf_original(3, 0);

        vector<int> ArrDec(N);
        FillDec(N, ArrDec);
        HeapBuild(ArrDec, 0, N - 1);
        Mf_Cf_original[0] = C_build + M_build;
        C_build = M_build = 0;

        vector<int> ArrRand(N);
        FillRand(N, ArrRand);
        HeapBuild(ArrRand, 0, N - 1);
        Mf_Cf_original[1] = C_build + M_build;
        C_build = M_build = 0;

        vector<int> ArrInc(N);
        FillInc(N, ArrInc);
        HeapBuild(ArrInc, 0, N - 1);
        Mf_Cf_original[2] = C_build + M_build;
        C_build = M_build = 0;

        PrintTableRow(N, teor, Mf_Cf_original);
    }

    cout << "\nТаблица 2: Трудоемкость сортировки\n";
    PrintTableHeader2();

    for (int N : sizes) {
        int teor = static_cast<int>(calculate_M(N) + calculate_C(N));
        vector<int> Mf_Cf_original(3, 0);

        vector<int> ArrDec(N);
        FillDec(N, ArrDec);
        HeapSort(ArrDec, N);
        Mf_Cf_original[0] = C + M;
        C = M = 0;

        vector<int> ArrRand(N);
        FillRand(N, ArrRand);
        HeapSort(ArrRand, N);
        Mf_Cf_original[1] = C + M;
        C = M = 0;

        vector<int> ArrInc(N);
        FillInc(N, ArrInc);
        HeapSort(ArrInc, N);
        Mf_Cf_original[2] = C + M;
        C = M = 0;

        PrintTableRow2(N, Mf_Cf_original);
    }

    return 0;
}
