#include <cstring>
#include <cassert>
#include <cstdio>
#include <algorithm>

using namespace std;

__inline bool lss(int x, int y) {
    return x < y;
}

__inline bool grtr(int x, int y) {
    return x > y;
}

const int N(211), M(51111);
int infi(1e9), LIM(50111);

int getInt() {
    int x(0);
    char c;
    c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - 48;
        c = getchar();
    }
    return x;
}

pair<int, int> vec[M];
int f[M], g[M], t[N], u[N], v[N], x[N], y[N], z[N];

void dp(int f[M], int n, int t[N], int u[N], int v[N]) {
    for (int i(1); i <= LIM; i++) {
        f[i] = infi;
    }
    f[0] = 0;
    for (int i(1); i <= n; i++) {
        for (int base(0); base < t[i]; base++) {
            f[base] = f[base];
            int ed(0);
            vec[ed++] = make_pair(0, f[base]);
            if (f[base] < 0) {
                printf("%d %d\n", base, i);
            }
            int op(0);
            for (int j(1); j * t[i] + base <= LIM; j++) {
                while (op < ed && vec[op].first < j - v[i]) {
                    op++;
                }
                while (op < ed && f[base + j * t[i]] - j * u[i] <= vec[ed - 1].second) {
                    ed--;
                }
                assert(vec[op].first < j);
                vec[ed++] = make_pair(j, f[base + j * t[i]] - j * u[i]);
                f[base + j * t[i]] = vec[op].second + j * u[i];
                if (f[base + j * t[i]] < 0) {
                    printf("%d %d %d %d\n", op, vec[op].first, vec[op].second, j);
                }
                assert(f[base + j * t[i]] > 0);
            }
        }
    }
}

void dp1(int f[M], int n, int t[N], int u[N], int v[N]) {
    for (int i(1); i <= LIM; i++) {
        f[i] = -infi;
    }
    f[0] = 0;
    for (int i(1); i <= n; i++) {
        for (int base(0); base < t[i]; base++) {
            f[base] = f[base];
            int ed(0);
            vec[ed++] = make_pair(0, f[base]);
            int op(0);
            for (int j(1); j * t[i] + base <= LIM; j++) {
                while (op < ed && vec[op].first < j - v[i]) {
                    op++;
                }
                while (op < ed && f[base + j * t[i]] - j * u[i] >= vec[ed - 1].second) {
                    ed--;
                }
                vec[ed++] = make_pair(j, f[base + j * t[i]] - j * u[i]);
                f[base + j * t[i]] = vec[op].second + j * u[i];
            }
        }
    }
}

int main() {
    int tests;
    tests = getInt();
    for (int qq(1); qq <= tests; qq++) {
        int n, m, p;
        n = getInt();
        m = getInt();
        p = getInt();
        for (int i(1); i <= n; i++) {
            t[i] = getInt();
            u[i] = getInt();
            v[i] = getInt();

        }
        for (int i(1); i <= m; i++) {
            x[i] = getInt();
            y[i] = getInt();
            z[i] = getInt();
        }
        LIM = p + 100;
        dp(f, n, t, u, v);
        int minSize(infi);
        for (int i(p); i <= LIM; i++) {
            minSize = min(minSize, f[i]);
        }
        LIM = min(50000, minSize >= infi ? infi : minSize * 100);
        if (minSize == infi) {
            printf("TAT\n");
            continue;
        }
        dp1(g, m, y, x, z);
        int minCost(infi);
        for (int i(0); i <= LIM; i++) {
            if (g[i] >= minSize) {
                minCost = i;
                break;
            }
        }
        if (minCost == infi) {
            printf("TAT\n");
        } else {
            printf("%d\n", minCost);
        }
    }
}
