#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Функции заполнения массива
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = n - i - 1;
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % 100;
}

// Исходный метод сортировки выбором
void SelectSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (A[j] < A[minIndex]) minIndex = j;
        }
        // Обмен элементами
        int temp = A[i];
        A[i] = A[minIndex];
        A[minIndex] = temp;
        moves += 3; // Записываем все перемещения
    }
}

// Улучшенный метод сортировки выбором
void ImprovedSelectSort(int A[], int n, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (A[j] < A[minIndex]) {
                minIndex = j;
            }
        }
        // Проверяем, нужно ли действительно менять элементы
        if (minIndex != i) {
            int temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
            moves += 3; // Записываем только реальные перемещения
        }
    }
}

// Вывод заголовка таблицы
void PrintTableHeader() {
    std::cout << "+------+----------------+---------------------+---------------------+" << std::endl;
    std::cout << "|  N   | M+C теоретич.  | Исходный Мфакт+Сфакт | Улучшенный Мфакт+Сфакт |" << std::endl;
    std::cout << "|      |                | Убыв. | Случ. | Возр. | Убыв. | Случ. | Возр. |" << std::endl;
    std::cout << "+------+----------------+-------+-------+-------+-------+-------+-------+" << std::endl;
}

// Вывод строки таблицы
void PrintTableRow(int n, int theoretical, 
                   int dec_original, int rand_original, int inc_original,
                   int dec_improved, int rand_improved, int inc_improved) {
    std::cout << "| " << std::setw(4) << n << " | " 
              << std::setw(14) << theoretical << " | "
              << std::setw(5) << dec_original << " | " 
              << std::setw(5) << rand_original << " | " 
              << std::setw(5) << inc_original << " | "
              << std::setw(5) << dec_improved << " | " 
              << std::setw(5) << rand_improved << " | " 
              << std::setw(5) << inc_improved << " |" << std::endl;
    std::cout << "+------+----------------+-------+-------+-------+-------+-------+-------+" << std::endl;
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
        int theoretical = (n * n) / 2 - n / 2 + 3 * (n - 1);
        
        // Для возрастающего массива
        FillInc(A, n);
        int inc_comparisons_original, inc_moves_original;
        SelectSort(A, n, inc_comparisons_original, inc_moves_original);
        int inc_total_original = inc_comparisons_original + inc_moves_original;
        
        FillInc(A, n);
        int inc_comparisons_improved, inc_moves_improved;
        ImprovedSelectSort(A, n, inc_comparisons_improved, inc_moves_improved);
        int inc_total_improved = inc_comparisons_improved + inc_moves_improved;
        
        // Для убывающего массива
        FillDec(A, n);
        int dec_comparisons_original, dec_moves_original;
        SelectSort(A, n, dec_comparisons_original, dec_moves_original);
        int dec_total_original = dec_comparisons_original + dec_moves_original;
        
        FillDec(A, n);
        int dec_comparisons_improved, dec_moves_improved;
        ImprovedSelectSort(A, n, dec_comparisons_improved, dec_moves_improved);
        int dec_total_improved = dec_comparisons_improved + dec_moves_improved;
        
        // Для случайного массива
        FillRand(A, n);
        int rand_comparisons_original, rand_moves_original;
        SelectSort(A, n, rand_comparisons_original, rand_moves_original);
        int rand_total_original = rand_comparisons_original + rand_moves_original;
        
        FillRand(A, n);
        int rand_comparisons_improved, rand_moves_improved;
        ImprovedSelectSort(A, n, rand_comparisons_improved, rand_moves_improved);
        int rand_total_improved = rand_comparisons_improved + rand_moves_improved;
        
        // Вывод результата
        PrintTableRow(n, theoretical,
                      dec_total_original, rand_total_original, inc_total_original,
                      dec_total_improved, rand_total_improved, inc_total_improved);        
        delete[] A;
    } 
    return 0;
}
