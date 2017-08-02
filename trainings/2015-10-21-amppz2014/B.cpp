#include <iostream>
#include <vector>

using namespace std;
const int N = 333333;
const int INF = 1 << 30;
int n, s, m;
int dist[N], from[N], u[N], v[N], inq[N], fa[N], ans[N], c[N];
vector<pair<int, int> > adj[N];
vector<int> queue;

int getfa(int x) {
    return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

int main() {
    scanf("%d%d%d", &n, &s, &m);
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    for (int i = 1; i <= s; i++) {
        int x;
        scanf("%d", &x);
        dist[x] = 0;
        from[x] = x;
        queue.push_back(x);
        inq[x] = 1;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u[i], &v[i], &c[i]);
        adj[u[i]].push_back(make_pair(v[i], c[i]));
        adj[v[i]].push_back(make_pair(u[i], c[i]));
    }

    for (int head = 0; head < (int)queue.size(); head++) {
        int now = queue[head];
        inq[now] = 0;
        for (int i = 0; i < (int)adj[now].size(); i++) {
            int to = adj[now][i].first, w = adj[now][i].second;
            if (dist[to] > dist[now] + w) {
                dist[to] = dist[now] + w;
                from[to] = from[now];
                if (!inq[to]) {
                    queue.push_back(to);
                    inq[to] = 1;
                }
            }
        }
    }
    vector<pair<int, pair<int, int> > > new_edge;
    for (int i = 1; i <= m; i++) {
        if (dist[u[i]] < INF && dist[v[i]] < INF && from[u[i]] != from[v[i]]) {
            new_edge.push_back(make_pair(dist[u[i]] + dist[v[i]] + c[i], make_pair(from[u[i]], from[v[i]])));
        }
    }

    sort(new_edge.begin(), new_edge.end());
    int query;
    scanf("%d", &query);
    vector<pair<pair<int, int>, pair<int, int> > > querys;

    for (int i = 1; i <= query; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        querys.push_back(make_pair(make_pair(z, i), make_pair(x, y)));
    }

    sort(querys.begin(), querys.end());
    int now = 0;
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 0; i < (int)querys.size(); i++) {
        for (; new_edge[now].first <= querys[i].first.first && (now < (int)new_edge.size()); now++) {
            int fx = getfa(new_edge[now].second.first);
            int fy = getfa(new_edge[now].second.second);
            fa[fx] = fy;
        }
        ans[querys[i].first.second] = (getfa(querys[i].second.first) == getfa(querys[i].second.second));
    }

    for (int i = 1; i <= query; i++) {
        puts(ans[i] ? "TAK" : "NIE");
    }

    return 0;
}
