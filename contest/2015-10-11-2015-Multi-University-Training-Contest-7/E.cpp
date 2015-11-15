#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
char text[9999];
int repeat, sum[2];
void solve() {
	int len = strlen(text);
	int tot = 0;
	sum[0] = sum[1] = 0;
	for (int i = 0; i < len; i++) {
		tot += text[i] - '0';
		sum[i & 1] += text[i] - '0';
	}
	vector<int> num;
	for (int i = 0; i < repeat; i++) {
		num.clear();
		for (int tmp = tot; tmp; tmp /= 10) {
			tot += tmp % 10;
			num.push_back(tmp % 10);
		}
		reverse(num.begin(), num.end());
		for (int j = 0; j < (int)num.size(); j++) {
			sum[len & 1] += num[j];
			len++;
		}
	}
	int rest = abs(sum[0] - sum[1]);
	if (rest % 11 == 0) {
		puts("Yes");
	} else {
		puts("No");
	}
}

int main() {
	for (;scanf("%s%d", text, &repeat) && repeat != -1; ) {
		static int counter = 0;
		printf("Case #%d: ", ++counter);
		solve();
	}
	return 0;
}
