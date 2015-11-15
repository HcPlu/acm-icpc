#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int N = 666;
int best[N][N], visit[N][N], stamp, number[N];
int n;
vector<pair<int, int> > plane;
map<pair<int, int>, int> counter;
int dfs(int l, int r) {	
	if (l > r) {
		return 0;
	}

	if (visit[l][r] == stamp) {
		return best[l][r];
	}
	visit[l][r] = stamp;
	
	best[l][r] = 0;
	int &result = best[l][r];
	
	int rest = 0;
	for (int i = 0; i < (int)plane.size(); i++) {
		if (plane[i] == make_pair(l, r)) {
			rest += number[i];
			continue;
		}
		if (plane[i].second <= r && plane[i].first >= l) {
			result = max(dfs(l, plane[i].first) + dfs(plane[i].second, r) + dfs(plane[i].first, plane[i].second), result);
		}
	}
	result += rest;
	return result;
}

void solve() {
	scanf("%d", &n);
	
	counter.clear();
	plane.clear();
	vector<int> vec;
	
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		plane.push_back(make_pair(x, y));
		counter[plane.back()]++;
		vec.push_back(plane.back().first);
		vec.push_back(plane.back().second);
	}
	sort(plane.begin(), plane.end());
	plane.erase(unique(plane.begin(), plane.end()), plane.end());
	int size = plane.size();
	for (int i = 0; i < (int)plane.size(); i++) {
		number[i] = counter[plane[i]];
	}
	
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	
	for (int i = 0; i < (int)plane.size(); i++) {
		plane[i].first = lower_bound(vec.begin(), vec.end(), plane[i].first) - vec.begin() + 1;
		plane[i].second = lower_bound(vec.begin(), vec.end(), plane[i].second) - vec.begin() + 1;
	}
	stamp++;
	printf("%d\n", dfs(0, (int)vec.size() + 1));
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
