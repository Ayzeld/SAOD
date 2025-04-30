#include <iostream>
#include <cstdlib>
#include <ctime>

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % 100;
}

int CheckSum(int A[], int n) {
    int summ = 0;
    for (int i = 0; i < n; i++) summ += A[i];
    return summ;
}

int RunNumber(int A[], int n) {
    if (n == 0) return 0;
    int series = 1;
     for (int i = 1; i < n; i++) {
        if (A[i] < A[i-1]) series++;
    }
    return series;
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) std::cout << A[i] << " ";
    std::cout << std::endl;
}

// SelectSort
void SelectSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (A[j] < A[minIndex]) minIndex = j;
        }
        // 3 пересылки
        int temp = A[i];
        A[i] = A[minIndex];
        A[minIndex] = temp;
        moves += 3;
    }
}

int main() {
    const int n = 10;
    int A[n];
    srand((unsigned)time(0));
    int comparisons, moves;

    std::cout << "Возрастающий массив: " << std::endl;
    FillInc(A, n);
    PrintMas(A, n);
    std::cout << "Серий до сортировки: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    SelectSort(A, n, comparisons, moves);
    PrintMas(A, n);
    std::cout << "Серий после сортировки: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    std::cout << "Сравнения: " << comparisons << std::endl;
    std::cout << "Переносы: " << moves << std::endl << std::endl;

    std::cout << "Убывающий массив:" << std::endl;
    FillDec(A, n);
    PrintMas(A, n);
    std::cout << "Серий до сортировки: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    SelectSort(A, n, comparisons, moves);
    PrintMas(A, n);
    std::cout << "Серий после сортировки: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    std::cout << "Сравнения: " << comparisons << std::endl;
    std::cout << "Переносы: " << moves << std::endl << std::endl;

    std::cout << "Рандомный массив: " << std::endl;
    FillRand(A, n);
    PrintMas(A, n);
    std::cout << "Серий до сортировки: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    
    SelectSort(A, n, comparisons, moves);
    PrintMas(A, n);
    std::cout << "Серий после сортировки: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    std::cout << "Сравнения: " << comparisons << std::endl;
    std::cout << "Переносы: " << moves << std::endl << std::endl;
    return 0;
}
