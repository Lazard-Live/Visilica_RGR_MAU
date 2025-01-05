#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// ------- Переменные --------
#include "variables.h"
// ------- База Слов --------
#include "words.h" // Дабавлять и удалять файлы в этом файле. Необходимо сохранение структуры.
// --------- Функции ----------
#include "functions/cyrillicaTest.h" // Проверка ввода. Допустима только кириллица.
#include "functions/helpTest.h" // Проверка запроса помощи от пользователя.
#include "functions/letterTest.h" // Проверка повторного ввода буквы.
// --------- Символьная графика --------
#include "gui/guiViselica.h" // Символьная графика попыток с отображением виселицы.
#include "gui/hello.h" // Приветствие и правила
#include "gui/endGame.h" // Сообщение и задержка завершения программы до нажатия клавиши "Enter"
#include "gui/attemptsGui.h" // Вывод оставшихся попыток

int main() {
    hello();
    srand(time(NULL)); // Инициализация генератора случайных чисел

    int numWords = sizeof(words) / sizeof(char *);
    char *wordToGuess = words[rand() % numWords]; // Выбираем случайное слово

    int wordLength = strlen(wordToGuess);
    char guessedWord[wordLength + 1];
    memset(guessedWord, '_', wordLength); // Заполняем массив подчеркиваниями
    guessedWord[wordLength] = '\0'; // Завершаем строку нулевым символом

    int attemptsLeft = maxAttempts;
    printf("\n------------------------------------------");
    guiViselica(attemptsLeft);

    while (attemptsLeft > 0 && correctGuesses != wordLength) {
        attemptsGui(attemptsLeft);
        printf("\n│ Отгадайте слово: %s"
               "\n+------------------------------------------", guessedWord);

        char guess;
        do {
            printf("\n│ Введите букву: ");
            scanf(" %c", &guess);

            helpTest(guess);
            printf("+------------------------------------------");
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
            guiViselica(attemptsLeft);
            printf("\n│ Неверная попытка! Осталось %d попыток.", attemptsLeft);
        } else {
            guiViselica(attemptsLeft);
            printf("\n│ Правильно! Буква добавлена в нужное место! ;) ");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\n│ Поздравляем! Вы отгадали слово: %s", wordToGuess);
    } else {
        printf("\n│ К сожалению, вы проиграли. Правильное слово было: %s", wordToGuess);
    }
    printf("\n+------------------------------------------");
    endGame();

    return 0;
}
