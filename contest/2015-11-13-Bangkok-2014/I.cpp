#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

const int N = 540;
const int M = 16000 * 2;

namespace MC {
    struct EdgeList {
        int size;
        int last[N];
        int succ[M], other[M], flow[M];

        void clear(int n) {
            size = 0;
            fill(last, last + n, -1);
        }

        void add(int x, int y, int c) {
            succ[size] = last[x];
            last[x] = size;
            other[size] = y;
            flow[size++] = c;
        }
    } e;

    int n, source, target;
    int dist[N], curr[N];

    void add(int x, int y, int c) {
        e.add(x, y, c);
        e.add(y, x, 0);
    }

    bool relabel() {
        std::vector<int> queue;
        for (int i = 0; i < n; ++i) {
            curr[i] = e.last[i];
            dist[i] = -1;
        }
        queue.push_back(target);
        dist[target] = 0;
        for (int head = 0; head < (int)queue.size(); ++head) {
            int x = queue[head];
            for (int i = e.last[x]; ~i; i = e.succ[i]) {
                int y = e.other[i];
                if (e.flow[i ^ 1] && dist[y] == -1) {
                    dist[y] = dist[x] + 1;
                    queue.push_back(y);
                }
            }
        }
        return ~dist[source];
    }

    int dfs(int x, int answer) {
        if (x == target) {
            return answer;
        }
        int delta = answer;
        for (int &i = curr[x]; ~i; i = e.succ[i]) {
            int y = e.other[i];
            if (e.flow[i] && dist[x] == dist[y] + 1) {
                int number = dfs(y, std::min(e.flow[i], delta));
                e.flow[i] -= number;
                e.flow[i ^ 1] += number;
                delta -= number;
            }
            if (delta == 0) {
                break;
            }
        }
        return answer - delta;
    }

    int solve() {
        int answer = 0;
        while (relabel()) {
            answer += dfs(source, INT_MAX);
        }
        return answer;
    }
};

void work() {
    int p, s, c, m;
    scanf("%d%d%d%d", &p, &s, &c, &m);
    MC::source = 0;
    MC::target = p + s + 1;
    MC::n = p + s + 2;
    MC::e.clear(MC::n);
    for (int i = 1; i <= p; i++) {
        MC::add(0, i, 1);
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;
        MC::add(a + 1, b + p + 1, 1);
    }
    for (int i = 1; i <= s; i++) {
        MC::add(i + p, MC::target, c);
    }
    printf("%d\n", MC::solve());
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
