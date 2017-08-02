#include <iostream>

using namespace std;
typedef unsigned long long LL;

const long long M = 1e9 + 7;
const int N = 11111;

int T, n;
int length[N];
char s[N];
long long sum[N], hash[N], rev_hash[N];
long long pow[N];

int main() {
    scanf("%d", &T);
    pow[0] = 1;
    for (int i = 1; i <= 2000; i++)
        pow[i] = pow[i - 1] * M;
    for (int testCount = 1; testCount <= T; testCount++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", s + 1);
            int len = strlen(s + 1);
            for (int j = 1; j <= len; j++)
                sum[j] = sum[j - 1] * M + s[j];
            hash[i] = sum[len];
            length[i] = len;
            sum[0] = 0;
            for (int j = len; j >= 1; j--)
                sum[len - j + 1] = sum[len - j] * M + s[j];
            rev_hash[i] = sum[len];
        }
        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                long long myhash, myrev_hash;
                if (i != j) {
                    myhash = hash[i] * pow[length[j]] + hash[j];
                    myrev_hash = rev_hash[j] * pow[length[i]] + rev_hash[i];
                    if (myhash == myrev_hash)
                        ans++;
                }
            }
        printf("Case #%d: %d\n", testCount, ans);
    }
    return 0;
}
