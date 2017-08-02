#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<queue>

using namespace std;

const int N = 222222;

typedef long long LL;

pair<pair<int, int>, int> a[N];

int n, tot, start[N];

struct Node {
    int x, y, next;
    LL key;
} road[N * 16];

int get_value(int x, int y) {
    pair<int, int> tx = a[x].first, ty = a[y].first;
    return min(abs(tx.first - ty.first), abs(tx.second - ty.second));
}

void build(int x, int y, int key) {
    tot++;
    road[tot].x = x;
    road[tot].y = y;
    road[tot].key = 1LL * key;
    road[tot].next = start[x];
    start[x] = tot;
}

void add(int x, int y) {
    int t = get_value(x, y);
    build(a[x].second, a[y].second, t);
    build(a[y].second, a[x].second, t);
}

void prepare() {
    sort(a + 1, a + 1 + n);
    int next = -1;
    for (int i = 1, j; i <= n; i = j) {
        for (j = i; a[j].first == a[i].first && j <= n; j++);
        for (int k = i; k + 1 < j; k++) {
            add(k, k + 1);
        }
        add(j - 1, i);
        if (next != -1)
            add(next, i);
        next = i;
    }
    add(1, next);
    return;
}

long long solve(int source, int target) {
    static long long dist[N];
    static bool certain[N];

    std::priority_queue<std::pair<long long, int> > heap;
    for (int i = 1; i <= n; ++i) {
        dist[i] = LONG_LONG_MAX;
        certain[i] = false;
    }

    dist[source] = 0;
    heap.push(std::make_pair(-dist[source], source));

    while (!heap.empty()) {
        int x = heap.top().second;
        heap.pop();
        if (x == target) {
            return dist[x];
        }
        if (certain[x]) {
            continue;
        }
        certain[x] = true;
        for (int i = start[x]; i; i = road[i].next) {
            int y = road[i].y;
            if (dist[y] > dist[x] + road[i].key) {
                dist[y] = dist[x] + road[i].key;
                heap.push(std::make_pair(-dist[y], y));
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first.first, &a[i].first.second);
        a[i].second = i;
    }
    prepare();
    for (int i = 1; i <= n; i++)
        swap(a[i].first.first, a[i].first.second);
    prepare();
    long long t = solve(1, n);
    cout << t << endl;
    return 0;
}
