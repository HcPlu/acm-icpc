#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int N = 1111111;

char a[N], b[N];
int counta[N], countb[N];

int main(void) {
    scanf("%s%s", a, b);

    int lena = (int)strlen(a);
    int lenb = (int)strlen(b);

    for (int i = 1; i < lena; ++i) {
        counta[a[i] - 'a']++;
    }

    for (int i = 0; i < lenb - 1; ++i) {
        countb[b[i] - 'a']++;
    }

    long long answer = 1LL * lena * lenb;
    for (int i = 0; i < 26; ++i) {
        answer -= 1LL * counta[i] * countb[i];
    }

    std::cout << answer << std::endl;
}
