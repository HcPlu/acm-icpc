#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2e5 + 10;

struct EdgeList {
	int size;
	int last[N], succ[N], other[N];
	
	void clear(int n) {
		size = 0;
		std::fill(last + 1, last + n + 1, 0);
	}
	
	void add(int x, int y) {
		size++;
		succ[size] = last[x];
		last[x] = size;
		other[size] = y;
	}
} e;

int n, d, answer, limit, stamp;
int a[N], f[N], g[N], ban[N], father[N], size[N], treef[N], treeg[N], stampf[N], stampg[N];

__inline int lowbit(int x) {
	return x & -x;
}

int find(int root) {
	std::vector<int> queue;
	father[root] = 0;
	queue.push_back(root);
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == father[x] || ban[y]) {
				continue;
			}
			father[y] = x;
			queue.push_back(y);
		}
	}
	int answer = 0, best = n;
	for (int index = (int)queue.size() - 1; index >= 0; --index) {
		int x = queue[index];
		size[x] = 1;

		int value = 0;
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == father[x] || ban[y]) {
				continue;
			}
			size[x] += size[y];
			value = std::max(value, size[y]);
		}
		value = std::max(value, (int)queue.size() - size[x]);
		if (best > value) {
			best = value;
			answer = x;
		}
	}
	
	return answer;
}

__inline int queryg(int x) {
	x = std::max(x, 1);

	int answer = 0;
	for (int i = x; i <= limit; i += lowbit(i)) {
		if (stampg[i] != stamp) {
			stampg[i] = stamp;
			treeg[i] = 0;
		}
		answer = std::max(answer, treeg[i]);
	}
	return answer;
}

__inline void insertg(int x, int val) {
	for (int i = x; i >= 1; i -= lowbit(i)) {
		if (stampg[i] != stamp) {
			stampg[i] = stamp;
			treeg[i] = 0;
		}
		treeg[i] = std::max(treeg[i], val);
	}
}

__inline int queryf(int x) {
	x = std::min(x, limit);
	
	int answer = 0;
	for (int i = x; i >= 1; i -= lowbit(i)) {
		if (stampf[i] != stamp) {
			stampf[i] = stamp;
			treef[i] = 0;
		}
		answer = std::max(answer, treef[i]);
	}
	return answer;
}

__inline void insertf(int x, int val) {
	for (int i = x; i <= limit; i += lowbit(i)) {
		if (stampf[i] != stamp) {
			stampf[i] = stamp;
			treef[i] = 0;
		}
		treef[i] = std::max(treef[i], val);
	}
}

void bfs(int root, int super) {
	std::vector<int> queue;

	if (a[root] >= a[super]) {
		f[root] = 1;
	} else {
		f[root] = -1;
	}
	if (a[super] >= a[root]) {
		g[root] = 1;
	} else {
		g[root] = -1;
	}

	father[root] = 0;
	queue.push_back(root);
	
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		
		if (std::abs(a[x] - a[super]) <= d) {
			if (f[x] != -1) {
				answer = std::max(answer, f[x] + queryg(a[x] - d) + 1);
				answer = std::max(answer, f[x] + 1);
			}
			if (g[x] != -1) {
				answer = std::max(answer, g[x] + 1);
				answer = std::max(answer, g[x] + queryf(a[x] + d) + 1);
			}
		}
		
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == father[x] || ban[y]) {
				continue;
			}
			
			if (f[x] != -1 && a[y] >= a[x]) {
				f[y] = f[x] + 1;
			} else {
				f[y] = -1;
			}
			if (g[x] != -1 && a[x] >= a[y]) {
				g[y] = g[x] + 1;
			} else {
				g[y] = -1;
			}

			father[y] = x; 
			queue.push_back(y);
		}
	}
	
	for (int index = 0; index < (int)queue.size(); ++index) {
		int x = queue[index];
		
		if (f[x] != -1) {
			insertf(a[x], f[x]);
		}
		if (g[x] != -1) {
			insertg(a[x], g[x]);
		}
	}
}

void dfs(int x) {
	ban[x = find(x)] = true;
	
	stamp++;
	
	for (int i = e.last[x]; i; i = e.succ[i]) {
		int y = e.other[i];
		if (ban[y]) {
			continue;
		}
		bfs(y, x);
	}

	for (int i = e.last[x]; i; i = e.succ[i]) {
		int y = e.other[i];
		if (ban[y]) {
			continue;
		}
		dfs(y);
	}
}

void solve(void) {
	scanf("%d%d", &n, &d);

	e.clear(n);
	for (int i = 1; i <= n; ++i) {
		ban[i] = false;
	}
	
	limit = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		limit = std::max(limit, a[i]);
	}
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		e.add(x, y);
		e.add(y, x);
	}
	
	answer = 1;
	dfs(1);
	printf("%d\n", answer);
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}
