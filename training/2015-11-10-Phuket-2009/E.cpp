#include <cstdio>
#include <cstring>

int a, b;
char op[111];

void solve(void) {
    bool answer;
    if (!strcmp(op, "<")) {
        answer = a < b;
    } else if (!strcmp(op, "<=")) {
        answer = a <= b;
    } else if (!strcmp(op, ">")) {
        answer = a > b;
    } else if (!strcmp(op, ">=")) {
        answer = a >= b;
    } else if (!strcmp(op, "==")) {
        answer = a == b;
    } else if (!strcmp(op, "!=")) {
        answer = a != b;
    }
    if (answer) {
        puts("true");
    } else {
        puts("false");
    }
}

int main(void) {
    for (int tests = 1; ~scanf("%d%s%d", &a, op, &b); ++tests) {
        if (!strcmp(op, "E")) {
            break;
        }
        printf("Case %d: ", tests);
        solve();
    }
}
