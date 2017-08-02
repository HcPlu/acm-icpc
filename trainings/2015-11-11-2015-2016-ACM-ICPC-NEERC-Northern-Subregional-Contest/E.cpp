#include <cstdio>
#include <cstring>

using namespace std;

const int LEN = 1005;

char c[LEN];

int main() {
    scanf("%s", c + 1);
    int len = strlen(c + 1);
    int nowsign = 0;
    int numdigit = 0;
    for (int i = 1; i <= len; i++) {
        if (c[i] == '+' || c[i] == '-') {
            if (c[i] == '+') {
                nowsign = 0;
                numdigit = 0;
            }
            if (c[i] == '-') {
                nowsign = 1;
                numdigit = 0;
            }
            printf("%c", c[i]);
            continue;
        }
        if (nowsign == 1) {
            printf("%c", c[i]);
            int j = i + 1;
            while (j <= len && c[j] == '0') {
                printf("+0");
                j++;
            }
            i = j - 1;
            nowsign = 0;
            if (j != len + 1 && (c[j] >= '0' && c[j] <= '9')) {
                printf("+");
            }
            nowsign = 0;
        } else {
            printf("%c", c[i]);
        }
    }
    puts("");
    return 0;
}
