#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

const int N = 1111111;

int n;
int m[N], l[N], size[N];
std::vector<int> edge[N];

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", m + i, l + i);
		if (~l[i]) {
			edge[l[i]].push_back(i);
		}
	}
	
	std::vector<int> queue;
	for (int i = 0; i < n; ++i) {
		if (l[i] == -1) {
			queue.push_back(i);
		}
	}
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			queue.push_back(y);
		}
	}
	
	long long answer = 0;
	for (int index = n - 1; index >= 0; --index) {
		int x = queue[index];
		
		std::vector<int> list;
		
		size[x] = m[x];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			size[x] += size[y];
			list.push_back(size[y]);
		}
		
		std::sort(list.begin(), list.end());
		long long number = 0;
		for (int i = 0; i < (int)list.size(); ++i) {
			answer += number;
			number += list[i];
		}
	}
	std::cout << answer << std::endl;
}
