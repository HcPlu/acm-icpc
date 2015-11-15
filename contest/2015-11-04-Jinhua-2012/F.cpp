#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int N = 1111;

class Polynomial {
public:
	int degree;
	int item[N];
	
	Polynomial(int degree = 0) : degree(degree) {
		memset(item, 0, sizeof(item));
	}
	
	friend bool operator < (const Polynomial &a, const Polynomial &b) {
		if (a.degree != b.degree) {
			return a.degree < b.degree;
		} else {
			for (int i = a.degree; i >= 0; --i) {
				if (std::abs(a.item[i]) != std::abs(b.item[i])) {
					return std::abs(a.item[i]) < std::abs(b.item[i]);
				} else if (a.item[i] != b.item[i]) {
					return a.item[i] < 0;
				}
			}
		}
		return false;
	}
	
	friend Polynomial operator / (Polynomial a, const Polynomial &b) {
		Polynomial c(a.degree - b.degree);
		for (int i = c.degree; i >= 0; --i) {
			int t = a.item[i + b.degree] / b.item[b.degree];
			c.item[i] = t;
			for(int j = 0; j <= b.degree; j++) {
				a.item[i + j] -= t * b.item[j]; 
			}
		}
		while(c.item[c.degree] == 0 && c.degree > 0) c.degree--;
		return c;
	}
	
	void print() const {
		putchar('(');
		for (int i = degree; i >= 0; --i) {
			if (item[i] == 0) {
				continue;
			}
			
			if (item[i] > 0) {
				if (i != degree) {
					putchar('+');
				}
			} else {
				putchar('-');
			}
			
			if (i == 0) {
				printf("%d", std::abs(item[i]));
			} else {
				if (std::abs(item[i]) != 1) {
					printf("%d", std::abs(item[i]));
				}
			}
			
			if (i != 0) {
				putchar('x');
				if (i >= 2) {
					putchar('^');
					printf("%d", i);
				}
			}
		}
		putchar(')');
	}
};

int n;
std::vector<int> factor[N];
Polynomial divide[N];

void solve(void) {
	if (n == 1) {
		puts("x-1");
		return;
	}

	std::vector<Polynomial> answer;
	
	for (int i = 0; i < (int)factor[n].size(); ++i) {
		int x = factor[n][i];
		answer.push_back(divide[x]);
	}
	
	std::sort(answer.begin(), answer.end());
	for (int i = 0; i < (int)answer.size(); ++i) {
		answer[i].print();
	}
	puts("");
}

int main(void) {
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			factor[j].push_back(i);
		}
	}
	
	for (int i = 1; i < N; ++i) {
		divide[i].degree = i;
		divide[i].item[i] = 1;
		divide[i].item[0] = -1;
		
		for (int j = 0; j < (int)factor[i].size(); ++j) {
			int k = factor[i][j];
			
			if (k != i) {
				divide[i] = divide[i] / divide[k];
			}
		}
	}
	
	for (; scanf("%d", &n) && n; solve());
}
