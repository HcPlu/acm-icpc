#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

const int N = 100005;

int n, X, Y, tot = 0;
int value[N], S[N], P[N], F[N];
int start[N];
pair<int, int> f[N][2];

struct Node {
    int x, y, next;
} road[N << 1];

void build(int x, int y) {
    tot++;
    road[tot].x = x, road[tot].y = y, road[tot].next = start[x], start[x] = tot;
}

pair<int, int> add(pair<int, int> x, pair<int, int> y) {
    return make_pair(x.first + y.first, x.second + y.second);
}

pair<int, int> uni(pair<int, int> x, pair<int, int> y) {
    return make_pair(max(x.first, y.first), min(x.second, y.second));
}

void dfs(int x, int fa, int flag) {
    flag ^= S[x];
    int now_value = value[x];
    if ((flag ^ P[x]) == 1) {
        now_value *= -1;
    }
    pair<int, int> current = make_pair(now_value, now_value);
    f[x][0] = current;
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa)
            continue;
        dfs(to, x, flag);
        f[x][0] = add(f[x][0], uni(f[to][0], f[to][1]));
    }
    f[x][1] = make_pair(-f[x][0].second, -f[x][0].first);
    int delta = 0;
    if (S[x])
        delta = Y;
    else
        delta = X;
    f[x][1].first -= delta;
    f[x][1].second += delta;
    return;
}

void work() {
    tot = 0;
    for (int i = 1; i <= n + 1; i++)
        start[i] = 0;
    for (int i = 2; i <= n + 1; i++) {
        scanf("%d%d%d%d", &value[i], &F[i], &S[i], &P[i]);
        F[i]++;
        build(F[i], i);
    }
    dfs(1, 0, 0);

    if (f[1][0].first < 0) {
        puts("HAHAHAOMG");
    } else {
        printf("%d\n", f[1][0].first);
    }
    return;
}

int main() {
    while (scanf("%d%d%d", &n, &X, &Y) == 3) {
        work();
    }
    return 0;
}
