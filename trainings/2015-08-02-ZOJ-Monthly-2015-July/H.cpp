#include <iostream>

using namespace std;

const int INF = 233333;

const int N = 200000;

int n, m, q;
pair<int, int> T[N];

pair<int, int> update(pair<int, int> p1, pair<int, int> p2) {
    pair<int, int> ret;
    ret.first = min(p1.first, p2.first);
    ret.second = min(max(p1.first, p2.first), min(p1.second, p2.second));

    return ret;
}

int lowbit(int x) {
    return x & (-x);
}

void add(int pos, int change) {
    for (int i = pos; i <= n + 1; i += lowbit(i)) {
        T[i] = update(T[i], make_pair(change, INF));
    }
}

pair<int, int> query(int pos) {
    pair<int, int> ret = make_pair(INF, INF);
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ret = update(ret, T[i]);
    }
    return ret;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &q) == 3) {
        for (int i = 1; i <= n + 1; i++) {
            T[i] = make_pair(INF, INF);
        }
        for (int i = 1; i <= m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            add(n + 1 - x, y);
        }

        for (int i = 1; i <= q; i++) {
            int pos;
            scanf("%d", &pos);
            int ans = pos - query(n + 1 - pos).second;
            if (ans <= 0) {
                puts("0");
            } else {
                printf("%d\n", ans);
            }

        }
    }

    return 0;
}
