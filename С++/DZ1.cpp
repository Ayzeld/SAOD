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

void PrintTableHeader() {
    std::cout << "+------+----------------+---------------------+" << std::endl;
    std::cout << "|  N   | M+C теоретич.  | Исходный Мфакт+Сфакт |" << std::endl;
    std::cout << "|      |                | Убыв. | Случ. | Возр. |" << std::endl;
    std::cout << "+------+----------------+-------+-------+-------+" << std::endl;
}

void PrintTableRow(int n, int theoretical, int dec, int rand, int inc) {
    std::cout << "| " << std::setw(4) << n << " | " 
              << std::setw(14) << theoretical << " | " 
              << std::setw(5) << dec << " | " 
              << std::setw(5) << rand << " | " 
              << std::setw(5) << inc << " |" << std::endl;
    std::cout << "+------+----------------+-------+-------+-------+" << std::endl;
}

int main() {
    const int sizes[] = {10, 100};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    srand((unsigned)time(0));
    
    PrintTableHeader();
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* A = new int[n];
        
        // Теоретическое значение M+C для сортировки выбором: n²/2 - n/2 + 3(n-1)
        int theoretical = (n*n)/2 - n/2 + 3*(n-1);
        
        // Для возрастающего массива
        FillInc(A, n);
        int inc_comparisons, inc_moves;
        SelectSort(A, n, inc_comparisons, inc_moves);
        int inc_total = inc_comparisons + inc_moves;
        
        // Для убывающего массива
        FillDec(A, n);
        int dec_comparisons, dec_moves;
        SelectSort(A, n, dec_comparisons, dec_moves);
        int dec_total = dec_comparisons + dec_moves;
        
        // Для случайного массива
        FillRand(A, n);
        int rand_comparisons, rand_moves;
        SelectSort(A, n, rand_comparisons, rand_moves);
        int rand_total = rand_comparisons + rand_moves;
        
        PrintTableRow(n, theoretical, dec_total, rand_total, inc_total);
        
        delete[] A;
    }
    
    return 0;
}
