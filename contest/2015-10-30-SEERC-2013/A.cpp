#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;

const int N = 1005;

pair<int, pair<int, int> > t[N];

int n;
bool exist[N];

void work() {
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &t[i].second.first, &t[i].second.second, &t[i].first);
    sort(t + 1, t + 1 + n);
    reverse(t + 1, t + 1 + n);
    for (int i = 1; i <= n; i++)
        exist[i] = false;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += t[i].first * t[i].second.second;
    }
    for (int i = 1; i <= n; i++) {
        int next = -1;
        for (int j = 1; j <= n; j++) {
            if (exist[j] || j == i)
                continue;
            if (t[j].second.first < t[i].second.second) {
                if (next == -1 || t[next].second.first < t[j].second.first) {
                    next = j;
                }
            }
        }
        if (next == -1)
            continue;
        ans -= t[next].second.first * t[i].first;
        exist[next] = true;
    }
    printf("%d\n", ans);
    return;
}

int main() {
    while (scanf("%d", &n) == 1) {
        work();
    }
    return 0;
}
