#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

const double eps = 1e-6;
const int N = 1111;

int n;
double d;
bool mark[N];
std::pair<double, double> point[N];

double sqr(const double &x) {
	return x * x;
}

double dist(int i, int j) {
	return ceil(sqrt(sqr(point[i].first - point[j].first) + sqr(point[i].second - point[j].second)));
}

bool check(int x, int y) {
	if (mark[x] && mark[y]) {
		return dist(x, y) < d + eps;
	}
	if (mark[x] || mark[y]) {
		return dist(x, y) < d / 2 + eps;
	}
	return false;
}

bool check() {
	static bool visit[N];
	
	std::vector<int> queue;
	std::fill(visit + 1, visit + n + 1, 0);
	
	visit[1] = true;
	queue.push_back(1);
	
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		if (mark[x]) {
			for (int y = 1; y <= n; ++y) {
				if (visit[y]) {
					continue;
				}
				if (check(x, y)) {
					visit[y] = true;
					queue.push_back(y);
				}
			}
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		if (!visit[i]) {
			return false;
		}
	}
	return true;
}

void solve(void) {
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &point[i].first, &point[i].second);
		mark[i] = true;
	}
	if (!check()) {
		puts("-1");
		return;
	}
	for (int i = n; i >= 1; --i) {
		mark[i] = false;
		if (!check()) {
			mark[i] = true;
		}
	}
	bool first = true;
	for (int i = n; i >= 1; --i) {
		if (mark[i]) {
			first = false;
			putchar('1');
		}
		if (!mark[i] && !first) {
			putchar('0');
		}
	}
	puts("");
}	

int main(void) {
	for (; ~scanf("%d%lf", &n, &d); solve());
}
