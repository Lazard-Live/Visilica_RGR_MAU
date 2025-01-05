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
