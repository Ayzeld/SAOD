#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstring>
#include <iomanip>

// Для удобства
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

#define DEBUG 1

struct Node {
    char key;
    Node* next;
    Node(char k) : key(k), next(nullptr) {}
};

// Проверка простого числа
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Хеш-функция (символ по модулю размера таблицы)
unsigned int hash_function(char c, unsigned int m) {
    return static_cast<unsigned char>(c) % m;
}

// Вставка элемента в список по индексу хеша (без дубликатов)
void insert(std::vector<Node*>& hashTable, char key, int m) {
    unsigned int hashValue = hash_function(key, m);
    Node* current = hashTable[hashValue];

    while (current) {
        if (current->key == key) return;  // Уже есть — не вставляем
        current = current->next;
    }

    Node* newNode = new Node(key);
    newNode->next = hashTable[hashValue];
    hashTable[hashValue] = newNode;
}

// Очистка всей хеш-таблицы (освобождение памяти)
void freeHashTable(std::vector<Node*>& hashTable) {
    for (auto& head : hashTable) {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }
}

// Подсчет коллизий
int count_collisions(std::vector<Node*>& hashTable, const string& key_string, int m) {
    freeHashTable(hashTable);
    hashTable.assign(m, nullptr);

    for (char c : key_string) {
        insert(hashTable, c, m);
    }

    int collisions = 0;
    for (int i = 0; i < m; i++) {
        int count = 0;
        Node* current = hashTable[i];
        while (current) {
            count++;
            current = current->next;
        }
        if (count > 1) collisions += (count - 1);
    }

    return collisions;
}

// Печать содержимого хеш-таблицы
void printHashTable(const std::vector<Node*>& hashTable) {
    cout << "Содержимое хеш-таблицы:\n";
    for (size_t i = 0; i < hashTable.size(); i++) {
        cout << "Индекс " << i << ": ";
        Node* current = hashTable[i];
        while (current) {
            cout << current->key << " -> ";
            current = current->next;
        }
        cout << "NULL\n";
    }
}

// Поиск элемента
void search(const std::vector<Node*>& hashTable, char key) {
    int m = static_cast<int>(hashTable.size());
    unsigned int hashValue = hash_function(key, m);
    Node* current = hashTable[hashValue];
    int position = 0;

    while (current) {
        if (current->key == key) {
            cout << "Элемент '" << key << "' найден в списке " << hashValue
                 << " на позиции " << position << ".\n";
            return;
        }
        current = current->next;
        position++;
    }
    cout << "Элемент '" << key << "' не найден.\n";
}

// Подсчет уникальных символов
int countUniqueChars(const string& str) {
    bool seen[256] = {false};
    int count = 0;
    for (unsigned char c : str) {
        if (!seen[c]) {
            seen[c] = true;
            count++;
        }
    }
    return count;
}

void printHeader() {
    cout << "| " << std::left << std::setw(20) << "Размер хеш-таблицы"
         << " | " << std::setw(25) << "Количество исходных символов"
         << " | " << std::setw(20) << "Количество коллизий" << " |\n";

    cout << "|--------------------|---------------------------|----------------------|\n";
}

void printRow(int tableSize, int initialSymbols, int collisions) {
    cout << "| " << std::left << std::setw(20) << tableSize
         << " | " << std::setw(25) << initialSymbols
         << " | " << std::setw(20) << collisions << " |\n";
}

int main() {
    vector<int> primes;
    for (int i = 11; primes.size() < 10 && i <= 101; i++) {
        if (is_prime(i)) primes.push_back(i);
    }

    string key_string = 
        "The integration of digital technology into education has revolutionized how knowledge is acquired, shared, and applied in the 21st century. "
        "From interactive e-learning platforms to AI-driven tutoring systems, technology has dismantled traditional barriers, making education more accessible, personalized, and efficient. "
        "This transformation has not only reshaped classrooms but also redefined the roles of educators and learners, creating a dynamic ecosystem where innovation thrives."
        "One of the most significant advancements is the rise of Massive Open Online Courses (MOOCs). Platforms like Coursera, edX, and Khan Academy offer courses from top universities to anyone with an internet connection, democratizing access to high-quality education. "
        "Learners in remote areas, working professionals, and those with financial constraints can now study subjects ranging from quantum physics to graphic design at their own pace. "
        "This shift has challenged the notion that education must be confined to physical institutions, fostering a global community of self-directed learners."
        "Moreover, artificial intelligence (AI) has introduced tools that adapt to individual learning styles. Adaptive learning software analyzes student performance in real time, identifying strengths and weaknesses to tailor content accordingly. "
        "For instance, language apps like Duolingo use AI to adjust difficulty levels based on user progress, ensuring optimal engagement. Similarly, virtual tutors powered by natural language processing (NLP) provide instant feedback, reducing dependency on human instructors for routine queries. "
        "These innovations not only enhance comprehension but also free educators to focus on mentorship and critical thinking exercises."
        "The COVID-19 pandemic accelerated the adoption of hybrid learning models, blending online and in-person instruction. Video conferencing tools like Zoom and Microsoft Teams became lifelines for schools and universities, enabling continuity amid lockdowns. "
        "While this transition exposed disparities in digital access—highlighting the “homework gap” faced by low-income students—it also spurred initiatives to distribute devices and improve internet connectivity. Governments and nonprofits worldwide recognized that equitable access to technology is no longer a luxury but a necessity for educational equity."
        "Another transformative trend is the use of virtual and augmented reality (VR/AR) in classrooms. Immersive simulations allow students to explore historical sites, conduct virtual lab experiments, or visualize complex mathematical concepts. "
        "For example, medical students can practice surgeries in risk-free VR environments, while history classes might “visit” ancient civilizations through AR-enhanced textbooks. Such experiential learning boosts retention and engagement, catering to diverse learning preferences."
        "However, the digital revolution also presents challenges. Concerns about data privacy, screen time, and the erosion of face-to-face interaction persist. Critics argue that over-reliance on technology may diminish soft skills like teamwork and empathy, which are cultivated through in-person collaboration. "
        "Additionally, the rapid pace of technological change demands constant upskilling from educators, many of whom struggle to keep up with new tools. Addressing these issues requires a balanced approach—embracing technology while preserving the human elements of teaching."
        "Looking ahead, emerging technologies like blockchain could further disrupt education. Blockchain-based credentialing systems might replace traditional diplomas, enabling secure, verifiable records of lifelong learning. "
        "Similarly, decentralized platforms could empower learners to curate personalized education pathways, combining courses from multiple institutions. As the gig economy grows, such flexibility will be crucial for workers navigating career shifts in an automated world."
        "In conclusion, digital technology has irreversibly altered the educational landscape, offering unprecedented opportunities and challenges. Its success hinges on inclusive policies, ethical frameworks, and collaboration between tech developers, educators, and policymakers. "
        "By harnessing innovation responsibly, society can ensure that education remains a catalyst for empowerment, equality, and global progress in the digital age.";

    int key_length = countUniqueChars(key_string);

    cout << "Исследование количества коллизий:\n";
    printHeader();

    vector<Node*> hashTable(101, nullptr);

    for (int m : primes) {
        int collisions = count_collisions(hashTable, key_string, m);
        printRow(m, key_length, collisions);
    }

    int m = 17;
    freeHashTable(hashTable);
    hashTable.assign(m, nullptr);

    for (char c : key_string) {
        insert(hashTable, c, m);
    }

    if (DEBUG) {
        printHashTable(hashTable);
    }

    cout << "\nПоиск элементов:\n";
    search(hashTable, 'e');
    search(hashTable, ' ');
    search(hashTable, 'i');
    search(hashTable, 'X');

    freeHashTable(hashTable);

    return 0;
}
