#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>

using namespace std;

const int N = 200005;

int a[N], n;
int palindrome[N];
int c[N * 2 + 20];

void manacher(int *text, int n) {
    palindrome[0] = 1;
    for (int i = 1, j = 0; i < n; ++i) {
        if (j + palindrome[j] <= i) {
            palindrome[i] = 0;
        } else {
            palindrome[i] = min(palindrome[(j << 1) - i], j + palindrome[j] - i);
        }
        while (i - palindrome[i] >= 0 && i + palindrome[i] < n && text[i - palindrome[i]] == text[i + palindrome[i]]) {
            palindrome[i]++;
        }
        if (i + palindrome[i] > j + palindrome[j]) {
            j = i;
        }
    }
}

pair<int, int> pos[N];
set<pair<int, int> > Q;

void work() {
    Q.clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        c[2 * i - 2] = -1;
        c[2 * i - 1] = a[i];
    }
    c[2 * n] = -1;

    manacher(c, 2 * n + 1);
    for (int i = 1; i <= 2 * n + 1; i++) {
        pos[i] = make_pair(palindrome[i - 1], i);
    }

    sort(pos + 1, pos + 1 + 2 * n + 1);
    reverse(pos + 1, pos + 1 + 2 * n + 1);
    int ans = 0;
    for (int i = 1; i <= 2 * n + 1; i++) {
        if (pos[i].second % 2 == 0) {
            continue;
        }
        if (i != 1) {
            set<pair<int, int> >::iterator it1 = Q.lower_bound(make_pair(pos[i].second - pos[i].first + 1, 0));
            if (it1 != Q.end()) {
                ans = max((pos[i].second - (*it1).first) / 2, ans);
            }
            set<pair<int, int> >::iterator it2 = Q.lower_bound(make_pair(pos[i].second + pos[i].first, 0));
            if (it2 != Q.begin()) {
                it2--;
            }
            if ((*it2).first - pos[i].second + 1 <= pos[i].first) {
                ans = max(((*it2).first - pos[i].second) / 2, ans);
            }
        }
        swap(pos[i].first, pos[i].second);
        Q.insert(pos[i]);
    }
    printf("%d\n", ans * 3);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i), work();
    }
    return 0;
}
