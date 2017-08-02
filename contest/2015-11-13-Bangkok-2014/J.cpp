#include<cstdio>

using namespace std;

const int N = 100005;

int num[17][16];
int ans[N];

void work() {
    for (int i = 1; i <= 16; i++)
        for (int j = 0; j < i; j++)
            num[i][j] = 0;
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        for (int j = 0; j < a; j++) {
            num[b][j]++;
        }
    }
    for (int i = 0; i <= n; i++) {
        ans[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int result = 0;
        for (int j = 1; j <= 16; j++) {
            result += num[j][i % j];
        }
        ans[result]++;
    }
    for (int i = 0; i <= n; i++) {
        printf("%d\n", ans[i]);
    }
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
