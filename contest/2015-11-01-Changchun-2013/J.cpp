#pragma comment(linker, "/STACK:1024000000,1024000000") 

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>


using namespace std;

const int N = 100005;

int start[N], tot;

struct Node {
	int x, y, next;
}road[N << 1];

int n, deep[N], father[N][23];
int ans[22], id[22], L[N], R[N], gxx, ind[N];

vector<pair<int, pair<int, int> > > limit[5];

void build(int x, int y) {
	tot++;
	road[tot].x = x;
	road[tot].y = y;
	road[tot].next = start[x];
	start[x] = tot;
}

void dfs(int x, int fa) {
	father[x][0] = fa;
	L[x] = ++gxx;
	deep[x] = deep[fa] + 1;
	for(int i = start[x]; i; i = road[i].next) {
		int to = road[i].y;
		if(to == fa) continue;
		dfs(to, x);
	}
	R[x] = gxx;
	return ;
}

int lca(int x, int y) {
	if(deep[x] < deep[y]) {
		swap(x, y);
	}
	for(int i = 20; i >= 0; i--) {
		if(deep[father[x][i]] >= deep[y]) {
			x = father[x][i];
		}
	}
	if(x == y) {
		return x;
	}
	for(int i = 20; i >= 0; i--) {
		if(father[x][i] != father[y][i]) {
			x = father[x][i];
			y = father[y][i];
		}
	}
	return father[x][0];
}

int up(int x, int dis) {
	int target = deep[x] - dis;
	for(int i = 20; i >= 0; i--) {
		if(deep[father[x][i]] >= target) {
			x = father[x][i];
		}
	}	
	return x;
}

int dis(int x, int y) {
	int t = lca(x, y);
	return deep[x] + deep[y] - 2 * deep[t] + 1;
}

bool inseg(pair<int, int> x, int y) {
	if(y >= x.first && y <= x.second)
		return true;
	return false;
}

void addlimit(int idx, int idy, int x, int y) {
	int t = lca(x, y);
	if(deep[x] - deep[t] == deep[y] - deep[t]) {
		int now_dis = deep[x] - deep[t] + 1;
		int to;
		to = up(x, now_dis - 2);
		limit[idx].push_back(make_pair(0, make_pair(L[to], R[to])));
		
		to = up(y, now_dis - 2);
		limit[idy].push_back(make_pair(0, make_pair(L[to], R[to])));
		
	} else {
		if(deep[x] - deep[t] < deep[y] - deep[t]) {
			swap(x, y);
			swap(idx, idy);
		}
		int now_dis = dis(x, y);
		if(now_dis & 1) {
			now_dis >>= 1;
			int to = up(x, now_dis - 1);
			limit[idx].push_back(make_pair(0, make_pair(L[to], R[to])));
			to = father[to][0];
			limit[idy].push_back(make_pair(1, make_pair(L[to], R[to])));
		} else {
			now_dis >>= 1;
			int to = up(x, now_dis - 1);
			limit[idx].push_back(make_pair(0, make_pair(L[to], R[to])));
			limit[idy].push_back(make_pair(1, make_pair(L[to], R[to])));
		}
	}
	return ;
}

int get_ans(int id) {
	vector<pair<int, int> > lim;
	vector<pair<int, int> > g[4];
	for(int i = 0; i <= 1; i++)
		g[i].clear();
	lim.clear();
	for(int i = 0; i < limit[id].size(); i++) {
		if(limit[id][i].first == 0) {
			g[i].push_back(limit[id][i].second);
		} else {
			if(limit[id][i].second.first > 1) 
				g[i].push_back(make_pair(1, limit[id][i].second.first - 1));
			if(limit[id][i].second.second < n) 
				g[i].push_back(make_pair(limit[id][i].second.second + 1, n));
		}
	}
	for(int i = 0; i < g[0].size(); i++)
		for(int j = 0; j < g[1].size(); j++) {
			int l = max(g[0][i].first, g[1][j].first);
			int r = min(g[0][i].second, g[1][j].second);
			if(l > r) continue;
			lim.push_back(make_pair(l, r));
		}
	sort(lim.begin(), lim.end());
	int ans = 0;
	for(int i = 0, j; i < lim.size(); i = j) {
		j = i;
		int Maxr = lim[i].second;
		for(; j < lim.size() && inseg(make_pair(lim[i].first, Maxr), lim[j].first); j++) {
			Maxr = max(Maxr, lim[j].second);
		}
		ans += (Maxr - lim[i].first + 1);
	}
	return ans;
}

void work() {
	tot = gxx = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		start[i] = 0;
	for(int i = 1; i <= n - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		build(x, y);
		build(y, x);
	}
	deep[1] = 1;
	dfs(1, 0);
	for(int i = 1; i <= 20; i++) 
		for(int j = 1; j <= n; j++)
			father[j][i] = father[father[j][i - 1]][i - 1];
	int Q;
	scanf("%d", &Q);
	for(int tt = 1; tt <= Q; tt++) {
		for(int j = 1; j <= 3; j++)
			scanf("%d", &ind[j]);
		for(int i = 1; i <= 3; i++) {
			limit[i].clear();
			ans[i] = 0;
		}
		for(int i = 1; i <= 3; i++)
			for(int j = i + 1; j <= 3; j++) {
				addlimit(i, j, ind[i], ind[j]);
			}
		ans[1] = get_ans(1);
		ans[2] = get_ans(2);
		ans[3] = get_ans(3);
		printf("%d %d %d\n", ans[1], ans[2], ans[3]);
	}
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
