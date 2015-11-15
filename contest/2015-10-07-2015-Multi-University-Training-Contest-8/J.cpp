#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int mod = 258280327;
const int N = 100005;

int a[N];
int f[N][10][10];

int fix(int x) {
	if(x == 0)  x = 9;
	return x;
}

void work() {
	int n;
	scanf("%d", &n);
	int base = 0, A, B, sum = 0;
	scanf("%d%d", &A, &B);
	if(A > B) swap(A, B);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), sum = (sum + a[i]) % 9;
	
	if(A == 0 && B == 0) {
		if(n == 0) puts("1");
		else
			puts("0");
		return ;
	}
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++)
				f[i][j][k] = 0;
	f[0][0][0] = 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++) {
				if(!f[i][j][k]) continue;
				f[i + 1][fix((j + a[i + 1]) % 9)][k] = (f[i + 1][fix((j + a[i + 1]) % 9)][k] + f[i][j][k]) % mod;
				f[i + 1][j][fix((k + a[i + 1]) % 9)] = (f[i + 1][j][fix((k + a[i + 1]) % 9)] + f[i][j][k]) % mod;
			}
	if(A != 0) f[n][A][B] = (f[n][A][B] + f[n][0][B]) % mod;
	if(B != 0) f[n][A][B] = (f[n][A][B] + f[n][A][0]) % mod;
	printf("%d\n", f[n][A][B]);
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
