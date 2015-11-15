#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 105;

int f[N][N][N];
int ans[N];
int a[N][N];

int dx[2] = {0, -1};
int dy[2] = {-1, 0};

void work() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &a[i][j]);
	int limit = min(n, m);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			for(int k = 0; k <= limit; k++)
				f[i][j][k] = -0x3f3f3f3f;
	for(int i = 0; i <= n; i++)
		f[i][0][0] = 0;
	for(int i = 0; i <= m; i++)
		f[0][i][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k <= limit; k++) {
				f[i][j][k] = max(f[i][j][k], f[i][j - 1][k]);
				f[i][j][k] = max(f[i][j][k], f[i - 1][j][k]);
				if(k) {	
					f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1] + a[i][j]);
				}
			}
	for(int i = 0; i <= limit; i++) {
		ans[i] = f[n][m][i];
	}
	
	
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= m; j++)
			for(int k = 0; k <= limit; k++)
				f[i][j][k] = 0x3f3f3f3f;
	for(int i = 0; i <= n; i++)
		f[i][0][0] = 0;
	for(int i = 0; i <= m; i++)
		f[0][i][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			for(int k = 0; k <= limit; k++) {
				f[i][j][k] = min(f[i][j][k], f[i][j - 1][k]);
				f[i][j][k] = min(f[i][j][k], f[i - 1][j][k]);
				if(k) {	
					f[i][j][k] = min(f[i][j][k], f[i - 1][j - 1][k - 1] + a[i][j]);
				}
			}
	long long result = 0;
	for(int i = 1; i * 2 <= limit; i++) {
		result = max(result, 1LL * ans[i] - f[n][m][i * 2] );
	}
	cout << result << endl;
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {	
		work();
	}
	return 0;
}
