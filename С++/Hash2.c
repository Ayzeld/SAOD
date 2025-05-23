#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int hash(char c, int size) {
    return (c % size + size) % size; 
}

//считаем количество уникальных символов
int countUniqueSym(char *str){
    int syms[256]  = {0}; //под каждый символ своя ячейка
    int counter = 0;
    for(int i = 0; str[i] != '\0'; i++){
        unsigned char c = (unsigned char)str[i];
        if (!syms[c]){
            syms[c] = 1;
            counter++;
        }
    }
    return counter;
}


//линейная проба
int linearProbe(int *table, int size, int key, int *probes) {
    int m = 0;
    int index;
    do {
        index = (key + m) % size;
        if (table[index] == 0) {
            *probes = m;
            return index;
        }
        m++;
    } while (m < size);
    *probes = -1; 
    return -1;
}


//квадратичная проба
int quadraticProbe(int *table, int size, int key, int *probes) {
    int m = 0;
    int index;
    do {
        index = (key + m * m) % size;
        if (table[index] == 0) {
            *probes = m;
            return index;
        }
        m++;
    } while (m < size);
    *probes = -1; 
    return -1;
}

//заполнение
int insert(int *table, int size, char c, int method) {
    int key = hash(c, size);
    for (int i = 0; i < size; i++) {
        int probeIndex;
        if (method == 1) {
            probeIndex = (key + i) % size;
        } else {
            probeIndex = (key + i * i) % size;
        }
        if (table[probeIndex] == 0) {
            break; 
        }
        if (table[probeIndex] == (int)c) {
            return 0; 
        }
    }
    int probes;
    int index;
    if (method == 1) {
        index = linearProbe(table, size, key, &probes);
    } else {
        index = quadraticProbe(table, size, key, &probes);
    }
    if (index == -1) {
        return -1; 
    }
    table[index] = (int)c;
    return probes; 
}

void printHashTable(int *table, int size, const char *method) {
    printf("\n%s [size: %d]\n", method, size);
    
    // Вывод позиций
    printf("Pos:");
    for (int i = 0; i < size; i++) {
        printf("|%2d", i);
    }
    printf("|\n");
    

    // Вывод значений
    printf("Val:");
    for (int i = 0; i < size; i++) {
        if (table[i] == 0) {
            printf("|  ");
        } else {
            printf("|%2c", table[i]);
        }
    }
    printf("|\n\n");
}
int main() {
    char *text ="The integration of digital technology into education has revolutionized how knowledge is acquired, shared, and applied in the 21st century. From interactive e-learning platforms to AI-driven tutoring systems, technology has dismantled traditional barriers, making education more accessible, personalized, and efficient. This transformation has not only reshaped classrooms but also redefined the roles of educators and learners, creating a dynamic ecosystem where innovation thrives.One of the most significant advancements is the rise of Massive Open Online Courses (MOOCs). Platforms like Coursera, edX, and Khan Academy offer courses from top universities to anyone with an internet connection, democratizing access to high-quality education. Learners in remote areas, working professionals, and those with financial constraints can now study subjects ranging from quantum physics to graphic design at their own pace. This shift has challenged the notion that education must be confined to physical institutions, fostering a global community of self-directed learners.Moreover, artificial intelligence (AI) has introduced tools that adapt to individual learning styles. Adaptive learning software analyzes student performance in real time, identifying strengths and weaknesses to tailor content accordingly. For instance, language apps like Duolingo use AI to adjust difficulty levels based on user progress, ensuring optimal engagement. Similarly, virtual tutors powered by natural language processing (NLP) provide instant feedback, reducing dependency on human instructors for routine queries. These innovations not only enhance comprehension but also free educators to focus on mentorship and critical thinking exercises.The COVID-19 pandemic accelerated the adoption of hybrid learning models, blending online and in-person instruction. Video conferencing tools like Zoom and Microsoft Teams became lifelines for schools and universities, enabling continuity amid lockdowns. While this transition exposed disparities in digital access—highlighting the “homework gap” faced by low-income students—it also spurred initiatives to distribute devices and improve internet connectivity. Governments and nonprofits worldwide recognized that equitable access to technology is no longer a luxury but a necessity for educational equity.Another transformative trend is the use of virtual and augmented reality (VR/AR) in classrooms. Immersive simulations allow students to explore historical sites, conduct virtual lab experiments, or visualize complex mathematical concepts. For example, medical students can practice surgeries in risk-free VR environments, while history classes might “visit” ancient civilizations through AR-enhanced textbooks. Such experiential learning boosts retention and engagement, catering to diverse learning preferences.However, the digital revolution also presents challenges. Concerns about data privacy, screen time, and the erosion of face-to-face interaction persist. Critics argue that over-reliance on technology may diminish soft skills like teamwork and empathy, which are cultivated through in-person collaboration. Additionally, the rapid pace of technological change demands constant upskilling from educators, many of whom struggle to keep up with new tools. Addressing these issues requires a balanced approach—embracing technology while preserving the human elements of teaching.Looking ahead, emerging technologies like blockchain could further disrupt education. Blockchain-based credentialing systems might replace traditional diplomas, enabling secure, verifiable records of lifelong learning. Similarly, decentralized platforms could empower learners to curate personalized education pathways, combining courses from multiple institutions. As the gig economy grows, such flexibility will be crucial for workers navigating career shifts in an automated world.In conclusion, digital technology has irreversibly altered the educational landscape, offering unprecedented opportunities and challenges. Its success hinges on inclusive policies, ethical frameworks, and collaboration between tech developers, educators, and policymakers. By harnessing innovation responsibly, society can ensure that education remains a catalyst for empowerment, equality, and global progress in the digital age.";
    int numKeys = countUniqueSym(text);

    int size = 47;
    int *linearTable = (int *)calloc(size, sizeof(int));
    int *quadraticTable = (int *)calloc(size, sizeof(int));

    if (linearTable == NULL || quadraticTable == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    int linearCollisions = 0;
    int quadraticCollisions = 0;
    for (int j = 0; j < strlen(text); j++) {
        int lin_result = insert(linearTable, size, text[j], 1);
        int quad_result = insert(quadraticTable, size, text[j], 2);
        if (lin_result >= 0) linearCollisions += lin_result;
        if (quad_result >= 0) quadraticCollisions += quad_result;
    }

    printHashTable(linearTable, size, "Линейная");
    printHashTable(quadraticTable, size, "Квадратичная");

    printf("| %-15s | %-19s | %-19s | %-19s |\n", "Размер", "Количество исх. символов", "Кол-во коллизий (Линейные пробы)", "Кол-во коллизий (Квадратичные пробы)");
    printf("|-----------|--------------------------|----------------------------------|--------------------------------------|\n");

    free(linearTable);
    free(quadraticTable);


    int prime_numbers[10];
    int index = 0;
    int turn = 0;
    //вычислим все простые числа начиная с 14 до 101 и будем записывать каждое второе число 
    for(int i = 14; i < 102; i++){
        if (isPrime(i) && turn == 0){
            prime_numbers[index] = i;
            index++;
            turn = 1;
        }
        else if(isPrime(i) && turn == 1){
            turn = 0;
        }
    }

    for (int i = 0; i < 10; i++) {

        int *linearTable = (int *)calloc(prime_numbers[i], sizeof(int));
        int *quadraticTable = (int *)calloc(prime_numbers[i], sizeof(int));

   

        int linearCollisions = 0;
        int quadraticCollisions = 0;

        for (int j = 0; j < strlen(text); j++) {
            int lin_result = insert(linearTable, prime_numbers[i], text[j], 1);
            int quad_result = insert(quadraticTable, prime_numbers[i], text[j], 2);
            if (lin_result >= 0) linearCollisions += lin_result;
            if (quad_result >= 0) quadraticCollisions += quad_result;
        }

        printf("| %-9d | %-24d | %-32d | %-36d |\n", prime_numbers[i], numKeys, linearCollisions, quadraticCollisions);

        free(linearTable);
        free(quadraticTable);
    }

    return 0;
}
