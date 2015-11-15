#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<set>

using namespace std;

int n, m, k;

char type[111];

set<int> k1[1005];
set<int> k2[1005];

void work() {
	int t;
	for(int i = 1; i <= m; i++) {
		k1[i].clear(), k2[i].clear();
	}
	scanf("%d", &t);
	for(int i = 1; i <= t; i++) {
		scanf("%s", type + 1);
		int id;
		scanf("%d", &id);
		if(type[1] == 'p') {
			scanf("%s", type + 1);
			int p;
			scanf("%d", &p);
			k1[id].insert(p);
		} else {
			scanf("%s", type + 1);
			int p;
			scanf("%d", &p);
			k2[p].insert(id);	
		}
	}
	int ans = n * m * k;
	for(int i = 1; i <= m; i++) {
		ans -= k1[i].size() * n;
		ans -= k2[i].size() * k; 
		ans += k1[i].size() * k2[i].size();
	}
	printf("%d\n", ans);
	return ;
}

int main() {
	while(scanf("%d%d%d", &n, &m, &k) == 3 && (n + m + k != 0))
		work();
}
