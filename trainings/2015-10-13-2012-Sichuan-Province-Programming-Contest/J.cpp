#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

typedef long long LL;

struct Node {
    int x, y, key, next;
} road[N << 1];

int father[N][20], tot = 0, start[N];
int team[N], dis[N], deep[N];
int n, Q;
bool used[N];

void build(int x, int y, int key) {
    tot++;
    road[tot].x = x;
    road[tot].y = y;
    road[tot].key = key;
    road[tot].next = start[x];
    start[x] = tot;
    return;
}

void bfs(int x) {
    int head = 0, tail = 1;
    team[1] = x;
    used[x] = true;
    deep[x] = 1;
    dis[x] = 0;
    father[x][0] = 0;
    while (head < tail) {
        int u = team[++head];
        for (int i = start[u]; i; i = road[i].next) {
            int to = road[i].y;
            if (used[to])
                continue;
            deep[to] = deep[u] + 1;
            dis[to] = dis[u] + road[i].key;
            team[++tail] = to;
            father[to][0] = u;
            used[to] = true;
        }
    }
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            father[j][i] = father[father[j][i - 1]][i - 1];
    return;
}

int lca(int x, int y) {
    if (deep[x] < deep[y]) {
        swap(x, y);
    }
    for (int i = 19; i >= 0; i--) {
        if (deep[father[x][i]] >= deep[y]) {
            x = father[x][i];
        }
    }
    //	printf("%d %d\n", x, father[x][0]);
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--) {
        if (father[x][i] != father[y][i]) {
            x = father[x][i];
            y = father[y][i];
        }
    }
    return father[x][0];
}

int get_dis(int x, int y) {
    int t = lca(x, y);
    return dis[x] + dis[y] - 2 * dis[t];
}

int point[5];

void work() {
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; i++)
        start[i] = used[i] = 0;
    tot = 0;
    for (int i = 1; i < n; i++) {
        int p, q, t;
        scanf("%d%d%d", &p, &q, &t);
        build(p, q, t);
        build(q, p, t);
    }

    int cost;

    scanf("%d%d%d", &point[1], &point[2], &cost);

    bfs(1);

    //get_dis(3, 5);
    //return ;

    for (int i = 1; i <= Q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        long long ans = get_dis(x, y);
        long long temp = ans;
        for (int S = 1; S <= 2; S++)
            for (int T = 1; T <= 2; T++) {
                if (S == T)
                    continue;
                //		printf("%d %d\n", get_dis(3, 5), get_dis(point[T], y));
                ans = min(ans, 1LL * get_dis(point[S], x) + get_dis(point[T], y) + cost);
            }
        printf("%lld\n", temp - ans);
    }
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d:\n", i);
        work();
    }
}
