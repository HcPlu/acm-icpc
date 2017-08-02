#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int N = 305;

int n, m, k, tot = 0;
int start[N];
bool used[N];

vector<pair<int, int> > seq;
vector<pair<int, int> > exist[N];

struct Node {
    int x, y, next;
} road[N * N * 2];

void build(int x, int y) {
    tot++;
    road[tot].x = x, road[tot].y = y, road[tot].next = start[x];
    start[x] = tot;
}

void dfs(int x) {
    used[x] = true;
    for (int i = 0; i < exist[x].size(); i++) {
        seq.push_back(exist[x][i]);
    }
    for (int i = start[x]; i; i = road[i].next) {
        int to = road[i].y;
        if (used[to])
            continue;
        dfs(to);
    }
    return;
}

void work() {
    tot = 0;
    for (int i = 1; i <= n; i++) {
        start[i] = 0;
        exist[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        build(x, y);
        build(y, x);
    }
    for (int i = 1; i <= k; i++) {
        int p, q, t;
        scanf("%d%d%d", &p, &q, &t);
        exist[p].push_back(make_pair(t, q));
    }
    for (int i = 1; i <= n; i++)
        used[i] = false;
    int result = 0;
    for (int now = 1; now <= n; now++) {
        if (used[now])
            continue;
        seq.clear();
        dfs(now);
        if (seq.size() == 0) {
            continue;
        }
        sort(seq.begin(), seq.end());
        reverse(seq.begin(), seq.end());
        int ans = seq[0].first + 1;
        int sum = 0;
        for (int i = 0, j; i < seq.size(); i = j) {
            j = i;
            for (; j < seq.size() && seq[j].first == seq[i].first; sum += seq[j].second, j++);
            if ((j) < seq.size()) {
                ans = min(ans, max(seq[j].first + 1, sum));
            } else {
                ans = min(ans, max(0, sum));
            }
        }
        result += ans;
    }
    printf("%d\n", result);
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3 && (n || m || k)) {
        work();
    }
    return 0;
}
