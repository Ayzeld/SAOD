#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % 100;
}

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

void ShakerSort(int A[], int n, int& M, int& C) {  // <- здесь изменил на int& C
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

void PrintTable() {
    std::cout << "+------+-------+-------+-------+--------+--------+-------+\n";
    std::cout << "|  N   | Убыв. | Случ. | Возр. | Убыв.  | Случ.  | Возр. |\n";
    std::cout << "+------+-------+-------+-------+--------+--------+-------+\n";

    int sizes[] = {100, 200, 300, 400, 500};

    for (int n : sizes) {
        int* A = new int[n];

        int M_bubble, C_bubble;
        int M_shaker, C_shaker;

        // Пузырьковая сортировка
        FillDec(A, n);
        BubbleSort(A, n, M_bubble, C_bubble);
        int dec_bubble = M_bubble + C_bubble;

        FillRand(A, n);
        BubbleSort(A, n, M_bubble, C_bubble);
        int rand_bubble = M_bubble + C_bubble;

        FillInc(A, n);
        BubbleSort(A, n, M_bubble, C_bubble);
        int inc_bubble = M_bubble + C_bubble;

        // Шейкерная сортировка
        FillDec(A, n);
        ShakerSort(A, n, M_shaker, C_shaker);
        int dec_shaker = M_shaker + C_shaker;

        FillRand(A, n);
        ShakerSort(A, n, M_shaker, C_shaker);
        int rand_shaker = M_shaker + C_shaker;

        FillInc(A, n);
        ShakerSort(A, n, M_shaker, C_shaker);
        int inc_shaker = M_shaker + C_shaker;

        std::cout << "| " << std::setw(4) << n << " | "
                  << std::setw(5) << dec_bubble << " | "
                  << std::setw(5) << rand_bubble << " | "
                  << std::setw(5) << inc_bubble << " | "
                  << std::setw(6) << dec_shaker << " | "
                  << std::setw(6) << rand_shaker << " | "
                  << std::setw(5) << inc_shaker << " |\n";

        std::cout << "+------+-------+-------+-------+--------+--------+-------+\n";

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
