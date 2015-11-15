#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

const int N = 105;
const int mod = 1000000007;
char c[4][N];
int n,f[N][4];
pair<int, int> limit[3];

pair<int, int> get(char x, int i) {
	pair<int, int> ans;
	if(x >= '0' && x <= '9') {
		ans = make_pair(x - '0', x - '0');
	} else {
		ans = make_pair(0, 9);
	}
	if(i == n) {
		ans.first = max(ans.first, 1);
	}
	return ans;
}

void update(int &x, int y) {
	x += y;
	if(x >= mod) {
		x -= mod;
	}
	return ;
}

void work() {
	scanf("%s", c[2] + 1);
	scanf("%s", c[3] + 1);
	n = strlen(c[1] + 1);
	for(int i = 1; i <= 3; i++)
		reverse(c[i] + 1, c[i] + 1 + n);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= 1; j++)
			f[i][j] = 0;
	f[0][0] = 1;
	for(int i = 0; i < n; i++)
		for(int j = 0; j <= 1; j++) {
			for(int k = 1; k <= 3; k++)
				limit[k] = get(c[k][i + 1], i + 1);
			for(int ia = limit[1].first; ia <= limit[1].second; ia++) {
				for(int ib = limit[2].first; ib <= limit[2].second; ib++) {
					for(int ic = limit[3].first; ic <= limit[3].second; ic++) {
						if((ia + ib + j) % 10 == ic) {
							int jw = (ia + ib + j) / 10;
							update(f[i + 1][jw], f[i][j]);
						}
					}
				}
			}
		}	
	printf("%d\n", f[n][0]);
}

int main() {
	while(scanf("%s", c[1] + 1) == 1) {
		if(strlen(c[1] + 1) == 1 && c[1][1] =='0') break;
		work();
	}
	return 0;
}
