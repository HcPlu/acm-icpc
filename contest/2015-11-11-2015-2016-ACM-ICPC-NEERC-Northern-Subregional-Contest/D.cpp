#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

long long n;
void solve() {
    cin >> n;
    int base = 0;
    vector<long long> answer;
    for (; n > 0; n >>= 1, base++) {
        if ((n & 1) == 0) {
            continue;
        }
        long long now = 1;
        int j;
        for (j = 0; now <= n; ) {
            now = now * 3;
            j++;
        }
        now /= 3;
        j--;
        n -= now;
        answer.push_back((1LL << base) * now);
    }
    sort(answer.begin(), answer.end());
    printf("%d\n", (int)answer.size());
    for (int i = 0; i < (int)answer.size(); i++) {
        cout << answer[i] << (i == (int)answer.size() - 1 ? "\n" : " ");
    }
}
int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
}
