#include <cstdio>

using namespace std;

const int N = 1005;

int n, m;
int num[N][N];
char ans[N][N];

int dx[9] = {0, 1, 1, 1, -1, -1, -1, 0, 0};
int dy[9] = {0, 0, 1, -1, 0, 1, -1, 1, -1};

void work() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &num[i][j]);
    if (n == 1 && m == 1) {
        if (num[1][1] == 0) {
            puts("-");
        } else {
            puts("L");
        }
        return;
    }
    for (int i = 1; i <= n; i++) {

        if (num[i][1] <= 3) {
            ans[i][1] = '-';
        } else {
            ans[i][1] = 'L';
            for (int k = 1; k <= 8; k++) {
                int ux = i + dx[k];
                int uy = 1 + dy[k];
                if (ux == 0 || uy == 0 || ux > n || uy > m)
                    continue;
                num[ux][uy]--;
            }
        }

        for (int j = 2; j < m; j++) {
            if (num[i][j] > 4 || (num[i][j] == 4 && num[i][j + 1] < 4)) {
                ans[i][j] = 'L';
                for (int k = 1; k <= 8; k++) {
                    int ux = i + dx[k];
                    int uy = j + dy[k];
                    if (ux == 0 || uy == 0 || ux > n || uy > m)
                        continue;
                    num[ux][uy]--;
                }
            } else {
                ans[i][j] = '-';
            }
        }

        if (num[i][m] <= 3) {
            ans[i][m] = '-';
        } else {
            ans[i][m] = 'L';
            for (int k = 1; k <= 8; k++) {
                int ux = i + dx[k];
                int uy = m + dy[k];
                if (ux == 0 || uy == 0 || ux > n || uy > m)
                    continue;
                num[ux][uy]--;
            }
        }

    }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 1; j <= m; j++)
            printf("%c", ans[i][j]);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        work();
    }
    return 0;
}
