#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const unsigned long long MAGIC = 4423;

const int N = 5001;

int n;
int child[N * 31][26];
bool accept[N * 31];
unsigned long long hash[N * 31]; 

void solve(void) {
	int size = 0;
	for (int i = 0; i < n; ++i) {
		static char text[111];
		scanf("%s", text);
		
		int length = (int)strlen(text);
		
		int now = 0;
		for (int j = 0; j < length; ++j) {
			int token = text[j] - 'a';
			if (!child[now][token]) {
				child[now][token] = ++size;
			}
			now = child[now][token];
		}
		accept[now] = true;
	}
	std::vector<unsigned long long> value;
	for (int x = size; x >= 0; --x) {
		hash[x] = 13;
		for (int token = 0; token < 26; ++token) {
//			if (child[x][token]) {
				hash[x] = hash[x] * MAGIC + hash[child[x][token]];
//			}
		}
		hash[x] = hash[x] * MAGIC + 17 + accept[x];
//		hash[x] = hash[x] * MAGIC + 1 + accept[x];
		value.push_back(hash[x]);
	}
	std::sort(value.begin(), value.end());
	value.erase(unique(value.begin(), value.end()), value.end());
	printf("%d\n", (int)value.size());
	
	for (int i = 0; i <= size; ++i) {
		accept[i] = 0;
		for (int token = 0; token < 26; ++token) {
			child[i][token] = 0;
		}
	}
}

int main(void) {
	for (; ~scanf("%d", &n); solve());
}
