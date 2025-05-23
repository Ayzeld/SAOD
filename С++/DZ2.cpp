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
    for (int i = 0; i < n; i++) A[i] = rand() % 1000;
}

void BubbleSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (A[j] > A[j + 1]) {
                // 3 пересылки при обмене
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                moves += 3;
            }
        }
    }
}

void PrintTable() {
    std::cout << "+------+----------------+---------------------+" << std::endl;
    std::cout << "|  N   | M+C теоретич.  |    Мфакт+Сфакт      |" << std::endl;
    std::cout << "|      |                | Убыв. | Случ. | Возр. |" << std::endl;
    std::cout << "+------+----------------+-------+-------+-------+" << std::endl;

    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        int* A = new int[n];
        int C, M;
        
        // Теоретическое значение для худшего случая (M = 3C)
        int theoretical = 2 * ((n*n - n)/2); // C + M = C + 3C = 4C, но формула требует уточнения
        
        // Убывающий (максимальные M+C)
        FillDec(A, n);
        BubbleSort(A, n, C, M);
        int dec_total = C + M;
        
        // Случайный
        FillRand(A, n);
        BubbleSort(A, n, C, M);
        int rand_total = C + M;
        
        // Возрастающий (минимальные M+C)
        FillInc(A, n);
        BubbleSort(A, n, C, M);
        int inc_total = C + M;

        std::cout << "| " << std::setw(4) << n << " | " 
                  << std::setw(14) << (3 * (((n*n) - n)/4) + ((n*n) - n)/2) << " | "
                  << std::setw(5) << dec_total << " | "
                  << std::setw(5) << rand_total << " | "
                  << std::setw(5) << inc_total << " |" << std::endl;
        std::cout << "+------+----------------+-------+-------+-------+" << std::endl;

        delete[] A;
    }
}

int main() {
    srand(time(0));
    PrintTable();
    return 0;
}
