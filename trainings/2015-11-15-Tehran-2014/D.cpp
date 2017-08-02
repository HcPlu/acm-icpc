#include <iostream>
#include <vector>

using namespace std;
const int N = 222;
const int INF = 1 << 30;

vector<pair<int, int> > adj[N];
int dist[N], f[N], inqueue[N];;
int n, source, target;

void add(int x, int y, int w) {
    adj[x].push_back(make_pair(y, w));
    adj[y].push_back(make_pair(x, w));
}

void spfa() {
    for (int i = 0; i <= 200; i++) {
        dist[i] = INF;
        inqueue[i] = 0;
    }
    vector<int> queue;
    queue.push_back(source);
    dist[source] = 0;
    inqueue[source] = 1;
    for (int head = 0; head < (int)queue.size(); head++) {
        int x = queue[head];
        inqueue[x] = 0;
        for (int i = 0; i < (int)adj[x].size(); i++) {
            int to = adj[x][i].first;
            if (dist[to] > dist[x] + adj[x][i].second) {
                dist[to] = dist[x] + adj[x][i].second;
                if (!inqueue[to]) {
                    inqueue[to] = 1;
                    queue.push_back(to);
                }
            }
        }
    }
    printf("%d\n", dist[target]);
}

void solve() {
    for (int i = 0; i <= 200; i++) {
        adj[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        int m;
        scanf("%d", &m);
        for (int j = 1; j <= m; j++) {
            scanf("%d", &f[j]);
        }
        sort(f + 1, f + m + 1);
        for (int j = 1; j < m; j++) {
            add(f[j], f[j + 1], f[j + 1] - f[j]);
        }
    }
    spfa();
}

int main() {
    for (; scanf("%d%d%d", &n, &source, &target) && (n > 0 || source > 0 || target > 0); solve());
    return 0;
}
