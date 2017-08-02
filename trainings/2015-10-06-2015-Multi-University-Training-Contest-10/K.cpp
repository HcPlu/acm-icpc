#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

int num[N * 3], tot = 0, k[N * 3], start[N * 3];

struct node {
    int x, y, key, next;
} road[N * 2];

void build(int x, int y, int key) {
    tot++;
    road[tot].x = x, road[tot].y = y, road[tot].next = start[x], start[x] = tot, road[tot].key = key;
    return;
}

void dfs(int x, int fa, int value) {
    num[value]++;
    k[x] = value;
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa)
            continue;
        dfs(to, x, value ^ road[i].key);
    }
    return;
}

void work() {
    int n;
    scanf("%d", &n);
    int Max = 0;
    tot = 0;
    for (int i = 1; i <= n; i++)
        start[i] = 0;
    for (int i = 1; i < n; i++) {
        int p, q, t;
        scanf("%d%d%d", &p, &q, &t);
        build(p, q, t), build(q, p, t);
        Max = max(Max, t);
    }
    Max *= 2;
    memset(num, 0, sizeof(num));
    dfs(1, 0, 0);
    int Q;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        long long ans = 0;
        int p;
        scanf("%d", &p);
        for (int j = 1; j <= n; j++) {
            ans += 1LL * num[p ^ k[j]];
        }
        if (p == 0)
            ans += 1LL * n;
        ans /= 2;
        cout << ans << endl;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        work();
    return 0;
}
