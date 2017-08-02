#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>

using namespace std;

const int N = 50005;

int start[N], tot = 0;
int Max[N][19], Min[N][19];
int Log[N];

struct Node {
    int x, y, next, key;
} road[N << 1];
int n, m, up[N];

struct Msg {
    pair<int, int> Max[2];

    void clear() {
        Max[0] = make_pair(-1, -1);
        Max[1] = make_pair(-1, -1);
    }

    void update(pair<int, int> x) {
        for (int i = 0; i <= 1; i++) {
            if (x > Max[i]) {
                swap(x, Max[i]);
            }
        }
        return;
    }

    int Query(int x) {
        int ans = 0;
        for (int i = 0; i <= 1; i++) {
            if (Max[i].second != x) {
                ans = Max[i].first;
                break;
            }
        }
        return ans;
    }
} Max_son[N];

int lowbit(int x) {
    return x & (-x);
}

void build(int x, int y, int key) {
    tot++;
    road[tot].x = x;
    road[tot].y = y;
    road[tot].next = start[x];
    road[tot].key = key;
    start[x] = tot;
}

void dfs(int x, int fa) {
    Max_son[x].update(make_pair(0, x));
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa) {
            continue;
        }
        dfs(to, x);
        Max_son[x].update(make_pair(Max_son[to].Max[0].first + road[i].key, to));
    }
    return;
}

int get_max(int x, int y) {
    int len = Log[y - x + 1];
    return max(Max[x][len], Max[y - (1 << len) + 1][len]);
}

int get_min(int x, int y) {
    int len = Log[y - x + 1];
    return min(Min[x][len], Min[y - (1 << len) + 1][len]);
}

void get_up(int x, int fa, int now_value) {
    up[x] = now_value;
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (to == fa) {
            continue;
        }
        int t = Max_son[x].Query(to);
        get_up(to, x, max(now_value, t) + road[i].key);
    }
    return;
}

void work() {
    tot = 0;
    for (int i = 1; i <= n; i++) {
        start[i] = 0;
        Max_son[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        build(x, y, z);
        build(y, x, z);
    }
    dfs(1, 0);
    get_up(1, 0, 0);
    for (int i = 1; i <= n; i++)
        Max[i][0] = Min[i][0] = max(up[i], Max_son[i].Max[0].first);
    for (int i = 1; i <= Log[n]; i++)
        for (int j = 1; (j + (1 << i) - 1) <= n; j++) {
            Max[j][i] = max(Max[j][i - 1], Max[j + (1 << i - 1)][i - 1]);
            Min[j][i] = min(Min[j][i - 1], Min[j + (1 << i - 1)][i - 1]);
        }

    for (int T = 1; T <= m; T++) {
        int limit;
        scanf("%d", &limit);
        int R = 1;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            while (R <= n && get_max(i, R) - get_min(i, R) <= limit)
                R++;
            ans = max(ans, R - i);
        }
        printf("%d\n", ans);
    }
    return;
}

int main() {
    Log[1] = 0;
    for (int i = 2; i <= 50000; i++)
        Log[i] = Log[i - 1] + (i == lowbit(i));
    while (1) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0)
            break;
        work();
    }
    return 0;
}
