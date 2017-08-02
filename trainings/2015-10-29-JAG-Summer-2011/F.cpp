#include <cstdio>
#include <algorithm>
#include <cmath>

const double INF = 1e60;
const int N = 200000;

int n;
int a[22];
double f[22][N + 1];

void update(double &x, const double &y) {
    x = std::min(x, y);
}

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= N; ++j) {
            f[i][j] = INF;
        }
    }

    f[0][1] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= N; ++j) {
            for (int k = j; k <= N; k += j) {
                update(f[i + 1][k], std::max(f[i][j], 1. * std::abs(a[i + 1] - k) / a[i + 1]));
            }
        }
    }

    double answer = INF;
    for (int i = 1; i <= N; ++i) {
        update(answer, f[n][i]);
    }
    printf("%.10f\n", answer);
}
