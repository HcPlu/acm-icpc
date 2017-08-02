#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>

using namespace std;

const int N = 125;

double p[N][N];
int n, seq[10005];
double f[10005][N];

void work() {
    n = n * (n - 1) * (n - 2) / 6;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lf", &p[i][j]);
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &seq[i]);
        seq[i]++;
    }
    double ans = 0;

    memset(f, 0, sizeof(f));

    for (int i = 0; i <= n; i++)
        f[0][i] = 1;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = max(f[i][j], f[i - 1][j] * p[j][seq[i]]);
        }
        for (int j = 1; j <= n; j++) {
            f[i][seq[i - 1]] = max(f[i][seq[i - 1]], f[i - 1][j] * p[seq[i - 1]][seq[i]]);
        }
    }
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[m][i]);
    printf("%.10f\n", ans);
    return;
}

int main() {
    while (scanf("%d", &n) == 1) {
        work();
    }
    return 0;
}
