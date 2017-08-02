#include <iostream>


using namespace std;
const int N = 111111;
const int mod = 365 * 24 * 60 * 60;
int n;
pair<int, int> que[N];

bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return 1LL * p1.first * p2.second < 1LL * p2.first * p1.second;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        que[i] = make_pair(x, y);
    }

    sort(que + 1, que + n + 1, cmp);

    long long answer = 0;
    long long now = 0;
    for (int i = 1; i <= n; i++) {
        answer += now * que[i].second + que[i].first;
        answer %= mod;
        now += que[i].second * now + que[i].first;
        now %= mod;
    }

    printf("%d\n", (int)answer);
}

int main() {
    for (; scanf("%d", &n) == 1 && n; solve());
}
