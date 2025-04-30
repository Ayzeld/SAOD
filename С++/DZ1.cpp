#include <iostream>
#include <cstdlib>
#include <ctime>

// Заполняем массив возрастающими числами
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

// Заполняем массив убывающими числами
void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i - 1;
    }
}

// Заполняем массив случайными числами
void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

// Контрольная сумма
int CheckSum(int A[], int n) {
    int summ = 0;
    for (int i = 0; i < n; i++) {
        summ += A[i];
    }
    return summ;
}

// Считаем серии
int RunNumber(int A[], int n) {
    if (n == 0) return 0;
    int series = 1;
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) {
            series++;
        }
    }
    return series;
}

// Выводим массив
void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

// Сортировка SelectSort
void SelectSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++; // сравнение A[j] и A[minIndex]
            if (A[j] < A[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // 3 пересылки 
            int temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
            moves += 3;
        }
    }
}

int main() {
    const int n = 15;
    int A[n];
    srand(static_cast<unsigned>(time(0)));

    // Возрастающий массив
    std::cout << "Возрастающий массив:" << std::endl;
    FillInc(A, n);
    PrintMas(A,n);
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    // Сортируем и считаем статистику
    int comparisons, moves;
    SelectSort(A, n, comparisons, moves);
    std::cout << "После сортировки SelectSort:" << std::endl;
    PrintMas(A, n);
    std::cout << "Серия: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    std::cout << "Количество сравнений: " << comparisons << std::endl;
    std::cout << "Количество пересылок: " << moves << std::endl;
    std::cout << std::endl;

    // Убывающий массив
    std::cout << "Убывающий массив:" << std::endl;
    FillDec(A, n);
    PrintMas(A, n);
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;

    SelectSort(A, n, comparisons, moves);
    std::cout << "После сортировки SelectSort:" << std::endl;
    PrintMas(A, n);
    std::cout << "Серия: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    std::cout << "Количество сравнений: " << comparisons << std::endl;
    std::cout << "Количество пересылок: " << moves << std::endl;
    std::cout << std::endl;

    // Случайный массив
    std::cout << "Рандомный массив:" << std::endl;
    FillRand(A, n);
    PrintMas(A, n);
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    
    SelectSort(A, n, comparisons, moves);
    std::cout << "После сортировки SelectSort:" << std::endl;
    PrintMas(A, n);
    std::cout << "Серия: " << RunNumber(A, n) << std::endl;
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl;
    std::cout << "Количество сравнений: " << comparisons << std::endl;
    std::cout << "Количество пересылок: " << moves << std::endl;
    std::cout << std::endl;
    return 0;
}
