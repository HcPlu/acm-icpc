#include <iostream>

using namespace std;

const int N = 2010;

int m, n, w[N], a[N], b[N];
int f[N][N][2];

void update(int &x, int y, int z) {
    x = max(x, y);
    x = max(x, z);
}

void solve() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &w[i], &a[i], &b[i]);
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j][1] = f[i][j][0] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
            if (j >= w[i]) {
                update(f[i][j][1], f[i][j - w[i]][0] + b[i] + a[i], f[i][j - w[i]][1] + a[i]);
            }
            update(ans, f[i][j][1], f[i][j][0]);
        }
    }

    printf("%d\n", ans);
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
}
