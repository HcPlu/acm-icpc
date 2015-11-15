#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const double eps =  1e-10;
double answer, l, r, prob, delta, target;
int k;

void dfs(double l, double r, int dep, double p) {
	if (dep > k) {
		double mid = (l + r) / 2;
		if (mid < target + delta + eps && mid > target - delta - eps) {
			answer += p;
		}
		return;
	} else {
		if (r < target + delta + eps && l > target - delta - eps) {
			answer += p;
			return;
		} else {
			if (l > target + delta + eps || r < target - delta - eps) {
				return;
			}
			double mid = (l + r) / 2;
			if (mid > target - eps) {
				dfs(l, mid, dep + 1, p * (1 - prob));
				dfs(mid, r, dep + 1, p * prob);
			} else {
				dfs(l, mid, dep + 1, p * prob);
				dfs(mid, r, dep + 1, p * (1 - prob));
			}
		}
	}
}

int main() {
	scanf("%d%lf%lf", &k, &l, &r);
	scanf("%lf%lf%lf", &prob, &delta, &target);
	answer = 0;
	dfs(l, r, 1, 1.);
	printf("%.10f\n", answer);
}
