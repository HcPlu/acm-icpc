#include <iostream>
#include <vector>


using namespace std;
const int INF = 1 << 29;
const int N = 433;
int g[N][N], best[20][1 << 18], dist[20][20], n, m, limit, num, s, cost[N], a[N];
int inq[20][1 << 18];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            g[i][j] = INF;
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = g[v][u] = w;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && j != k && i != k) {
                    g[i][j] = min(g[i][k] + g[k][j], g[i][j]);
                }
            }
        }
    }

    for (int i = 1; i <= num; i++) {
        scanf("%d%d", &a[i], &cost[i]);
    }
    a[num + 1] = s;
    cost[num + 1] = 0;
    for (int i = 1; i <= num + 1; i++) {
        for (int j = 1; j <= num + 1; j++) {
            dist[i][j] = g[a[i]][a[j]];
        }
    }

    for (int i = 1; i <= num + 1; i++) {
        for (int j = 0; j < (1 << num); j++) {
            best[i][j] = INF;
            inq[i][j] = 0;
        }
    }


    vector<pair<int, int> > queue;
    queue.push_back(make_pair(num + 1, 0));
    best[num + 1][0] = 0;
    inq[num + 1][0] = 1;

    for (int head = 0; head < (int)queue.size(); head++) {
        int now = queue[head].first;
        int state = queue[head].second;
        int nowdist = best[now][state];
        inq[now][state] = 0;
        for (int i = 1; i <= num; i++) {
            if (best[i][state | (1 << i - 1)] > nowdist + dist[now][i] + cost[i]) {
                best[i][state | (1 << i - 1)] = nowdist + dist[now][i] + cost[i];
                if (!inq[i][state || (1 << i - 1)]) {
                    queue.push_back(make_pair(i, state | (1 << i - 1)));
                    inq[i][state | (1 << i - 1)] = 1;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= num; i++) {
        for (int j = 0; j < (1 << num); j++) {
            if (best[i][j] + dist[i][num + 1] <= limit) {
                ans = max(ans, __builtin_popcount(j));
            }
        }
    }

    printf("%d\n", ans);
}

int main() {
    for (; scanf("%d%d%d%d%d", &n, &m, &num, &s, &limit) && (n > 0 && m > 0); solve());
    return 0;
}
