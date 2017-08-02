#include <cstdio>
#include <algorithm>

int n, m;
int answer[2];

void solve(void) {
    scanf("%d%d", &n, &m);

    answer[0] = answer[1] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            scanf("%d", &x);

            if (x == -1) {
                continue;
            }
            answer[i + j & 1] += x;
        }
    }
    printf("%d\n", std::abs(answer[0] - answer[1]));
}

int main(void) {
    int tests;
    for (scanf("%d", &tests); tests--; solve());
}
