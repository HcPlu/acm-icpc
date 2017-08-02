#include <cstdio>

const long long mod = 1e9 + 7;
const int N = 111111;

int n, m;
int father[N];

int find(int x) {
    if (father[x] != x) {
        father[x] = find(father[x]);
    }
    return father[x];
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        father[x] = y;
    }
}

void solve(void) {
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        merge(x, y);
    }

    int count = 0;
    long long answer = 1;
    for (int i = 1; i <= n; ++i) {
        if (find(i) == i) {
            (answer *= 2) %= mod;
            count++;
        }
    }

    (answer += (count != n)) %= mod;
    printf("%d\n", (int)answer);
}

int main(void) {
    for (; scanf("%d%d", &n, &m) && (n || m); solve()) {
    }
}
