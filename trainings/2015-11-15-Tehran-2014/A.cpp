#include <cstdio>

int a, b, c, d;

int main(void) {
    for (; scanf("%d%d%d%d", &a, &b, &c, &d) && (a || b || c || d); printf("%d %d\n", c - b, d - a));
}
