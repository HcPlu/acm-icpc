#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

const long long MOD = 1000000007;

const int N = 100005;

int test = 0;
pair<int, int> tmp[N];

void work() {
    int n;
    scanf("%d", &n);
    unsigned long long res = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &tmp[i].first, &tmp[i].second);
        res += (unsigned long long)tmp[i].second;
    }
    sort(tmp + 1, tmp + 1 + n);
    reverse(tmp + 1, tmp + 1 + n);
    unsigned long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (unsigned long long)tmp[i].second * res;
        res -= (unsigned long long)tmp[i].second;
    }
    long long CC = 1;
    for (int i = 2; i <= n; i++) {
        CC = (CC * (tmp[i].second + 1)) % MOD;
    }
    printf("Case %d: ", ++test);
    cout << ans << " " << CC << endl;
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
