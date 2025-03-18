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

int main() { 
    const int n = 15;
    int A[n]; 
    srand(static_cast<unsigned>(time(0))); // Инициализируем генератор

    std::cout << "Возрастающий массив: "; 
    FillInc(A, n); 
    PrintMas(A, n); 
    std::cout << "Серия: " << RunNumber(A, n) << std::endl; 
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl; 
    std::cout << "Убывающий массив: "; 
    FillDec(A, n); 
    PrintMas(A, n); 
    std::cout << "Серия: " << RunNumber(A, n) << std::endl; 
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl; 
    std::cout << "Рандомный массив: "; 
    FillRand(A, n);
    PrintMas(A, n); 
    std::cout << "Серия: " << RunNumber(A, n) << std::endl; 
    std::cout << "Контрольная сумма: " << CheckSum(A, n) << std::endl; 
    return 0; 
}
