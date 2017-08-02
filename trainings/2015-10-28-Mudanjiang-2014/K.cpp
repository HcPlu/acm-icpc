#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 1111111;

char text[N];

void solve(void) {
    scanf("%s", text);
    int length = (int)strlen(text);

    int digits = 0, stars = 0;
    for (int i = 0; i < length; ++i) {
        if (text[i] == '*') {
            stars++;
        } else {
            digits++;
        }
    }

    int answer = std::max(0, stars - digits + 1);
    int digit = answer;

    for (int i = 0; i < length; ++i) {
        if (text[i] == '*') {
            if (digit < 2) {
                for (int j = length - 1; j > i; --j) {
                    if (text[j] != '*') {
                        std::swap(text[i], text[j]);
                        break;
                    }
                }
                answer++;
                digit++;
            } else {
                digit--;
            }
        } else {
            digit++;
        }
    }
    printf("%d\n", answer);
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve()) {
    }
}
