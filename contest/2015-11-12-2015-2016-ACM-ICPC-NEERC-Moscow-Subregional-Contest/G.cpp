#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>

using namespace std;

const int N = 200005;

pair<pair<int, int>, int> a[N];

pair<double, int> Max[5];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first.first, &a[i].first.second);
        a[i].second = i;
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= 4; i++) {
        Max[i] = make_pair(-1e10, 0);
    }
    pair<double, pair<int, int> > ans = make_pair(-1e10, make_pair(0, 0));
    double base = sqrt(2.) - 1;
    for (int i = 1; i <= n; i++) {
        double t = base * a[i].first.first - a[i].first.second;
        if (i != 1) {
            ans = max(ans, make_pair(t + Max[1].first, make_pair(Max[1].second, a[i].second)));
        }

        t = base * a[i].first.first + a[i].first.second;
        if (i != 1) {
            ans = max(ans, make_pair(t + Max[2].first, make_pair(Max[2].second, a[i].second)));
        }

        t = a[i].first.first - base * a[i].first.second;
        if (i != 1) {
            ans = max(ans, make_pair(t + Max[3].first, make_pair(Max[3].second, a[i].second)));
        }

        t = a[i].first.first + base * a[i].first.second;
        if (i != 1) {
            ans = max(ans, make_pair(t + Max[4].first, make_pair(Max[4].second, a[i].second)));
        }

        t = -base * a[i].first.first + a[i].first.second;
        Max[1] = max(Max[1], make_pair(t, a[i].second));

        t = -base * a[i].first.first - a[i].first.second;
        Max[2] = max(Max[2], make_pair(t, a[i].second));

        t = 1. * -a[i].first.first + base * a[i].first.second;
        Max[3] = max(Max[3], make_pair(t, a[i].second));

        t = 1. * -a[i].first.first - base * a[i].first.second;
        Max[4] = max(Max[4], make_pair(t, a[i].second));
    }
    printf("%d %d\n", ans.second.first, ans.second.second);
    return 0;
}
