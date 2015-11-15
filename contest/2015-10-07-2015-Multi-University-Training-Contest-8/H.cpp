#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
char text[10];
void out(int num) {
	if (!num) {
		printf("%d",num);
		return;
	}

	int divide = __gcd(120, num);
	if (divide == 120) {
		printf("%d", num / 120);
		return;
	}
	printf("%d/%d", num / divide, 120 / divide);
}
void solve() {
	scanf("%s", text);
	int hour = (text[0] - '0') * 10 + text[1] - '0';
	hour %= 12;
	int minite = (text[3] - '0') * 10 + text[4] - '0';
	int second = (text[6] - '0') * 10 + text[7] - '0';
	
	int angle1 = 3600 * hour + minite * 60 + second;
	int angle2 = 6 * 120 * minite + second * 12;
	int angle3 = 6 * 120 * second;
	int ans1 = abs(angle1 - angle2);
	int ans2 = abs(angle1 - angle3);
	int ans3 = abs(angle2 - angle3);
	
	ans1 = min(ans1, 360 * 120 - ans1);
	ans2 = min(ans2, 360 * 120 - ans2);
	ans3 = min(ans3, 360 * 120 - ans3);



/*	double angle1 = 30 * hour + minite / 2 + second / 120;
	double angle2 = 6 * minite + second / 10;
	double angle3 = 6 * second;
	double ans1 = fabs(angle1 - angle2);
	ans1 = min()
	double ans2 = fabs(angle1 - angle3);
	double ans3 = fabs(angle2 - angle3);*/
	
	out(ans1);putchar(' ');
	out(ans2);putchar(' ');
	out(ans3);puts(" ");
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}
