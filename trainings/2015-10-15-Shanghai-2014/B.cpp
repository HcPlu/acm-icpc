#include <iostream>
#include <vector>

using namespace std;
const int N = 11111;
int dx[222];
int dy[222];
struct Step {
    char dir;
    int len;
} step[N];
vector<vector<int> > f;

void solve() {
    int n, m, k;
    char s[22];
    scanf("%d%d%d", &n, &m, &k);
    f = vector<vector<int> >(n + 2, vector<int>(m + 2));
    for (int i = 1; i <= k; i++) {
        scanf("%s %d", s, &step[i].len);
        step[i].dir = s[0];
    }

    int nowx = 1, nowy = 1, newx = 1, newy = 1;
    for (int now = 1; now <= k; now++) {
        newx = nowx + step[now].len * dx[step[now].dir];
        newy = nowy + step[now].len * dy[step[now].dir];
        if (newy == nowy) {

            if (step[now].dir == 'D') {
                f[min(nowx, newx)][nowy]++;
                f[max(newx, nowx)][nowy]--;
            } else {
                f[min(nowx, newx)][nowy]--;
                f[max(newx, nowx)][nowy]++;
            }
        }
        nowx = newx;
        nowy = newy;
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = f[i][j] + f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
            ans += f[i][j] * f[i][j];
        }
    }
    printf("%lld\n", ans);
}

int main() {
    dx['U'] = -1;
    dx['D'] = 1;
    dy['L'] = -1;
    dy['R'] = 1;
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
