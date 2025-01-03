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
int help = 0; // 䫠� ���᪠���

// --------- �㭪樨 ----------
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

// �஢�ઠ ����୮�� ����� �㪢�.
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

void hello(){
    printf("\n���������������������������������������������Ŀ"
           "\n�     ���� ���������� � ���� '��ᨫ��'      �"
           "\n�����������������������������������������������"
           "\n           ����: �⣠���� ᫮��                "
           "\n        (�᫨ ᫠� ��宬 ����� - ?)          \n");
}

void endGame() {
    printf("\n���������������������������������������������Ŀ"
           "\n�       ������ 'Enter' ��� ��室�...         �"
           "\n�����������������������������������������������\n");
    scanf("");

    getchar();
    getchar(); // �����쪨� ������ ��� ���४⭮� ࠡ���
}

void attemptsGui(int attempts) {
    printf("\n������������������������������������������"
           "\n� ��⠫��� ����⮪: %d", attempts);
}

int main() {
    hello();
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

        attemptsGui(attemptsLeft);
        printf("\n� �⣠���� ᫮��: %s"
               "\n�������������������������������������������", guessedWord);

        char guess;
        do {
            printf("\n� ������ �㪢�: ");
            scanf(" %c", &guess);

            helpTest(guess);
            printf("�������������������������������������������");
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
            printf("\n� ����ୠ� ����⪠! ��⠫��� %d ����⮪.", attemptsLeft);
        } else {
            printf("\n� �ࠢ��쭮! �㪢� ��������� � �㦭�� ����! ;) ");
        }
    }

    if (correctGuesses == wordLength) {
        printf("\n� ����ࠢ�塞! �� �⣠���� ᫮��: %s", wordToGuess);
    } else {
        printf("\n� � ᮦ������, �� �ந�ࠫ�. �ࠢ��쭮� ᫮�� �뫮: %s", wordToGuess);
    }
    printf("\n�������������������������������������������");
    endGame();

    return 0;
}
