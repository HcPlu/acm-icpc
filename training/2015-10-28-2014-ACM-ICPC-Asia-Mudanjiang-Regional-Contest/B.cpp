#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 211111;

int n;
vector<int> edge[N];
int dist[N], prev[N];
vector<int> path;

int far(int source, vector<int> &path) {
    fill(dist + 1, dist + n + 1, -1);
    vector<int> queue;

    queue.push_back(source);
    dist[source] = 0;
    prev[source] = -1;

    for (int head = 0; head < (int)queue.size(); ++head) {
        int x = queue[head];
        for (int i = 0; i < (int)edge[x].size(); ++i) {
            int y = edge[x][i];
            if (dist[y] == -1) {
                dist[y] = dist[x] + 1;
                prev[y] = x;
                queue.push_back(y);
            }
        }
    }

    int target = source;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] > dist[target]) {
            target = i;
        }
    }

    path.clear();
    for (int i = target; i != source; i = prev[i]) {
        path.push_back(i);
    }
    path.push_back(source);

    return target;
}


pair<int, pair<int, int> > check(int len) {
    if (len >= (int)path.size()) {
        return make_pair(1, make_pair(path[0], path.back()));
    }

    int a = path[len];
    int b = path[(int)path.size() - len - 1];
    vector<int> queue;
    queue.push_back(a);
    queue.push_back(b);
    for (int i = 1; i <= n; i++) {
        dist[i] = -1;
    }
    dist[a] = 0;
    dist[b] = 0;
    for (int head = 0; head < (int)queue.size(); head++) {
        int x = queue[head];
        for (int i = 0; i < (int)edge[x].size(); i++) {
            int y = edge[x][i];
            if (dist[y] == -1) {
                dist[y] = dist[x] + 1;
                queue.push_back(y);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] > len) {
            return make_pair(0, make_pair(0, 0));
        }
    }

    return make_pair(1, make_pair(a, b));
}

void solve(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        edge[i].clear();
    }
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    int a = far(1, path);
    int b = far(a, path);

    int left = 0, right = n;
    int ans1, ans2;
    while (left < right) {
        int mid = left + right >> 1;
        pair<int, pair<int, int> > answer = check(mid);
        if (answer.first == 1) {
            right = mid;
            ans1 = answer.second.first;
            ans2 = answer.second.second;
        } else {
            left = mid + 1;
        }
    }

    if (ans1 > ans2) {
        swap(ans1, ans2);
    }

    if (ans1 == ans2) {
        ans2 = ans2 % n + 1;
    }

    printf("%d %d %d\n", left + right >> 1, ans1, ans2);
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve());
}
