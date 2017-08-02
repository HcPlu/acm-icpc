#include <iostream>

using namespace std;
int n, m;
int f[55][111];
int cost[111][111], profit[111][55], answer;

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &profit[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    memset(f, 0, sizeof f);

    for (int i = 1; i <= n; i++) {
        f[1][i] = profit[i][1];
    }

    for (int i = 2; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                f[i][j] = max(f[i - 1][k] - cost[k][j] + profit[j][i], f[i][j]);
            }
        }
    }
    answer = 0;
    for (int i = 1; i <= n; i++) {
        answer = max(answer, f[m][i]);
    }
    cout << answer << endl;
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
}
