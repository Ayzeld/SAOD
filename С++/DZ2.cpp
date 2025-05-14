#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

// Заполнение массивов
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % 1000;
}

// Пузырьковая сортировка с правильным подсчётом
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

// Вывод таблицы с теоретическими значениями
void PrintTheoreticalTable() {
    std::cout << "\nТЕОРЕТИЧЕСКИЕ ЗНАЧЕНИЯ (M + C):\n";
    std::cout << "+------+---------------+---------------+---------------+\n";
    std::cout << "|  N   |    Min (M=0)  | Средний случай | Max (M=3*C)   |\n";
    std::cout << "+------+---------------+---------------+---------------+\n";
    
    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        double C = (pow(n, 2) - n)/2;
        double M_min = 0;
        double M_avg = 3 * ((pow(n, 2) - n)/4;
        double M_max = 3 * ((pow(n, 2) - n)/2);
        
        std::cout << "| " << std::setw(4) << n << " | " 
                  << std::setw(12) << (C + M_min) << " | "
                  << std::setw(14) << (C + M_avg) << " | "
                  << std::setw(12) << (C + M_max) << " |\n";
        std::cout << "+------+---------------+---------------+---------------+\n";
    }
}

// Вывод таблицы с практическими результатами
void PrintPracticalTable() {
    std::cout << "\nПРАКТИЧЕСКИЕ РЕЗУЛЬТАТЫ (M + C):\n";
    std::cout << "+------+---------------+---------------+---------------+\n";
    std::cout << "|  N   | Возр. (min)  | Случайный      | Убыв. (max)   |\n";
    std::cout << "+------+---------------+---------------+---------------+\n";
    
    int sizes[] = {100, 200, 300, 400, 500};
    for (int n : sizes) {
        int* A = new int[n];
        int C, M;
        
        // Лучший случай (возрастающий)
        FillInc(A, n);
        BubbleSort(A, n, C, M);
        int min = C + M;
        
        // Средний случай (случайный)
        FillRand(A, n);
        BubbleSort(A, n, C, M);
        int avg = C + M;
        
        // Худший случай (убывающий)
        FillDec(A, n);
        BubbleSort(A, n, C, M);
        int max = C + M;
        
        std::cout << "| " << std::setw(4) << n << " | " 
                  << std::setw(12) << min << " | "
                  << std::setw(14) << avg << " | "
                  << std::setw(12) << max << " |\n";
        std::cout << "+------+---------------+---------------+---------------+\n";
        
        delete[] A;
    }
}

int main() {
    srand(time(0));
    
    PrintTheoreticalTable();
    PrintPracticalTable();
    
    return 0;
}
