#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ��६����
char *words[] = { // ���ᨢ � ᫮���� ��� �⣠�뢠���
        "���",
        "����",
        "�����ᨭ",
        "�����ࠤ",
        "�����",
        "���ᨪ",
        "᫨��",
        "��㡭���",
        "������"
};
int endGame = 0; // 䫠� �����襭�� ����
int help = 0; // 䫠� ���᪠���

// �㭪樨
// �஢�ઠ �����. �����⨬� ⮫쪮 ��ਫ���.
int cyrillicaTest(char c) {
    return (c >= '�' && c <= '�') || (c >= '�' && c <= '�');
}

// �஢�ઠ ����� ����� �� ���짮��⥫�.
int helpTest(int p) {
    if (p == '?') {
        help = 1;
        return 1;
    }
    return 0;
}

// �㭪�� ��� �஢�ન, �뫠 �� �㪢� 㦥 ������� ࠭��.
int letterTest(const char *guessedWord, char guess) {
    for (int i = 0; guessedWord[i] != '\0'; ++i) {
        if (help == 1) { // �᪫�砥� �� �஢�ન �㪢� ���᪠��� �᫨ ����祭� ���᪠���
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

int main() {
    printf("\n���������������������������������������������Ŀ"
           "\n�     ���� ���������� � ���� '��ᨫ��'      �"
           "\n�����������������������������������������������"
           "\n           ����: �⣠���� ᫮��                "
           "\n        (�᫨ ᫠� ��宬 ����� - ?)          \n");
    srand(time(NULL)); // ���樠������ ������� ��砩��� �ᥫ

    int numWords = sizeof(words) / sizeof(char *);
    char *wordToGuess = words[rand() % numWords]; // �롨ࠥ� ��砩��� ᫮��

    int wordLength = strlen(wordToGuess);
    char guessedWord[wordLength + 1];
    memset(guessedWord, '_', wordLength); // ������塞 ���ᨢ ����ન����ﬨ
    guessedWord[wordLength] = '\0'; // �����蠥� ��ப� �㫥�� ᨬ�����


    int maxAttempts = 6; // ���ᨬ��쭮� ������⢮ ����⮪
    int attemptsLeft = maxAttempts;
    int correctGuesses = 2; // ���稪 �⣠������ �㪢� (����砫쭮 2 �.�. ����祭� �㪢� ���᪠���)

    while (attemptsLeft > 0 && correctGuesses != wordLength) {

        printf("\n�������������������������������������������"
               "\n� ��⠫��� ����⮪: %d"
               "\n�������������������������������������������"
               "\n� �⣠���� ᫮��: %s"
               "\n�������������������������������������������", attemptsLeft, guessedWord);

        char guess;
        do {
            printf("\n� ������ �㪢�: ");
            scanf(" %c", &guess);

            printf(" %c", helpTest(guess));
            if (helpTest(guess)) {
                // ���������� ��ࢮ� � ��⥩ �㪢� � ����⢥ ���᪠���
                guessedWord[0] = wordToGuess[0];
                guessedWord[2] = wordToGuess[2];
                printf("\n�������������������������������������������"
                       "\n� ��������! ��⨢�஢��� ���᪠���! �� �� ��������!... :) "
                       "\n�������������������������������������������"
                       "\n� �⣠���� ᫮��: %s"
                       "\n�������������������������������������������", guessedWord);

            } else if (!cyrillicaTest(guess)) { //�஢�ઠ �� ���ਫ���
                printf("\n�������������������������������������������"
                       "\n� ��������, ������ �㪢� ���᪮�� ��䠢��."
                       "\n�������������������������������������������");
            } else if (letterTest(guessedWord, guess)) { //�஢�ઠ �㪢� � ᫮��
                printf("\n�������������������������������������������"
                       "\n� �� 㦥 ����� ��� �㪢�. ���஡�� �����."
                       "\n�������������������������������������������");
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
            printf("\n�������������������������������������������"
                   "\n� ����ୠ� ����⪠! ��⠫��� %d ����⮪."
                   "\n�������������������������������������������", attemptsLeft);
        } else {
            printf("\n�������������������������������������������"
                   "\n� �ࠢ��쭮! �㪢� ��������� � �㦭�� ����! ;) "
                   "\n�������������������������������������������");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\n�������������������������������������������"
               "\n� ����ࠢ�塞! �� �⣠���� ᫮��: %s"
               "\n�������������������������������������������", wordToGuess);
    } else {
        printf("\n�������������������������������������������"
               "\n� � ᮦ������, �� �ந�ࠫ�. �ࠢ��쭮� ᫮�� �뫮: %s"
               "\n�������������������������������������������", wordToGuess);
    }

    printf("\n���������������������������������������������Ŀ"
           "\n�       ������ 'Enter' ��� ��室�...         �"
           "\n�����������������������������������������������\n");
    scanf("");

    getchar();
    getchar();

    return 0;
}
