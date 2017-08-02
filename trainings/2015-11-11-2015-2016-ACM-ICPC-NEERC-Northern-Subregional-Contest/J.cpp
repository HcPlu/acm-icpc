#include <iostream>
#include <vector>

#define left LLFEG
#define right RITHTGH

using namespace std;

const int INF = 1 << 29;

const int N = 55555;

int n, limit, price[N], d[N], ok[N];
long long dp[N];

int main() {
    scanf("%d%d", &n, &limit);
    for (int i = 1; i < n; i++) {
        scanf("%d", &price[i]);
    }
    for (int i = 2; i < n; i++) {
        scanf("%d", &d[i]);
    }

    d[1] = 0;
    d[n] = 0;

    for (int i = 1; i <= n - 1; i++) {
        ok[i] = 1;
    }

    int minx = INF;
    for (int i = n - 1; i >= 1; i--) {
        if (price[i] >= minx) {
            ok[i] = 0;
        } else {
            minx = min(price[i], minx);
        }
    }

    vector<int> card;

    for (int i = 1; i <= n - 1; i++) {
        if (ok[i])
            card.push_back(i);
    }

    int left = 0, right = (int)card.size() - 1;
    int answer;

    while (left <= right) {
        int mid = (left + right) >> 1;
        vector<int> stack;
        dp[1] = 0;
        int head = 0;
        stack.push_back(1);
        for (int i = 2; i <= n; i++) {
            for (; head < (int)stack.size() && stack[head] < i - card[mid]; head++);
            dp[i] = dp[stack[head]] + i - stack[head] + d[i];
            for (; (int)stack.size() > head && dp[i] <= dp[stack.back()] + i - stack.back(); stack.pop_back());
            stack.push_back(i);
        }
        if (dp[n] > limit) {
            left = mid + 1;
        } else {
            right = mid - 1;
            answer = price[card[mid]];
        }
    }

    printf("%d\n", answer);

}
