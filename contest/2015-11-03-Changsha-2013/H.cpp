#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
#define floor FLLOORR
const double eps = 1e-10;
const double PI = acos(-1.);
int check(int edges, double radius, double h, double limit) {
	double angle = 2 * PI / edges / 2;
	return tan(angle) * radius * 2 * h > limit - eps;
}

double calc(int edges, double radius, double h) {
	double angle = 2 * PI / edges / 2;
	double area = tan(angle) * radius * 2 *  edges * h;
	return area;
}

double R, r, height;
int floor;
double h, limit;
void solve() {	
	double delta = (R - r) / floor;
	h = height / floor;
	int edges = 3;
	double answer = 0;
	for (int i = 1; i <= floor; i++) {
		for (; check(edges, r, h, limit); edges++);
		edges--;
		answer += calc(edges, r, h);
		r += delta;
	}
	
	printf("%.3f\n", answer);
	
}
int main() {
	for (; ~scanf("%lf%lf%lf%d%lf", &R, &r, &height, &floor, &limit) ; solve());
	return 0;
}
