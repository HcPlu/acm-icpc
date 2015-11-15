#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int INF = 1 << 30;
const int N = 111;
int cost[N], price[N][18];
int n, m;
int f[N][1 << 17][2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cost[i]);
		for (int j = 1; j <= m; j++) {
			scanf("%d", &price[i][j]);
		}
	}
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < (1 << m); j++) {
			for (int k = 0; k < 2; k++)
			f[i][j][k] = INF;
		}
	}
	
	f[0][0][0] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int state = 0; state < (1 << m); state++) {
				for (int k = 0; k < 2; k++) {
					if (k == 0) {
						f[i][state][k] = min(f[i - 1][state][0], f[i - 1][state][1]);
					} else {
						if (j == 1) {
							if (state >> (j - 1) & 1) {
								int tmp = min(f[i 	- 1][state ^ (1 << j - 1)][0], f[i - 1][state ^ (1 << j - 1)][1]);
								f[i][state][k] = min(f[i][state][k], tmp + cost[i] + price[i][j]);
							}
							f[i][state][k] = min(f[i][state][k], f[i - 1][state][0] + cost[i]);
							f[i][state][k] = min(f[i][state][k], f[i - 1][state][1] + cost[i]);
						} else {
							if (state >> (j - 1) & 1) {
								f[i][state][k] = min(f[i][state ^ (1 << j - 1)][k]  + price[i][j], f[i][state][k]);
							}
						}
					}
				}
			}
		}
	}
	
	printf("%d\n", min(f[n][(1 << m) - 1][0], f[n][(1 << m) - 1][1]));
	return 0;
}
