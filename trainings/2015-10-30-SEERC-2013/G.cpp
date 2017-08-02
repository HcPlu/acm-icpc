#include <iostream>

using namespace std;
const int INF = 1 << 30;
const int N = 1111111;

int f[N][2][2];
int a[N], b[N], c[N];
int n;

int calc(int pos, int now, int post, int prev) {
    if (!now) {
        return 0;
    }
    if (post && prev) {
        return c[pos];
    }
    if (post || prev) {
        return b[pos];
    }
    return a[pos];
}

void update(int &x, int y) {
    x = max(x, y);
}

void solve() {
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
    f[0][0][1] = 0;
    f[0][0][0] = 0;
    f[0][1][0] = -INF;
    f[0][1][1] = -INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                f[i][j][k] = -INF;
                for (int l = 0; l < 2; l++) {
                    update(f[i][j][k], f[i - 1][l][j] + calc(i, j, k, l));
                }
            }
        }
    }

    int answer = max(f[n][1][0], f[n][0][0]);
    printf("%d\n", answer);
}

int main() {
    for (; scanf("%d", &n) == 1; solve()) {
    }
    return 0;
}
