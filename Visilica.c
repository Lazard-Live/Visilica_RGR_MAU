#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ���ᨢ � ᫮���� ��� �⣠�뢠���
char *words[] = {
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


// �㭪�� ��� �஢�ન, ���� �� ᨬ��� ���᪮� �㪢��
int cyrillicaTest(char c) {
    return (c >= '�' && c <= '�') || (c >= '�' && c <= '�');
}

int helpTest(int p) {
    if (p == '?') {
        help = 1;
        return 1;
    }

    return 0;
}

// �㭪�� ��� �஢�ન, �뫠 �� �㪢� 㦥 �������
int letterTest(const char *guessed_word, char guess) {

    for (int i = 0; guessed_word[i] != '\0'; ++i) {
        if (help == 1) {
            if (i != 0) {
                if (i != 2) { // �᪫�砥� �� �஢�ન �㪢� ���᪠��� (�१ || �� ���⥫� ࠡ����)
                    if (guessed_word[i] == guess) {
                        return 1;
                    }
                }
            }
        } else if (guessed_word[i] == guess) {
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

    int num_words = sizeof(words) / sizeof(char *);
    char *word_to_guess = words[rand() % num_words]; // �롨ࠥ� ��砩��� ᫮��

    int word_length = strlen(word_to_guess);
    char guessed_word[word_length + 1];
    memset(guessed_word, '_', word_length); // ������塞 ���ᨢ ����ન����ﬨ
    guessed_word[word_length] = '\0'; // �����蠥� ��ப� �㫥�� ᨬ�����


    int max_attempts = 6; // ���ᨬ��쭮� ������⢮ ����⮪
    int attempts_left = max_attempts;
    int correct_guesses = 2; // ���稪 �⣠������ �㪢� (����砫쭮 2 �.�. ����祭� �㪢� ���᪠���)

    while (attempts_left > 0 && correct_guesses != word_length) {

        printf("\n�������������������������������������������"
               "\n� ��⠫��� ����⮪: %d"
               "\n�������������������������������������������"
               "\n� �⣠���� ᫮��: %s"
               "\n�������������������������������������������", attempts_left, guessed_word);

        char guess;
        do {
            printf("\n� ������ �㪢�: ");
            scanf(" %c", &guess);

            printf(" %c", helpTest(guess));
            if (helpTest(guess)) {
                // ���������� ��ࢮ� � ��⥩ �㪢� � ����⢥ ���᪠���
                guessed_word[0] = word_to_guess[0];
                guessed_word[2] = word_to_guess[2];
                printf("\n�������������������������������������������"
                       "\n� ��������! ��⨢�஢��� ���᪠���! �� �� ��������!... :) "
                       "\n�������������������������������������������"
                       "\n� �⣠���� ᫮��: %s"
                       "\n�������������������������������������������", guessed_word);

            } else if (!cyrillicaTest(guess)) { //�஢�ઠ �� ���ਫ���
                printf("\n�������������������������������������������"
                       "\n� ��������, ������ �㪢� ���᪮�� ��䠢��."
                       "\n�������������������������������������������");
            } else if (letterTest(guessed_word, guess)) { //�஢�ઠ �㪢� � ᫮��
                printf("\n�������������������������������������������"
                       "\n� �� 㦥 ����� ��� �㪢�. ���஡�� �����."
                       "\n�������������������������������������������");
            }
        } while (!cyrillicaTest(guess) || letterTest(guessed_word, guess));

        // ���� �஢�ન �㪢� � �������� ᫮��
        int found = 0;
        for (int i = 0; i < word_length; ++i) {
            if (i != 0) {
                if (i != 2) {
                    if (word_to_guess[i] == guess) { // �᫨ � �祩�� ������� �㪢� �...
                        guessed_word[i] = guess;
                        found = 1;
                        correct_guesses++;
                    }
                }
            }
        }

        if (!found) {
            attempts_left--;
            printf("\n�������������������������������������������"
                   "\n� ����ୠ� ����⪠! ��⠫��� %d ����⮪."
                   "\n�������������������������������������������", attempts_left);
        } else {
            printf("\n�������������������������������������������"
                   "\n� �ࠢ��쭮! �㪢� ��������� � �㦭�� ����! ;) "
                   "\n�������������������������������������������");
        }
    }

    if (correct_guesses == word_length) {
        printf("\n�������������������������������������������"
               "\n� ����ࠢ�塞! �� �⣠���� ᫮��: %s"
               "\n�������������������������������������������", word_to_guess);
    } else {
        printf("\n�������������������������������������������"
               "\n� � ᮦ������, �� �ந�ࠫ�. �ࠢ��쭮� ᫮�� �뫮: %s"
               "\n�������������������������������������������", word_to_guess);
    }

    printf("\n���������������������������������������������Ŀ"
           "\n�       ������ 'Enter' ��� ��室�...         �"
           "\n�����������������������������������������������\n");
    scanf("");

    getchar();
    getchar();

    return 0;


}
