#include <cstdio>
#include <algorithm>
#include <sstream>
#include <vector>

const int N = 5555;

char buffer[11111111];
int n, m, stamp, count;
std::vector<int> edge[N];
int visit[N];

void dfs(int x) {
	count++;
	visit[x] = stamp;
	for (int i = 0; i < (int)edge[x].size(); ++i) {
		int y = edge[x][i];
		if (visit[y] != stamp) {
			dfs(y);
		}
	}
}

void solve(void) {
	std::vector<int> source;
	for (int i = 1; i <= m; ++i) {
		int x;
		scanf("%d", &x);
		source.push_back(x);
	}
	for (int i = 1; i <= n; ++i) {
		edge[i].clear();
	}
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		
		gets(buffer);
		std::stringstream os(buffer);
		for (int y; os >> y; edge[x].push_back(y));
	}
	std::pair<int, int> best = std::make_pair(-1, -n);
	for (int i = 0; i < (int)source.size(); ++i) {
		count = 0;
		stamp++;
		dfs(source[i]);
		best = std::max(best, std::make_pair(count, -source[i]));
	}
	printf("%d\n", -best.second);
}

int main(void) {
	for (; ~scanf("%d%d", &n, &m); solve());
}
