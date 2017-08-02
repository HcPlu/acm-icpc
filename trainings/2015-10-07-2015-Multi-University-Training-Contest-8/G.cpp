#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 105;
const int M = 505;

int init[N][N], goal[N][N];

pair<pair<int, int>, pair<int, int> > a[M];

char type[15];
int ans[M], n, m;
bool visit[M];

bool check(int type, int x, int id) {
    if (type == 1) {
        for (int i = 1; i <= n; i++)
            if (goal[i][x] > 0 && goal[i][x] != id)
                return false;
    } else {
        for (int i = 1; i <= n; i++)
            if (goal[x][i] > 0 && goal[x][i] != id)
                return false;
    }
    return true;
}

void work() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &init[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &goal[i][j]);
    for (int i = 1; i <= m; i++) {
        scanf("%s", type + 1);
        int p, q;
        scanf("%d%d", &p, &q);
        if (type[1] == 'L')
            a[i] = make_pair(make_pair(1, p), make_pair(q, i));
        else
            a[i] = make_pair(make_pair(2, p), make_pair(q, i));
    }
    sort(a + 1, a + 1 + m);
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= m; i++) {
        int now = 0;
        for (int j = 1; j <= m; j++) {
            if (visit[j])
                continue;
            if (check(a[j].first.first, a[j].first.second, a[j].second.first)) {
                now = j;
                break;
            }
        }
        ans[i] = a[now].second.second;
        int x = a[now].first.second;
        if (a[now].first.first == 1) {
            for (int j = 1; j <= n; j++)
                goal[j][x] = -1;
        } else {
            for (int j = 1; j <= n; j++)
                goal[x][j] = -1;
        }
        visit[now] = true;
    }
    reverse(ans + 1, ans + 1 + m);
    for (int i = 1; i <= m; i++)
        printf("%d%s", ans[i], (i == m) ? "\n" : " ");
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
        work();
    return 0;
}
