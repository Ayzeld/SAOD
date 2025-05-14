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
                M += 3; // 3 пересылки на каждый обмен
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
                M += 3; // 3 пересылки на каждый обмен
                swapped = true;
            }
        }
        left++;
    }
}

void PrintTable() {
    std::cout << "+------+---------------------+" << std::endl;
    std::cout << "|  N   |    Мфакт+Сфакт      |" << std::endl;
    std::cout << "|      | Убыв. | Случ. | Возр. |" << std::endl;
    std::cout << "+------+-------+-------+-------+" << std::endl;

    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        int* A = new int[n];
        int M, C;
        
        // Убывающий (максимальные M+C)
        FillDec(A, n);
        ShakerSort(A, n, M, C);
        int dec_total = M + C;
        
        // Случайный
        FillRand(A, n);
        ShakerSort(A, n, M, C);
        int rand_total = M + C;
        
        // Возрастающий (минимальные M+C)
        FillInc(A, n);
        ShakerSort(A, n, M, C);
        int inc_total = M + C;

        std::cout << "| " << std::setw(4) << n << " | " 
                  << std::setw(5) << dec_total << " | "
                  << std::setw(5) << rand_total << " | "
                  << std::setw(5) << inc_total << " |" << std::endl;
        std::cout << "+------+-------+-------+-------+" << std::endl;

        delete[] A;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    PrintTable();
    return 0;
}
