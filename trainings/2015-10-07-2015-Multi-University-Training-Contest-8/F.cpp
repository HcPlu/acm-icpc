#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 222222;

int n, m, stamp;
std::vector<std::pair<int, int> > edge[N];
std::pair<int, int> edges[N];
bool visit[N], mark[N];
int dist[N];

void solve(void) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        visit[i] = false;
        edge[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
        mark[i] = false;
    }
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges[i] = std::make_pair(x, y);
        edge[x].push_back(std::make_pair(y, i));
    }

    visit[1] = true;
    stamp = 0;

    for (int l = 1, r = n; l <= r;) {
        if (visit[l]) {
            dist[l] = stamp++;
            for (int i = 0; i < (int)edge[l].size(); ++i) {
                int y = edge[l][i].first;
                if (visit[y]) {
                    continue;
                }
                visit[y] = true;
                mark[edge[l][i].second] = true;
            }
            l++;
        }
        if (visit[r]) {
            dist[r] = stamp++;
            for (int i = 0; i < (int)edge[r].size(); ++i) {
                int y = edge[r][i].first;
                if (visit[y]) {
                    continue;
                }
                visit[y] = true;
                mark[edge[r][i].second] = true;
            }
            r--;
        }
    }

    for (int i = 1; i <= m; ++i) {
        if (mark[i]) {
            printf("%d\n", dist[edges[i].second] - dist[edges[i].first]);
        } else {
            printf("%d\n", n);
        }
    }
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve());
}
