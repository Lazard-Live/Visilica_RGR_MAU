#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// ------- ��६���� --------
#include "variables.h"
// ------- ���� ���� --------
#include "words.h" // ��������� � 㤠���� 䠩�� � �⮬ 䠩��. ����室��� ��࠭���� ��������.
// --------- �㭪樨 ----------
#include "functions/cyrillicaTest.h" // �஢�ઠ �����. �����⨬� ⮫쪮 ��ਫ���.
#include "functions/helpTest.h" // �஢�ઠ ����� ����� �� ���짮��⥫�.
#include "functions/letterTest.h" // �஢�ઠ ����୮�� ����� �㪢�.
// --------- ������쭠� ��䨪� --------
#include "gui/guiViselica.h" // ������쭠� ��䨪� ����⮪ � �⮡ࠦ����� ��ᥫ���.
#include "gui/hello.h" // �ਢ���⢨� � �ࠢ���
#include "gui/endGame.h" // ����饭�� � ����প� �����襭�� �ணࠬ�� �� ������ ������ "Enter"
#include "gui/attemptsGui.h" // �뢮� ��⠢���� ����⮪

int main() {
    hello();
    srand(time(NULL)); // ���樠������ ������� ��砩��� �ᥫ

    int numWords = sizeof(words) / sizeof(char *);
    char *wordToGuess = words[rand() % numWords]; // �롨ࠥ� ��砩��� ᫮��

    int wordLength = strlen(wordToGuess);
    char guessedWord[wordLength + 1];
    memset(guessedWord, '_', wordLength); // ������塞 ���ᨢ ����ન����ﬨ
    guessedWord[wordLength] = '\0'; // �����蠥� ��ப� �㫥�� ᨬ�����

    int attemptsLeft = maxAttempts;
    printf("\n------------------------------------------");
    guiViselica(attemptsLeft);

    while (attemptsLeft > 0 && correctGuesses != wordLength) {
        attemptsGui(attemptsLeft);
        printf("\n� �⣠���� ᫮��: %s"
               "\n+------------------------------------------", guessedWord);

        char guess;
        do {
            printf("\n� ������ �㪢�: ");
            scanf(" %c", &guess);

            helpTest(guess);
            printf("+------------------------------------------");
            if (helpTest(guess)) {
                guessedWord[0] = wordToGuess[0]; // ���������� ��ࢮ�
                guessedWord[2] = wordToGuess[2]; // � ��⥩ �㪢� � ����⢥ ���᪠���
                printf("\n� ��������! ��⨢�஢��� ���᪠���! �� �� ��������!... ;) "
                       "\n� �⣠���� ᫮��: %s", guessedWord);

            } else if (!cyrillicaTest(guess)) { //�஢�ઠ �� ���ਫ���
                printf("\n� ��������, ������ �㪢� ���᪮�� ��䠢��.");
            } else if (letterTest(guessedWord, guess)) { //�஢�ઠ �㪢� � ᫮��
                printf("\n� �� 㦥 ����� ��� �㪢�. ���஡�� �����.");
            }
        } while (!cyrillicaTest(guess) || letterTest(guessedWord, guess));

        // ���� �஢�ન �㪢� � �������� ᫮��
        int found = 0;
        for (int i = 0; i < wordLength; ++i) {
            if (i != 0) {
                if (i != 2) {
                    if (wordToGuess[i] == guess) { // �᫨ � �祩�� ������� �㪢� �...
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
            printf("\n� ����ୠ� ����⪠! ��⠫��� %d ����⮪.", attemptsLeft);
        } else {
            guiViselica(attemptsLeft);
            printf("\n� �ࠢ��쭮! �㪢� ��������� � �㦭�� ����! ;) ");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\n� ����ࠢ�塞! �� �⣠���� ᫮��: %s", wordToGuess);
    } else {
        printf("\n� � ᮦ������, �� �ந�ࠫ�. �ࠢ��쭮� ᫮�� �뫮: %s", wordToGuess);
    }
    printf("\n+------------------------------------------");
    endGame();

    return 0;
}
