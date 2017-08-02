#include <iostream>

using namespace std;

int n, m;
int a[111111], sum[111111], N[111111], minn[111111];

void solve() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] + a[i] % m + m) % m;
    }
    for (int i = 0; i < m; i++) {
        minn[i] = n + 1;
        N[i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        minn[sum[i]] = min(minn[sum[i]], i);
        N[sum[i]] = max(N[sum[i]], i);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        ans = max(ans, N[i] - minn[i]);
    }
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        solve();
    }
}
