#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 500005;

int used[N], n, k, A, B, start[N], tot = 0, f[N];
int U_cnt = 0, exist[N];

struct node {
    int x, y, next;
} road[N * 2];

void build(int x, int y) {
    tot++;
    road[tot].x = x;
    road[tot].y = y;
    road[tot].next = start[x];
    start[x] = tot;
}

int bfs1() {
    static int team[N], dis[N];
    int head = 0, tail = 1;
    for (int i = 1; i <= n; i++)
        used[i] = false;
    used[1] = true;
    dis[1] = 0;
    team[1] = 1;
    while (head < tail) {
        int u = team[++head];
        for (int i = start[u]; i; i = road[i].next) {
            int to = road[i].y;
            if (used[to])
                continue;
            dis[to] = dis[u] + 1;
            if (to == n) {
                return dis[to];
            }
            used[to] = true;
            team[++tail] = to;
        }
    }
    return 0x3f3f3f3f;
}

int find(int x) {
    if (x == f[x]) {
        return f[x];
    }
    f[x] = find(f[x]);
    return f[x];
}

void delet(int x) {
    find(x);
    find(x + 1);
    f[x + 1] = f[x];
}

int bfs2() {
    static int team[N], dis[N];
    int head = 0, tail = 1;
    for (int i = 1; i <= n; i++)
        used[i] = false;
    for (int i = 1; i <= n; i++)
        f[i] = i;
    dis[1] = 0;
    used[1] = true;
    delet(1);
    team[1] = 1;
    used[0] = true;
    while (head < tail) {
        int u = team[++head];
        U_cnt++;
        for (int i = start[u]; i; i = road[i].next) {
            exist[road[i].y] = U_cnt;
        }
        for (int now = n; now > 0; now = find(now) - 1) {
            if (used[now])
                continue;
            if (exist[now] == U_cnt)
                continue;
            if (now == n) {
                return dis[u] + 1;
            }
            delet(now);
            used[now] = true;
            team[++tail] = now;
            dis[now] = dis[u] + 1;
        }
    }
    return 0x3f3f3f3f;
}

void work() {
    tot = 0;
    for (int i = 1; i <= n; i++)
        start[i] = 0;
    bool flag = false;
    for (int i = 1; i <= k; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        build(x, y);
        build(y, x);
        if (x == 1 && y == n) {
            flag = true;
        }
        if (x == n && y == 1) {
            flag = false;
        }
    }
    long long ans;
    if (!flag) {
        int t = bfs1();
        ans = min(1LL * t * A, 1LL * B);
        printf("%d\n", (int)ans);
    } else {
        int t = bfs2();
        ans = min(1LL * t * B, 1LL * A);
        printf("%d\n", (int)ans);
    }
    return;
}

int main() {
    while (scanf("%d%d%d%d", &n, &k, &A, &B) == 4) {
        work();
    }
    return 0;
}
