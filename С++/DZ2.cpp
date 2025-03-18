#include <iostream>
#include <cstdlib>
#include <ctime>

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

int CheckSum(int A[], int n) {
    int summ = 0;
    for (int i = 0; i < n; i++) {
        summ += A[i];
    }
    return summ;
}

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

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

void bubbleSort(int A[], int n, int& comparisons, int& swaps) {
    comparisons = 0; // счетчики 
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (A[j] > A[j + 1]) {
                std::swap(A[j], A[j + 1]);
                swaps++;
            }
        }
    }
}

int main() {
    const int n = 15; // Размер массива
    int A[n];
    int M, C; // Переменные для подсчета пересылок и сравнений
    srand(static_cast<unsigned>(time(0))); // Инициализируем генератор случайных чисел

    // Возрастающий массив
    std::cout << "Возрастающий массив: ";
    FillInc(A, n);
    PrintMas(A, n);
    M = C = 0; // Сбрасываем счетчики
    bubbleSort(A, n, M, C);
    std::cout << "После bubbleSort: ";
    PrintMas(A, n);
    std::cout << "Пересылки (M): " << M << ", Сравнения (C): " << C << std::endl;
    std::cout << "Серия: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    // Убывающий массив
    std::cout << "Убывающий массив: ";
    FillDec(A, n);
    PrintMas(A, n);
    M = C = 0; // Сбрасываем счетчики
    bubbleSort(A, n, M, C);
    std::cout << "После bubbleSort: ";
    PrintMas(A, n);
    std::cout << "Пересылки (M): " << M << ", Сравнения (C): " << C << std::endl;
    std::cout << "Серия: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    // Случайный массив
    std::cout << "Рандомный массив: ";
    FillRand(A, n);
    PrintMas(A, n);
    M = C = 0; // Сбрасываем счетчики
    bubbleSort(A, n, M, C);
    std::cout << "После bubbleSort: ";
    PrintMas(A, n);
    std::cout << "Пересылки (M): " << M << ", Сравнения (C): " << C << std::endl;
    std::cout << "Серия: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    return 0; // Возвращаем 0, чтобы указать на успешное выполнение
}
