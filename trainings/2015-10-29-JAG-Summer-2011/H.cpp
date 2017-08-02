#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>

#define foreach(it, e) for (__typeof(e.begin()) it = e.begin(); it != e.end(); ++it)

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x)))
#define lowbit(x) ((x) & (-(x)))

using namespace std;

int const INF = INT_MAX / 2;

int const NN = 111;
int const N = NN * NN * 20 * 2;

int n, m;
string str[NN];
int pre[NN][NN][20], suf[NN][NN][20];
vector<pair<int, int> > adj[N];

int tick, top;
int dfn[N], low[N], dist[N], visit[N], mark[N], target[N], stack[N];

inline void tarjan(int x) {
    dist[x] = -INF;
    if (target[x]) {
        dist[x] = max(dist[x], 0);
    }
    dfn[x] = low[x] = tick++;
    stack[top++] = x;
    visit[x] = true;
    for (int i = 0; i < (int)adj[x].size(); ++i) {
        int y = adj[x][i].first;
        int w = adj[x][i].second;
        if (x == y) {
            mark[x] = true;
            continue;
        }
        if (dfn[y] == -1) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (visit[y]) {
            low[x] = min(low[x], dfn[y]);
        }
        dist[x] = max(dist[x], dist[y] + w);
    }
    if (low[x] == dfn[x]) {
        int cnt = 0;
        bool reach = false;
        for (;;) {
            int y = stack[--top];
            visit[y] = false;
            cnt += 1 + mark[y];
            if (dist[y] >= 0) {
                reach = true;
            }
            if (x == y) {
                break;
            }
        }
        if (cnt >= 2 && reach) {
            //cout << x << " " << cnt << endl;
            puts("-1");
            exit(0);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        static char buffer[20];
        scanf("%s", buffer);
        str[i] = buffer;
    }
    int tot = 1;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= (int)str[k].length(); ++j) {
                pre[k][i][j] = tot++;
            }
            for (int j = 0; j <= (int)str[i].length(); ++j) {
                suf[k][i][j] = tot++;
            }
        }
    }


    for (; m--;) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--;
        y--;
        //	prefix  z x  -- y
        for (int z = 0; z < n; ++z) {
            for (int i = 0; i <= (int)str[z].length(); ++i) {
                int j = i - 1, k = 0;
                for (; j >= 0 && k < (int)str[y].length() && str[z][j] == str[y][k]; --j, ++k);
                if (j == -1) {
                    adj[pre[z][x][i]].push_back(make_pair(suf[z][y][(int)str[y].length() - k], str[y].length()));
                }
                if (k == (int)str[y].length()) {
                    adj[pre[z][x][i]].push_back(make_pair(pre[z][y][j + 1], str[y].length()));
                }
            }
        }
        //	suffix  x -- y z
        for (int z = 0; z < n; ++z) {
            for (int i = 0; i <= (int)str[z].length(); ++i) {
                int j = (int)str[x].length() - 1, k = (int)str[z].length() - i;
                for (; j >= 0 && k < (int)str[z].length() && str[x][j] == str[z][k]; --j, ++k);
                if (j == -1) {
                    adj[suf[y][z][i]].push_back(make_pair(suf[x][z][(int)str[z].length() - k], str[x].length()));
                }
                if (k == (int)str[z].length()) {
                    adj[suf[y][z][i]].push_back(make_pair(pre[x][z][j + 1], str[x].length()));
                }
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            target[pre[k][i][0]] = target[suf[k][i][0]] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= (int)str[i].length(); ++j) {
            bool yes = true;
            for (int k = j, l = (int)str[i].length() - 1; k < l; ++k, --l) {
                if (str[i][k] != str[i][l]) {
                    yes = false;
                    break;
                }
            }
            if (yes) {
                adj[0].push_back(make_pair(pre[i][i][j], (int)str[i].length()));
            }
        }
        for (int j = 0; j <= (int)str[i].length(); ++j) {
            bool yes = true;
            for (int k = 0, l = (int)str[i].length() - j - 1; k < l; ++k, --l) {
                if (str[i][k] != str[i][l]) {
                    yes = false;
                    break;
                }
            }
            if (yes) {
                adj[0].push_back(make_pair(suf[i][i][j], (int)str[i].length()));
            }
        }
    }
    /*
for (int i = 0; i < tot; ++i) {
    for (int j = 0; j < (int)adj[i].size(); ++j) {
        printf("%d -> %d\n", i, adj[i][j].first);
    }
}*/

    for (int i = 0; i < tot; ++i) {
        dfn[i] = low[i] = -1;
    }
    tarjan(0);
    printf("%d\n", max(dist[0], 0));
    return 0;
}
