#include <cstdio>

int main(void) {
    for (int a, b; ~scanf("%d%d", &a, &b);) {
        printf("%d\n", (b - a + 1) * (b - a) / 2);
    }
}
