#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

const int N = 300005;

int n, m, start[N], tot = 0;
int father[N][33], deep[N];
pair<pair<int, int>, int> t[N];

struct Node {
    int x, y, next;
} road[N << 1];

void build(int x, int y) {
    tot++;
    road[tot].x = x;
    road[tot].y = y;
    road[tot].next = start[x];
    start[x] = tot;
}

void dfs(int x, int fa) {
    deep[x] = deep[fa] + 1;
    father[x][0] = fa;
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa) {
            continue;
        }
        dfs(to, x);
    }
    return;
}

int get_lca(int x, int y) {
    if (deep[x] < deep[y]) {
        swap(x, y);
    }
    for (int i = 20; i >= 0; i--) {
        if (deep[father[x][i]] >= deep[y]) {
            x = father[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 20; i >= 0; i--) {
        if (father[x][i] != father[y][i]) {
            x = father[x][i];
            y = father[y][i];
        }
    }
    return father[x][0];
}

int dis(int x, int y) {
    int t = get_lca(x, y);
    return deep[x] + deep[y] - 2 * deep[t];
}

int realdis(int x, int y, int z) {
    return dis(x, z) + dis(z, y);
}

void work() {
    scanf("%d %d", &n, &m);
    tot = 0;
    for (int i = 1; i <= n; i++) {
        start[i] = 0;
    }
    for (int i = 1; i <= n - 1; i++) {
        int p, q;
        scanf("%d%d", &p, &q);
        build(p, q);
        build(q, p);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &t[i].first.first, &t[i].first.second, &t[i].second);
    }
    deep[1] = 1;
    dfs(1, 0);
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= n; j++) {
            father[j][i] = father[father[j][i - 1]][i - 1];
        }
    }
    int now = 1;
    for (int i = 1; i <= m; i++) {
        int a = t[i].first.first, b = t[i].first.second, d = t[i].second;
        while (1) {
            int base = realdis(a, b, now);
            bool flag = false;
            if (base <= d) {
                break;
            }
            for (int j = start[now]; j; j = road[j].next) {
                if (realdis(a, b, road[j].y) < base) {
                    flag = true;
                    now = road[j].y;
                    break;
                }
            }
            int dist = realdis(a, b, now);
            if (flag && dist <= d) {
                break;
            }
            if (flag && dist > d) {
                continue;
            }
            if (now == 1) {
                break;
            }
            now = father[now][0];
        }
    }
    for (int i = 1; i <= m; i++) {
        int a = t[i].first.first, b = t[i].first.second, d = t[i].second;
        int dist = realdis(a, b, now);
        if (dist > d) {
            puts("NIE");
            return;
        }
    }
    printf("TAK %d\n", now);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        work();
    }
}
