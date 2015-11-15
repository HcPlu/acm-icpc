#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Point {
	long long x, y;
	Point() {}
	Point(long long x, long long y) : x(x), y(y) {};
	void scan() {
		scanf("%lld%lld", &x, &y);
	}
	friend long long det(Point a, Point b) {
		return a.x * b.y - a.y * b.x;
	}
	friend long long dot(Point a, Point b) {
		return a.x * b.x + a.y * b.y;
	}
	friend long long dist(Point a, Point b) {
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}
	friend Point operator - (Point a, Point b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	long long len() {
		return (x * x + y * y);
	}
}point[10];

bool equal() {
	for (int i = 0; i < 4; i++) {
		if (dist(point[i], point[(i + 1) % 4]) != dist(point[(i + 1) % 4], point[(i + 2) % 4])) return 0;
	}
	return 1;
}

void solve() {
	for (int i = 0; i < 4; i++) {
		point[i].scan();
	}
	string ans;
	if (equal()) {
		Point t1 = point[1] - point[0];
		Point t2 = point[2] - point[1];
		if (dot(t1, t2) == 0) {
			ans = "Square";
		}
		else ans = "Diamond";
	} else {
		Point t1 = point[1] - point[0];
		Point t2 = point[2] - point[1];
		Point t3 = point[3] - point[2];
		Point t4 = point[0] - point[3];
		if (det(t1, t3) != 0 || det(t2, t4) != 0) {
			ans = "Others";
		} else {
			if (dot(t1, t2) == 0) {
				ans = "Rectangle";
			} else {
				ans = "Parallelogram";
			}
		}
	}
	cout << ans << endl;
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
}
