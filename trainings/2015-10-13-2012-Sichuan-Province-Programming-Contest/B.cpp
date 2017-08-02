#include <cstdio>

using namespace std;

const int N = 50005;

int k[N], a[N];

typedef long long LL;

long long get_num(int x) {
    return (1LL * x * x + x) / 2;
}

int num[2];

void work() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    double andd = 0, orr = 0, xorr = 0;
    for (int pos = 0; pos <= 30; pos++) {
        for (int i = 1; i <= n; i++) {
            k[i] = a[i] >> pos & 1;
        }
        num[0] = num[1] = 0;
        long long ans_and = 0, ans_or = 0, ans_xor = 0;
        for (int i = 1, j; i <= n; i = j) {
            if (k[i] == 0) {
                for (j = i; j <= n && k[j] == 0; j++) {
                }
                ans_or += get_num(j - i);
            } else {
                for (j = i; j <= n && k[j] == 1; j++) {
                }
                ans_and += get_num(j - i);
            }
        }
        num[0]++;
        int now = 0;
        for (int i = 1; i <= n; i++) {
            now ^= k[i];
            ans_xor += 1LL * num[now ^ 1];
            num[now]++;
        }
        //	printf("%lld %lld %lld\n", ans_and, ans_or, ans_xor);
        long long t = get_num(n);
        andd += (1. * ans_and / t) * (1 << pos);
        orr += (1. - (1. * ans_or / t)) * (1 << pos);
        xorr += (1. * ans_xor / t) * (1 << pos);
    }
    printf("%.6f %.6f %.6f\n", andd, orr, xorr);
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i), work();
    }
    return 0;
}
