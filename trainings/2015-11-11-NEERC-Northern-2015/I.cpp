#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const int N = 100005;

vector<int> queue;
multiset<pair<int, int> > adj[N];

int n, m, degree[N];
int ans[N], value[N];
vector<pair<int, int> > bel[N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].insert(make_pair(b, c));
        adj[c].insert(make_pair(b, a));

        bel[a].push_back(make_pair(b, c));
        bel[c].push_back(make_pair(b, a));
        degree[b] += 2;
    }
    for (int i = 1; i <= n; i++) {
        if (!degree[i]) {
            queue.push_back(i);
        }
    }
    for (int head = 0; head < queue.size(); head++) {
        int now = queue[head];
        multiset<pair<int, int> >::iterator it = adj[now].begin();
        for (; it != adj[now].end(); it++) {
            pair<int, int> t = (*it);
            degree[t.first] -= 2;
            adj[t.second].erase(make_pair(now, t.first));
            if (degree[t.first] == 0) {
                queue.push_back(t.first);
            }
        }
    }
    int L = 0, R = 0;
    for (int i = 1; i <= n; i++) {
        ans[i] = -0x3f3f3f3f;
    }
    for (int head = queue.size() - 1; head >= 0; head--) {
        int now = queue[head];
        int counter1 = 0, counter2 = 0;
        for (int i = 0; i < bel[now].size(); i++) {
            if (ans[bel[now][i].first] == -0x3f3f3f3f) {
                continue;
            }
            if (ans[bel[now][i].second] == -0x3f3f3f3f) {
                continue;
            }
            if (ans[bel[now][i].first] < ans[bel[now][i].second]) {
                counter1++;
            } else {
                counter2++;
            }
        }
        if (counter1 > counter2) {
            ans[now] = --L;
        } else {
            ans[now] = R++;
        }
    }
    for (int i = 1; i <= n; i++) {
        ans[i] -= (L - 1);
    }
    for (int i = 1; i <= n; i++) {
        value[ans[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d%s", value[i], (i == n) ? "\n" : " ");
    }
    return 0;
}
