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

void ShakerSort(int A[], int n, int& M, int C) {
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
    std::cout << "+------+-----------------------+-------------------------+\n";
    std::cout << "|  N   |     Пузырьковая       |      Шейкерная          |\n";
    std::cout << "|      | Убыв. | Случ. | Возр. | Убыв.  | Случ.  | Возр. |\n";
    std::cout << "+------+-------+-------+-------+--------+--------+-------+\n";

    int sizes[] = {100, 200, 300, 400, 500};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int n : sizes) {
        int* A = new int[n];

        int M_bubble, C_bubble;
        int M_shaker, C_shaker;

        // Пузырьковая
        // Убывающий
        FillDec(A, n);
        BubbleSort(A, n, M_bubble, C_bubble);
        int dec_bubble = M_bubble + C_bubble;

        // Случайный
        FillRand(A, n);
        BubbleSort(A, n, M_bubble, C_bubble);
        int rand_bubble = M_bubble + C_bubble;

        // Возрастающий
        FillInc(A, n);
        BubbleSort(A, n, M_bubble, C_bubble);
        int inc_bubble = M_bubble + C_bubble;

        // Шейкерная
        // Убывающий
        FillDec(A, n);
        ShakerSort(A, n, M_shaker, C_shaker);
        int dec_shaker = M_shaker + C_shaker;

        // Случайный
        FillRand(A, n);
        ShakerSort(A, n, M_shaker, C_shaker);
        int rand_shaker = M_shaker + C_shaker;

        // Возрастающий
        FillInc(A, n);
        ShakerSort(A, n, M_shaker, C_shaker);
        int inc_shaker = M_shaker + C_shaker;

        std::cout << "| " << std::setw(4) << n << " | "
                  << std::setw(5) << dec_bubble << " | "
                  << std::setw(5) << rand_bubble << " | "
                  << std::setw(5) << inc_bubble << " | "
                  << std::setw(5) << dec_shaker << " | "
                  << std::setw(5) << rand_shaker << " | "
                  << std::setw(5) << inc_shaker << " |" << std::endl;

        std::cout << "+------+-------+-------+-------+------------+------------+----------+\n";

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
