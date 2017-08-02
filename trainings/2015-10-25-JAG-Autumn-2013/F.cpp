#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 2000005;
const int mod = 1000000007;

char c[N];
char s[N];

int sign[N], number[N], cnt = 0;

int sqr(int x) {
    return 1LL * x * x % mod;
}

int calc(int x, int y) {
    if (y >= 40) {
        return 0;
    }
    long long res = 1LL << y;
    return 1LL * x / res;
}

void work() {
    int t = strlen(c + 1);
    cnt = 0;
    for (int i = 1; i <= t; i++) {
        if ((c[i] >= '0' && c[i] <= '9') || c[i] == '<' || c[i] == '>' || c[i] == 'S') {
            s[++cnt] = c[i];
        }
    }
    s[cnt + 1] = s[cnt + 2] = s[cnt + 3] = 0;

    int top1 = 0, top2 = 0;

    for (int i = 1, j; i <= cnt; i = j) {
        j = i;
        if (s[i] == 'S') {
            sign[++top1] = 1;
            j = i + 2;
        } else {
            if (s[i] == '>') {
                if (s[i + 2] == '>' || s[i + 2] == 0) {
                    number[top2] = sqr(number[top2]);
                    j = i + 1;
                    top1--;
                    if (sign[top1] == 2 && top2 >= 2) {
                        int a = number[top2], b = number[top2 - 1];
                        int t = calc(b, a);
                        top2 -= 2;
                        top1--;
                        number[++top2] = t;
                    }
                } else {
                    sign[++top1] = 2;
                    j = i + 2;
                }
            } else {
                int num = 0;
                for (; j <= cnt && (s[j] >= '0' && s[j] <= '9'); j++) {
                    num = num * 10 + s[j] - '0';
                }
                number[++top2] = num;
                if (sign[top1] == 2 && top2 >= 2) {
                    int a = number[top2], b = number[top2 - 1];
                    int t = calc(b, a);
                    top2 -= 2;
                    top1--;
                    number[++top2] = t;
                }
            }
        }
    }
    printf("%d\n", number[top2]);
    return;
}

int main() {
    while (gets(c + 1)) {
        if (c[1] == '#') {
            break;
        }
        work();
    }
    return 0;
}
