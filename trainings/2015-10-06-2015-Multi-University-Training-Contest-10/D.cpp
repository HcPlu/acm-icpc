#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 100005;

int n, m, p, q, tot, pre[N], dfn[N], value[N], Log[N], start[N];
int L[N], R[N];
int color[N], num_color, dfs_clock, low[N];
int Max[N][20];

pair<int, int> need[N];

struct Node {
    int x, y, next;
    bool flag;
} road[N << 1];

vector<int> adj[N];

void build(int x, int y) {
    tot++;
    road[tot].x = x, road[tot].y = y, road[tot].next = start[x];
    start[x] = tot;
    road[tot].flag = false;
}

int lowbit(int x) {
    return x & (-x);
}

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    for (int i = start[u]; i; i = road[i].next) {
        int v = road[i].y;
        if (!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv > pre[u]) {
                road[i].flag = road[i ^ 1].flag = true;
            }
        } else if (pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    low[u] = lowu;
    return lowu;
}

void get(int x, int fa) {
    if (color[x]) {
        return;
    }
    color[x] = num_color;
    value[num_color] = max(value[num_color], x);
    for (int i = start[x]; i; i = road[i].next) {
        int y = road[i].y;
        if (y == fa) {
            continue;
        }
        if (road[i].flag) {
            continue;
        }
        get(y, x);
    }
    return;
}

void get_dfn(int x, int y) {
    dfn[x] = L[x] = ++dfs_clock;
    for (int i = 0; i < adj[x].size(); i++) {
        int to = adj[x][i];
        if (to == y) {
            continue;
        }
        get_dfn(to, x);
    }
    R[x] = dfs_clock;
    return;
}

int rmq(int x, int y) {
    if (x > y) {
        return 0;
    }
    int id = Log[y - x + 1];
    return max(Max[x][id], Max[y - (1 << id) + 1][id]);
}

void work() {
    scanf("%d%d", &n, &m);
    tot = 1;
    dfs_clock = 0;
    for (int i = 1; i <= n; i++) {
        start[i] = pre[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &p, &q);
        build(p, q), build(q, p);
        need[i] = make_pair(p, q);
    }
    dfs(1, 0);
    dfs_clock = 0;
    for (int i = 1; i <= n; i++) {
        color[i] = 0;
    }
    num_color = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i]) {
            continue;
        }
        num_color++;
        value[num_color] = 0;
        get(i, 0);
    }
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int x = color[need[i].first], y = color[need[i].second];
        if (x == y) {
            continue;
        }
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    get_dfn(1, 0);
    for (int i = 1; i <= num_color; i++) {
        Max[dfn[i]][0] = value[i];
    }
    for (int i = 1; i <= 19; i++) {
        for (int j = 1; (j + (1 << i) - 1) <= num_color; j++) {
            Max[j][i] = max(Max[j][i - 1], Max[j + (1 << i - 1)][i - 1]);
        }
    }

    for (int i = 1; i <= m; i++) {
        int x = color[need[i].first], y = color[need[i].second];
        if (dfn[x] < dfn[y]) {
            swap(x, y);
        }
        if (x == y) {
            puts("0 0");
        } else {
            int Max1 = rmq(L[x], R[x]);
            int Max2 = max(rmq(1, L[x] - 1), rmq(R[x] + 1, num_color));
            Max1 = min(Max1, Max2);
            printf("%d %d\n", Max1, Max1 + 1);
        }
    }
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 2; i <= 100000; i++) {
        Log[i] = Log[i - 1] + (i == lowbit(i));
    }
    for (int i = 1; i <= T; i++) {
        work();
    }
    return 0;
}
