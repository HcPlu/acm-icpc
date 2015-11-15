#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>

const int N = 111;

int n, m, answer;
int graph[N][N];

void dfs(int size, std::vector<int> vector) {
	if (size * (size - 1) / 2 > m) {
		return;
	}
	if (size >= 2) {
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (i == j) {
					continue;
				}
				if (graph[vector[i]][vector[j]] == 0) {
					return;
				}
			}
		}
		int total = 0;
		for (int i = 0; i < size; ++i) {
			int number = INT_MAX;
			for (int j = 0; j < size; ++j) {
				if (i == j) {
					continue;
				}
				number = std::min(number, graph[vector[i]][vector[j]]);
			}
			total += number;
		}
		answer = std::max(answer, total);
	}
	int prev = (size == 0) ? -1 : vector.back();
	for (int i = prev + 1; i < n; ++i) {
		vector.push_back(i);
		dfs(size + 1, vector);
		vector.pop_back();
	}
}

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		graph[x - 1][y - 1] = w;
		graph[y - 1][x - 1] = w;
	}
	answer = 0;
	dfs(0, std::vector<int>());
	printf("%d\n", answer);
}
