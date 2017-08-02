#include <iostream>
#include <vector>

using namespace std;

const int N = 2555;
vector<int> edge[N];
vector<int> arrival[N];
int dist[N], from[N], id[N][N];
int on_cost[N], off_cost[N], cost[N], step[N], total, n, m, steps;
int dp[N][2];
char graph[55][55];

void add(int x, int y) {
    edge[x].push_back(y);
}

int go(int source, int target, int base) {
    for (int i = 1; i <= total; i++) {
        dist[i] = -1;
    }
    dist[source] = 0;
    vector<int> queue;
    queue.push_back(source);
    for (int head = 0; head < (int)queue.size(); head++) {
        int now = queue[head];
        if (now == target)
            break;
        for (int i = 0; i < (int)edge[now].size(); i++) {
            int y = edge[now][i];
            if (dist[y] == -1) {
                dist[y] = dist[now] + 1;
                queue.push_back(y);
                from[y] = now;
            }
        }
    }
    for (int i = target; i != source; i = from[i]) {
        arrival[i].push_back(base + dist[i]);
    }
    return dist[target];
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d", &steps);
    for (int i = 1; i <= n; i++) {
        scanf("%s", graph[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (graph[i][j] == '.')
                id[i][j] = ++total;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            if (graph[i][j] == '.' && graph[i][j + 1] == '.') {
                add(id[i][j], id[i][j + 1]);
                add(id[i][j + 1], id[i][j]);
            }
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            if (graph[i][j] == '.' && graph[i + 1][j] == '.') {
                add(id[i][j], id[i + 1][j]);
                add(id[i + 1][j], id[i][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &cost[id[i][j]]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &on_cost[id[i][j]]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &off_cost[id[i][j]]);
        }
    }

    for (int i = 1; i <= steps; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x++;
        y++;
        step[i] = id[x][y];
    }

    arrival[step[1]].push_back(0);
    int now = 0;
    for (int i = 1; i < steps; i++) {
        now += go(step[i], step[i + 1], now);
    }

    int answer = 0;

    for (int i = 1; i <= total; i++) {
        if (arrival[i].size() == 0) {
            continue;
        }

        dp[0][0] = on_cost[i] + off_cost[i];
        dp[0][1] = on_cost[i];
        for (int j = 1; j < (int)arrival[i].size(); j++) {
            dp[j][1] = min(dp[j - 1][0] + on_cost[i], dp[j - 1][1] + cost[i] * (arrival[i][j] - arrival[i][j - 1]));
            dp[j][0] = min(dp[j - 1][0] + on_cost[i] + off_cost[i],
                           dp[j - 1][1] + cost[i] * (arrival[i][j] - arrival[i][j - 1]) + off_cost[i]);
        }
        answer += dp[(int)arrival[i].size() - 1][0];
    }

    printf("%d\n", answer);
    return 0;
}
