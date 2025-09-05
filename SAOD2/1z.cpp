#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Прямой перебор
vector<int> simpleSearch(const string &text, const string &pattern, int &count) {
    vector<int> pos;
    int n = text.size(), m = pattern.size();
    if (m == 0 || m > n) return{};

    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            count++;
            j++;
        }
        if (j < m) count++;
        if (j == m) pos.push_back(i);
    }
    return pos;
}

// Рабин-Карп
vector<int> rabinKarp(const string &text, const string &pattern, int &count) {
    vector<int> pos;
    const int p = 31;
    const int mod = 1e9 + 7;
    int n = text.size(), m = pattern.size();
    long long hPat = 0, hText = 0, pPow = 1;
    if (m == 0 || m > n) return{};

    for (int i = 0; i < m; i++) {
        hPat = (hPat * p + pattern[i]) % mod;
        hText = (hText * p + text[i]) % mod;
        if (i < m - 1) pPow = (pPow * p) % mod;
    }
    for (int i = 0; i <= n - m; i++) {
        if (hPat == hText) {
            bool ok = true;
            for (int j = 0; j < m; j++) {
                count++;
                if (text[i + j] != pattern[j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) pos.push_back(i);
        }
        if (i < n - m) {
            hText = ( (hText - text[i] * pPow % mod + mod) % mod * p + text[i + m]) % mod;
        }
    }
    return pos;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string text, pattern;
    cout << "Введите текст: ";
    getline(cin, text);
    cout << "Введите подстроку: ";
    getline(cin, pattern);
    int cmp1 = 0, cmp2 = 0;
    auto res1 = simpleSearch(text, pattern, cmp1);
    auto res2 = rabinKarp(text, pattern, cmp2);
    cout << "\nТекст: " << text << "\nПодстрока: " << pattern << "\n";
    cout << "\nПеребор:\n";

    if (res1.empty()) cout << "Не найдено\n";
    else {
        cout << "Индексы: ";
        for (int i : res1) cout << i << " ";
        cout << "\n";
    }
    cout << "Сравнений: " << cmp1 << "\n";
    cout << "\nРабин-Карп:\n";
    if (res2.empty()) cout << "Не найдено\n";
    else {
        cout << "Индексы: ";
        for (int i : res2) cout << i << " ";
        cout << "\n";
    }
    cout << "Сравнений: " << cmp2 << "\n";
    return 0;
}
