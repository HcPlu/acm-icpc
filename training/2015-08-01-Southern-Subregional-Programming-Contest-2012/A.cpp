#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 200005;

long long f[N], a[N], tmp[N];
long long jp0[N], jp1[N], get[N];

int main() {
    long long n;
    scanf("%I64d", &n);
    for (long long i = 1; i <= n; i++)
        scanf("%I64d", &a[i]);
    sort(a + 1, a + 1 + n);
    for (long long i = 1; i <= n; i++)
        tmp[i] = a[i];
    f[0] = 1;
    for (long long i = 0; i <= 100; i++) {
        for (long long j = 1; j <= n; j++)
            if (a[j] != 0)
                goto syf;
        break;
        syf:;
        for (long long j = 0; j <= n + 1; j++)
            get[j] = 0;
        long long sum0 = 0, sum1 = 0;
        for (long long j = 1; j <= n; j++)
            if (a[j] & 1)
                jp1[++sum1] = a[j];
            else
                jp0[++sum0] = a[j];
        long long tw1 = 0, tw0 = 0;
        for (long long j = 1; j <= n + 1; j++) {
            long long res = (sum1 - tw1) + tw0;
            if (res % 2 == 0)
                get[tw0] += f[j - 1];
            if ((n - res) % 2 == 0)
                get[sum0 + tw1] += f[j - 1];
            if (a[j] & 1)
                tw1++;
            else
                tw0++;
            if (a[j] == 0)
                break;
        }
        long long cnt = 0;
        for (long long j = 1; j <= sum0; j++)
            a[++cnt] = jp0[j];
        for (long long j = 1; j <= sum1; j++)
            a[++cnt] = jp1[j];
        for (long long j = 1; j <= cnt; j++)
            a[j] >>= 1;
        for (long long j = 0; j <= n + 1; j++)
            f[j] = get[j];
    }

    long long flag = 0;
    for (long long i = 2; i <= n; i++)
        flag ^= (tmp[i] - tmp[1]);
    if (flag == 0)
        f[0]--;

    printf("%I64d\n", f[0]);
    return 0;
}
