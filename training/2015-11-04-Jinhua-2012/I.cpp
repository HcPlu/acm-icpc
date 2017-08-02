#include <cstdio>

int n;

void solve(void) {
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        answer += x * x;
    }
    printf("%d\n", answer);
}

int main(void) {
    for (; scanf("%d", &n) && n; solve());
}
