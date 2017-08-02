#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int N = 20005;

vector<int> ans;

struct Node {
    int h, m, s, id;

    friend bool operator <(const Node &a, const Node &b) {
        if (a.h == b.h) {
            if (a.m == b.m) {
                return a.s < b.s;
            } else {
                return a.m < b.m;
            }
        } else {
            return a.h < b.h;
        }
    }

    friend int operator -(const Node &a, const Node &b) {
        return (a.h - b.h) * 3600 + (a.m - b.m) * 60 + a.s - b.s;
    }
} point[N];

void work() {
    ans.clear();
    int n, l;
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; i++) {
        scanf("%d:%d:%d", &point[i].h, &point[i].m, &point[i].s), point[i].id = i;
    }
    sort(point + 1, point + 1 + n);
    int st;
    for (int i = 1; i <= n; i = st) {
        st = i;
        while (st <= n && point[st] - point[i] < l) {
            st++;
        }
        ans.push_back(point[i].id);
    }
    printf("%d\n", (int)ans.size());
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d%s", ans[i], i + 1 == ans.size() ? "\n" : " ");
    }
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
