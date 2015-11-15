#include <cstdio>
#include <algorithm>
#include <vector>

const long long mod = 1e9 + 7;

const int N = 222222;

int n;
int father[N];
bool leaf[N];
long long fact[N], answer[N];
std::vector<int> edge[N];

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		edge[i].clear();
	}
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	
	std::vector<int> queue;
	father[1] = 0;
	queue.push_back(1);
	
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (y == father[x]) {
				continue;
			}
			father[y] = x;
			queue.push_back(y);
		}
	}
	
	for (int index = n - 1; index >= 0; --index) {
		int x = queue[index];
		
		leaf[x] = true;
		answer[x] = 1;
		
		int leaves = 0, others = 0;
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (y == father[x]) {
				continue;
			}

			leaf[x] = false;
			(answer[x] *= answer[y]) %= mod;

			if (leaf[y]) {
				leaves++;
			} else {
				others++;
			}
		}
		
		if (!leaf[x]) {
			(answer[x] *= fact[leaves]) %= mod;

			if (others > 2) {
				puts("0");
				return;
			}
		
			if (others < 2) {
				(answer[x] *= 2) %= mod;
			}
		}
	}
	
	printf("%d\n", (int)answer[1]);
}

int main(void) {
	fact[0] = 1;
	for (int i = 1; i < N; ++i) {
		fact[i] = (fact[i - 1] * i) % mod;
	}
	
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}
