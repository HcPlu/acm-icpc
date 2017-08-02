#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int N = 20005;

int team[N], du[N], n, m, start[N], tot = 0;
int dfn[N];

vector<int> adj1[N], adj2[N];

bitset<N> a[N];

void build(int x, int y) {
    adj1[x].push_back(y);
    adj2[y].push_back(x);
    return;
}

void work() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        du[i] = 0, adj1[i].clear(), adj2[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        a[i].reset();
    }
    for (int i = 1; i <= n; i++) {
        a[i][i] = 1;
    }
    tot = 0;
    for (int i = 1; i <= m; i++) {
        int p, q;
        scanf("%d%d", &p, &q);
        build(p, q);
        du[q]++;
    }
    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++) {
        if (!du[i]) {
            team[++tail] = i, dfn[i] = tail;
        }
    }
    while (head < tail) {
        int u = team[++head];
        for (int i = 0; i < adj1[u].size(); i++) {
            du[adj1[u][i]]--;
            if (!du[adj1[u][i]]) {
                team[++tail] = adj1[u][i];
                dfn[adj1[u][i]] = tail;
            }
        }
    }
    int counter = 0;
    vector<pair<int, int> > temp;
    for (int i = 1; i <= n; i++) {
        temp.clear();
        int x = team[i];
        for (int j = 0; j < adj2[x].size(); j++) {
            temp.push_back(make_pair(-dfn[adj2[x][j]], adj2[x][j]));
        }
        sort(temp.begin(), temp.end());
        for (int j = 0; j < temp.size(); j++) {
            int to = temp[j].second;
            if (a[x][to] == 1) {
                counter++;
            }
            a[x] |= a[to];
        }
    }
    printf("%d\n", counter);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        work();
    }
    return 0;
}
