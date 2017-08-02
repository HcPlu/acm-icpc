#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 55;

double f[N * N][N][N];

double fix(double &x) {
    x = max(x, 0.);
}

void work() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n * m; i++)
        for (int j = 0; j <= n; j++)
            for (int l = 0; l <= m; l++)
                f[i][j][l] = 0;
    f[0][n][m] = 1;
    for (int k = 0; k <= n * m; k++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0)
                    continue;
                double p;
                double current = f[k][i][j];
                if (i) {
                    p = 1. * (m - j) * i / (n * m - k);
                    fix(p);
                    f[k + 1][i - 1][j] += current * p;
                }

                if (j) {
                    p = 1. * (n - i) * j / (n * m - k);
                    fix(p);
                    f[k + 1][i][j - 1] += current * p;
                }

                p = 1. * ((m - j) * (n - i) - k) / (n * m - k);
                fix(p);
                f[k + 1][i][j] += current * p;

                if (i && j) {
                    p = 1. * j * i / (n * m - k);
                    fix(p);
                    f[k + 1][i - 1][j - 1] += current * p;
                }
            }
        }
    }
    double ans = 0;
    for (int i = 0; i <= n * m; i++)
        ans += 1. * i * f[i][0][0];
    printf("%.12f\n", ans);
    return;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
        work();
}
