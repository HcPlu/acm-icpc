#include <iostream>

using namespace std;
char text[111111];

void solve() {
    scanf("%s", text);
    int len = strlen(text);
    if (len < 4) {
        printf("%snanodesu\n", text);
        return;
    }
    if (text[len - 4] == 'd' && text[len - 3] == 'e' && text[len - 2] == 's' && text[len - 1] == 'u') {
        for (int i = 0; i < len - 4; i++) {
            putchar(text[i]);
        }
        printf("nanodesu\n");
        return;
    }

    printf("%snanodesu\n", text);
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
