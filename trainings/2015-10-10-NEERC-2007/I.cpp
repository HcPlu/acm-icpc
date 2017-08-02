#include <cstdio>
#include <cctype>
#include <cstring>
#include <string>

char buffer[111111];
std::string table[26][26][40];

bool legal(char x) {
    return isdigit(x) || isalpha(x);
}

bool find(char a, char b, int length) {
    std::string &item = table[tolower(a) - 'a'][tolower(b) - 'a'][length];
    return item != "" && item != "!";
}

std::string fetch(char a, char b, int length) {
    return table[tolower(a) - 'a'][tolower(b) - 'a'][length];
}

void insert(char a, char b, int length, std::string data) {
    std::string &item = table[tolower(a) - 'a'][tolower(b) - 'a'][length];
    for (int i = 0; i < length; ++i) {
        data[i] = tolower(data[i]);
    }
    if (item == data) {
        return;
    }
    if (item == "") {
        item = data;
    } else {
        item = "!";
    }
}

std::string solve(const std::string &text) {
    if ((int)text.length() <= 2) {
        return text;
    }
    if (isdigit(text[1])) {
        int number = 0;
        for (int i = 1; i < (int)text.length() - 1; ++i) {
            number = number * 10 + text[i] - '0';
        }
        number += 2;
        if (!find(text[0], text[(int)text.length() - 1], number)) {
            return text;
        } else {
            std::string answer = fetch(text[0], text[(int)text.length() - 1], number);
            if (isupper(text[0]) && isupper(text[(int)text.length() - 1])) {
                for (int i = 0; i < (int)answer.length(); ++i) {
                    answer[i] = toupper(answer[i]);
                }
            } else {
                answer[0] = text[0];
            }
            return answer;
        }
    } else {
        insert(text[0], text[(int)text.length() - 1], (int)text.length(), text);
        return text;
    }
}

bool blank = false;

void solve() {
    int length = (int)strlen(buffer);
    if (length == 0) {
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                for (int k = 0; k < 40; ++k) {
                    table[i][j][k] = "";
                }
            }
        }
        blank = true;
        return;
    }

    if (blank) {
        blank = false;
        puts("");
    }

    for (int i = 0, j; i < length; i = j) {
        if (!legal(buffer[i])) {
            putchar(buffer[i]);
            j = i + 1;
        } else {
            std::string word = "";
            for (j = i; j < length && legal(buffer[j]); ++j) {
                word += buffer[j];
            }

            printf("%s", solve(word).c_str());
        }
    }
    puts("");
}

int main(void) {
    for (; gets(buffer); solve()) {
    }
}
