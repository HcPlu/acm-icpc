#include <iostream>

using namespace std;
const int N = 3 * 111111;
pair<int, int> q[N];
int pos[N];
int buy[N], sell[N], n, limit;

void solve() {
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &pos[i]);
    }
    for (int i = 0; i <= n; i++) {
        scanf("%d%d", &buy[i], &sell[i]);
    }

    int l = 1, r = 1;
    long long cost = 0;
    q[1].first = buy[0];
    q[1].second = limit;
    cost += 1LL * limit * buy[0];
    for (int i = 1; i <= n; i++) {
        int dist = pos[i] - pos[i - 1];
        for (; dist - q[l].second > 0 && l <= r; dist -= q[l].second, l++);
        q[l].second -= dist;
        if (q[l].second == 0)
            l++;
        int num = 0;
        for (; q[l].first < sell[i] && l <= r; l++) {
            num += q[l].second;
        }
        l--;
        q[l].first = sell[i];
        q[l].second = num;

        int need = 0;
        for (; q[r].first > buy[i] && l <= r; r--) {
            need += q[r].second;
            cost -= 1LL * q[r].first * q[r].second;
        }
        r++;
        q[r].first = buy[i];
        q[r].second = need + pos[i] - pos[i - 1];
        cost += 1LL * q[r].second * q[r].first;
    }
    for (int i = l; i <= r; i++) {
        cost -= 1LL * q[i].second * q[i].first;
    }

    printf("%I64d\n", cost);
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
    return 0;
}
