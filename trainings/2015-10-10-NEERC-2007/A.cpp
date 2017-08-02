#include <iostream>
#include <cmath>

using namespace std;
const int N = 333;
double labelx[N], labely[N];
int match[N], n, ans[N];
double graph[N][N], slack[N];
bool visitx[N], visity[N];
struct Point {
    int x, y;
} white[N], black[N];

const double eps = 1e-8;

double sqr(double x) {
    return x * x;
}

double dist(int a, int b) {
    return sqrt(sqr(white[a].x - black[b].x) + sqr(white[a].y - black[b].y));
}

bool dfs(int x) {
    visitx[x] = true;
    for (int y = 0; y < n; ++y) {
        if (visity[y]) {
            continue;
        }
        double delta = labelx[x] + labely[y] - graph[x][y];
        if (fabs(delta) < eps) {
            visity[y] = true;
            if (match[y] == -1 || dfs(match[y])) {
                match[y] = x;
                return true;
            }
        } else {
            slack[y] = min(slack[y], delta);
        }
    }
    return false;
}

void km() {
    for (int i = 0; i < n; i++) {
        match[i] = -1;
        labelx[i] = INT_MIN;
        labely[i] = 0;
        for (int j = 0; j < n; j++) {
            labelx[i] = max(labelx[i], graph[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        while (true) {
            fill(visitx, visitx + n, 0);
            fill(visity, visity + n, 0);
            for (int j = 0; j < n; j++) {
                slack[j] = INT_MAX;
            }
            if (dfs(i)) {
                break;
            }
            double delta = INT_MAX;
            for (int j = 0; j < n; j++) {
                if (!visity[j]) {
                    delta = min(delta, slack[j]);
                }
            }

            for (int j = 0; j < n; j++) {
                if (visitx[j]) {
                    labelx[j] -= delta;
                }
                if (visity[j]) {
                    labely[j] += delta;
                } else {
                    slack[j] -= delta;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ans[match[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i] + 1);
    }
}

int flg;

void solve() {
    if (flg)
        puts("");
    else {
        flg = 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &white[i].x, &white[i].y);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d%d", &black[i].x, &black[i].y);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = -dist(i, j);
        }
    }
    km();
}

int main() {
    flg = 0;
    for (; scanf("%d", &n) != EOF; solve());
    return 0;
}
