#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const int N = 2006;
const int mod = 2552;
int C[N][N];
int f[N];
pair<pair<int, int>, pair<int, int> > stick[N];

void fix(int &x) {
    x %= mod;
    x += mod;
    x %= mod;
}

int calc(int x, int y) {
    if (x < 0 || y < 0) {
        return 0;
    }
    return C[x + y + 1][x + 1];
}

void work() {
    int w, h, k;
    scanf("%d%d%d", &w, &h, &k);
    w++, h++;
    for (int d = 1; d <= k; d++) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &stick[i].first.first, &stick[i].first.second);
            scanf("%d%d", &stick[i].second.first, &stick[i].second.second);
            stick[i].first.first++;
            stick[i].first.second++;
            stick[i].second.first++;
            stick[i].second.second++;
        }
        sort(stick + 1, stick + 1 + n);
        for (int i = 1; i <= n; i++) {
            f[i] = calc(stick[i].first.first - 1, stick[i].first.second - 1);
            for (int j = 1; j < i; j++) {
                f[i] = f[i] - f[j] * calc(stick[i].first.first - stick[j].second.first,
                                          stick[i].first.second - stick[j].second.second) % mod;
            }
            fix(f[i]);
        }
        int ans = calc(w - 1, h - 1);
        for (int i = 1; i <= n; i++) {
            ans = ans - f[i] * calc(w - stick[i].second.first, h - stick[i].second.second) % mod;
        }
        fix(ans);
        printf("%d\n", ans);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    C[1][1] = 1;
    for (int i = 2; i < N; i++) {
        C[i][1] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= mod)
                C[i][j] -= mod;
        }
    }
    for (int i = 1; i <= T; i++) {
        work();
    }
    return 0;
}
