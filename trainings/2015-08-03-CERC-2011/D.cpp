#include <iostream>

using namespace std;
const int N = 1011;

int n;
char s2[N][N];
char s[N][N];
char code[N][N];
char ans[N][N];

void move() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s2[j][n + 1 - i] = s[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            s[i][j] = s2[i][j];
        }
    }
}

int main() {
    while (scanf("%d", &n) == 1 && n != 0) {
        for (int i = 1; i <= n; i++) {
            scanf("%s", s[i] + 1);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%s", code[i] + 1);
        }

        for (int rot = 1; rot <= 4; rot++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (s[i][j] == 'O') {
                        putchar(code[i][j]);
                    }
                }
            }
            move();
        }
        puts("");
    }
    return 0;
}
