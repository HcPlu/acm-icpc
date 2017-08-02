#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

int n, m, a[N];
int Or[N][25];

typedef long long LL;

void work() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= 20; i++)
        for (int j = 1; j <= n + 1; j++)
            Or[j][i] = 1 << 30;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), Or[i][0] = a[i];
    a[n + 1] = m + 1;
    n++;
    for (int i = 1; i <= 20; i++)
        for (int j = 1; (j + (1 << i) - 1) <= n; j++) {
            Or[j][i] = Or[j][i - 1] | Or[j + (1 << i - 1)][i - 1];
        }
    LL ans = 0;
    for (int i = 1; i < n; i++) {
        int now = i;
        int base = 0;
        for (int j = 20; j >= 0; j--) {
            if ((Or[now][j] | base) < m) {
                base = base | Or[now][j];
                now = now + (1 << j);
            }
        }
        //printf("%d %d\n", now, i);
        ans += 1LL * (now - i);
    }
    cout << ans << endl;
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        work();
    }
    return 0;
}
