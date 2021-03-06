#pragma comment(linker, "/STACK:102400000,102400000")

#include <cstdio>
#include <iostream>

using namespace std;

const long long INF = 1000000000000000000LL;

int l, r;
long long ans = 0;

void dfs(long long x, long long y) {
    if (y >= ans) {
        return;
    }
    if (x < 0) {
        return;
    }
    if (x == 0) {
        ans = min(ans, y);
        return;
    }
    if (x < y - x + 1) {
        return;
    }
    dfs(2LL * (x - 1) - y, y);
    dfs(2LL * (x - 1) - y + 1, y);
    dfs(x, 2LL * y - x);
    dfs(x, 2LL * y + 1 - x);
    return;
}

void work() {
    ans = INF;
    dfs(l, r);
    if (ans == INF) {
        puts("-1");
    } else {
        printf("%lld\n", ans);
    }
    return;
}

int main() {
    while (scanf("%d%d", &l, &r) == 2) {
        work();
    }
    return 0;
}
	
