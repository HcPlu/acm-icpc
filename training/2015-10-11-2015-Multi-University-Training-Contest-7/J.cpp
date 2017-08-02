#include <cstdio>

using namespace std;

const int N = 1005;
const int mod = 1000000007;
struct Node {
    int x, y, next;
} road[N << 1];

int start[N], num[N], visit[N];
int ni[N], tot = 0;
int f[N][N];

int powmod(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = 1LL * x * x % mod)
        if (y & 1)
            ans = 1LL * ans * x % mod;
    return ans;
}

void build(int x, int y) {
    tot++;
    road[tot].x = x, road[tot].y = y, road[tot].next = start[x], start[x] = tot;
}

void dfs(int x, int fa) {
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa)
            continue;
        dfs(to, x);
        num[x] += num[to];
    }
    return;
}

void work() {
    int n, k;
    scanf("%d%d", &n, &k);
    tot = 0;
    for (int i = 1; i <= n; i++)
        num[i] = 1, start[i] = 0;
    for (int i = 2; i <= n; i++) {
        int p, q;
        scanf("%d %d", &p, &q);
        build(p, q);
        build(q, p);
    }
    dfs(1, 0);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        f[0][0] = 1LL * f[0][0] * i % mod;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) {
            f[i][j] = 1LL * f[i - 1][j] * ni[num[i]] % mod * (num[i] - 1) % mod;
            if (j >= 1)
                f[i][j] = (f[i][j] + 1LL * f[i - 1][j - 1] * ni[num[i]] % mod) % mod;
        }
    printf("%d\n", f[n][k]);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= 1000; i++)
        ni[i] = powmod(i, mod - 2);
    for (int i = 1; i <= T; i++)
        printf("Case #%d: ", i), work();
    return 0;
}
