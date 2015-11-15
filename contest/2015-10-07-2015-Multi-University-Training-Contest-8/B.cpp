#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

const int N = 11111;
const int size = 300;

class Node {
public:
	int l, r, id;

	friend bool operator < (const Node &a, const Node &b) {
		int blocka = a.l / size;
		int blockb = b.l / size;
		if (blocka == blockb) {
			if (blocka & 1) {
				return a.r < b.r;
			} else {
				return a.r > b.r;
			}
		} else {
			return std::make_pair(blocka, a.r) < std::make_pair(blockb, b.r);
		}
	}
};

int n, m;
int a[N];
Node q[N];
std::vector<std::pair<int, int> > left[N], right[N];
long long answer[N];

void prepare() {
	for (int i = 1; i <= n + 1; ++i) {
		right[i].clear();
	}
	for (int i = n; i >= 1; --i) {
		right[i].push_back(std::make_pair(a[i], i));
		
		for (int j = 0; j < (int)right[i + 1].size(); ++j) {
			int number = std::__gcd(a[i], right[i + 1][j].first);
			
			if (number == right[i].back().first) {
				right[i].back().second = right[i + 1][j].second;
			} else {
				right[i].push_back(std::make_pair(number, right[i + 1][j].second));
			}
		}
	}
	
	for (int i = 0; i <= n; ++i) {
		left[i].clear();
	}
	for (int i = 1; i <= n; ++i) {
		left[i].push_back(std::make_pair(a[i], i));
		
		for (int j = 0; j < (int)left[i - 1].size(); ++j) {
			int number = std::__gcd(a[i], left[i - 1][j].first);
			
			if (number == left[i].back().first) {
				left[i].back().second = left[i - 1][j].second;
			} else {
				left[i].push_back(std::make_pair(number, left[i - 1][j].second));
			}
		}
	}
}

long long queryr(int x, int l, int r) {
	long long answer = 0;
	for (int i = 0; i < (int)right[x].size(); ++i) {
		int head = (i == 0) ? x : right[x][i - 1].second + 1;
		int tail = right[x][i].second;
		head = std::max(head, l);
		tail = std::min(tail, r);
		if (head <= tail) {
			answer += 1LL * (tail - head + 1) * right[x][i].first;
		}
	}
	return answer;
}

long long queryl(int x, int l, int r) {
	long long answer = 0;
	for (int i = 0; i < (int)left[x].size(); ++i) {
		int head = left[x][i].second;
		int tail = (i == 0) ? x : left[x][i - 1].second - 1;
		head = std::max(head, l);
		tail = std::min(tail, r);
		if (head <= tail) {
			answer += 1LL * (tail - head + 1) * left[x][i].first;
		}
	}
	return answer;
}

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	
	prepare();
	
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &q[i].l, &q[i].r);
		answer[i] = 0;
		q[i].id = i;
	}
	std::sort(q + 1, q + m + 1);
	
	int l = 1, r = 1;
	long long result = a[1];

	for (int i = 1; i <= m; ++i) {
		for (; l < q[i].l; l++) {
			result -= queryr(l, l, r);
		}
		for (; l > q[i].l; l--) {
			result += queryr(l - 1, l - 1, r);
		}
		for (; r < q[i].r; r++) {
			result += queryl(r + 1, l, r + 1);
		}
		for (; r > q[i].r; r--) {
			result -= queryl(r, l, r);
		}
		answer[q[i].id] = result;
	}
	
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", answer[i]);
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
