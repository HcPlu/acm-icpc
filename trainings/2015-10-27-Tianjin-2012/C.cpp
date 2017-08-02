#include <cstdio>
#include <cstring>
#include <algorithm>

const int INF = 1 << 30;

const int N = 1111;

int n;
int a[N], b[N];
char texta[N], textb[N];
int best[N][10][10];

void update(int &x, int y) {
    x = std::min(x, y);
}

void solve(void) {
    n = (int)strlen(texta + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = texta[i] - '0';
        b[i] = textb[i] - '0';
    }

    for (int i = 0; i <= n; ++i) {
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 10; ++y) {
                best[i][x][y] = INF;
            }
        }
    }
    best[0][0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int x = 0; x < 10; ++x) {
            if (i == 1 && x > 0) {
                continue;
            }
            for (int y = 0; y < 10; ++y) {
                int number1 = (b[i] - y + 10) % 10;
                int number2 = (y - b[i] + 10) % 10;

                for (int j = 0; j <= number1; ++j) {
                    for (int k = j; k <= number1; ++k) {
                        int _x, _y;
                        if (i == 1) {
                            _x = 0;
                            _y = 0;
                        } else if (i == 2) {
                            _x = 0;
                            _y = (x + k + 10) % 10;
                        } else {
                            _x = (a[i - 2] + j + 10) % 10;
                            _y = (x + k + 10) % 10;
                        }

                        update(best[i][x][y], best[i - 1][_x][_y] + number1);
                    }
                }
                for (int j = 0; j <= number2; ++j) {
                    for (int k = j; k <= number2; ++k) {
                        int _x, _y;
                        if (i == 1) {
                            _x = 0;
                            _y = 0;
                        } else if (i == 2) {
                            _x = 0;
                            _y = (x - k + 10) % 10;
                        } else {
                            _x = (a[i - 2] - j + 10) % 10;
                            _y = (x - k + 10) % 10;
                        }

                        update(best[i][x][y], best[i - 1][_x][_y] + number2);
                    }
                }
            }
        }
    }

    printf("%d\n", best[n][n >= 2 ? a[n - 1] : 0][n >= 1 ? a[n] : 0]);
}

int main(void) {
    for (; ~scanf("%s%s", texta + 1, textb + 1); solve()) {
    }
}
