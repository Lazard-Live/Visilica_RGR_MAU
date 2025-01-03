#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// переменные
char *words[] = { // Массив со словами для отгадывания
        "яблоко",
        "груша",
        "апельсин",
        "виноград",
        "лимон",
        "персик",
        "слива",
        "клубника",
        "малина"
};
int help = 0; // флаг подсказки

// --------- Функции ----------
// Проверка ввода. Допустима только кириллица.
int cyrillicaTest(char c) {
    return (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я');
}

// Проверка запроса помощи от пользователя.
int helpTest(int p) {
    if (p == '?') {
        help = 1;
        return 1;
    }
    return 0;
}

// Проверка повторного ввода буквы.
int letterTest(const char *guessedWord, char guess) {
    for (int i = 0; guessedWord[i] != '\0'; ++i) {
        if (help == 1) { // исключаем из проверки буквы подсказки если включена подсказка
            if (i != 0) {
                if (i != 2) {
                    if (guessedWord[i] == guess) {
                        return 1;
                    }
                }
            }
        } else if (guessedWord[i] == guess) {
            return 1;
        }
    }
    return 0;
}

void hello(){
    printf("\n┌─────────────────────────────────────────────┐"
           "\n│     Добро пожаловать в игру 'Висилица'      │"
           "\n└─────────────────────────────────────────────┘"
           "\n           Цель: Отгадать слово                "
           "\n        (если слаб духом вводи - ?)          \n");
}

void endGame() {
    printf("\n┌─────────────────────────────────────────────┐"
           "\n│       Нажмите 'Enter' для выхода...         │"
           "\n└─────────────────────────────────────────────┘\n");
    scanf("");

    getchar();
    getchar(); // маленький костыль для корректной работы
}

void attemptsGui(int attempts) {
    printf("\n┌─────────────────────────────────────────"
           "\n│ Осталось попыток: %d", attempts);
}

int main() {
    hello();
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int numWords = sizeof(words) / sizeof(char *);
    char *wordToGuess = words[rand() % numWords]; // Выбираем случайное слово

    int wordLength = strlen(wordToGuess);
    char guessedWord[wordLength + 1];
    memset(guessedWord, '_', wordLength); // Заполняем массив подчеркиваниями
    guessedWord[wordLength] = '\0'; // Завершаем строку нулевым символом


    int maxAttempts = 6; // Максимальное количество попыток
    int attemptsLeft = maxAttempts;
    int correctGuesses = 2; // Счетчик отгаданных буквы (изначально 2 т.к. включены буквы подсказки)

    while (attemptsLeft > 0 && correctGuesses != wordLength) {

        attemptsGui(attemptsLeft);
        printf("\n│ Отгадайте слово: %s"
               "\n├──────────────────────────────────────────", guessedWord);

        char guess;
        do {
            printf("\n│ Введите букву: ");
            scanf(" %c", &guess);

            helpTest(guess);
            printf("├──────────────────────────────────────────");
            if (helpTest(guess)) {
                guessedWord[0] = wordToGuess[0]; // Добавление первой
                guessedWord[2] = wordToGuess[2]; // и третей буквы в качестве подсказок
                printf("\n│ Внимание! Активирована подсказка! Ах ты негодник!... ;) "
                       "\n│ Отгадайте слово: %s", guessedWord);

            } else if (!cyrillicaTest(guess)) { //Проверка на киррилицу
                printf("\n│ Пожалуйста, введите букву русского алфавита.");
            } else if (letterTest(guessedWord, guess)) { //Проверка буквы в слове
                printf("\n│ Вы уже ввели эту букву. Попробуйте другую.");
            }
        } while (!cyrillicaTest(guess) || letterTest(guessedWord, guess));

        // Цикл проверки буквы в заданном слове
        int found = 0;
        for (int i = 0; i < wordLength; ++i) {
            if (i != 0) {
                if (i != 2) {
                    if (wordToGuess[i] == guess) { // Если в ячейке найдена буква то...
                        guessedWord[i] = guess;
                        found = 1;
                        correctGuesses++;
                    }
                }
            }
        }
        if (!found) {
            attemptsLeft--;
            printf("\n│ Неверная попытка! Осталось %d попыток.", attemptsLeft);
        } else {
            printf("\n│ Правильно! Буква добавлена в нужное место! ;) ");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\n│ Поздравляем! Вы отгадали слово: %s", wordToGuess);
    } else {
        printf("\n│ К сожалению, вы проиграли. Правильное слово было: %s", wordToGuess);
    }
    printf("\n├──────────────────────────────────────────");
    endGame();

    return 0;
}
