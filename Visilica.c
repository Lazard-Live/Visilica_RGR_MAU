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

void guiViselica(int attempts) {
    if (attempts == 6) {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||      "
               "\n�    ||    "
               "\n�    ||      "
               "\n�    ||      "
               "\n� ||||||______ ");
    } else  if (attempts == 5) {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||    (_)  "
               "\n�    ||    "
               "\n�    ||      "
               "\n�    ||      "
               "\n� ||||||______ ");
    }else if (attempts == 4) {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||    (_)  "
               "\n�    ||     � "
               "\n�    ||     �   "
               "\n�    ||         "
               "\n� ||||||______ ");
    }else if (attempts == 3) {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||    (_)  "
               "\n�    ||   �ͺ  "
               "\n�    ||     �   "
               "\n�    ||         "
               "\n� ||||||______ ");
    }else if (attempts == 2) {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||    (_)  "
               "\n�    ||   �ͺͻ "
               "\n�    ||     �   "
               "\n�    ||         "
               "\n� ||||||______ ");
    }else if (attempts == 1) {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||    (_)  "
               "\n�    ||   �ͺͻ "
               "\n�    ||    ��   "
               "\n�    ||    �    "
               "\n� ||||||______ ");
    }else {
        printf("\n�    ||========= "
               "\n�    ||     �   "
               "\n�    ||    (_)  "
               "\n�    ||   �ͺͻ "
               "\n�    ||    �ʷ  "
               "\n�    ||    � �  "
               "\n� ||||||______ ");
    }
};


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
    printf("\n����������������������������������������������Ŀ"
           "\n�         ���� ���������� � ����              �"
           "\n�  ��ͻ  ɻɻ ��ͻ ���ͻ  ��ͻ ɻɻ ɻɻ ��ͻ  �"
           "\n�  �ɻ�  ���� ��ͼ ���ͼ  �ɻ� ���� ���� �ɻ�  �"
           "\n�  �ȼȻ ���� ��   ���ͻ  ���� ���� ���� �ȼ�  �"
           "\n�  ��ͻ� ��ɺ ��   ���ͼ  ���� ��ɺ ���� �ɻ�  �"
           "\n�  ��ͼ� �ȼ� ��ͻ ���ͻ ɼ��� �ȼ� �ȼ� ����  �"
           "\n�  ���ͼ ��ͼ ��ͼ ���ͼ �ͼȼ ��ͼ ��ͻ ȼȼ  �"
           "\n� ���ࠡ��稪:�.�.���檨�  ��㯯�:���-���24�-1�"
           "\n������������������������������������������������"
           "\n���� ����:  ��ப� �����뢠���� ᫮��, ���஥ "
           "\n�� ����� 㣠����, �ᯮ���� �㪢� ���᪮�� ��䠢��. "
           "\n�����⨬� �訡��: 6             "
           "\n����� '?' �᫨ �㦭� ���᪠��� (����㯭� 1 ࠧ)  \n");
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
    printf("\n������������������������������������������");
    guiViselica(attemptsLeft);

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
    printf("\n�������������������������������������������");
    endGame();

    return 0;
}
