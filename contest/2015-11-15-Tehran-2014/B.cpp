#include <iostream>
#include <cstring>
#include <cstdio>

#include <algorithm>
#include <string>
using namespace std;
const string name[16] = {"White", "Silver", "Gray", "Black", "Red", "Maroon", "Yellow", "Olive", "Lime", "Green", "Aqua", "Teal", "Blue", "Navy", "Fuchsia", "Purple"};
const int r[16] = {255, 192, 128, 0, 255, 128, 255, 128, 0, 0, 0, 0, 0, 0, 255, 128};
const int g[16] = {255, 192, 128, 0, 0, 0, 255, 128, 255, 128, 255, 128, 0, 0, 0, 0};
const int b[16] = {255, 192, 128, 0, 0, 0, 0, 0, 0, 0, 255, 128, 255, 128, 255, 128};
int x, y, z;
int calc(int i) {
	return (r[i] - x) * (r[i] - x) + (g[i] - y) * (g[i] - y)  + (b[i] - z) * (b[i] - z);
}
void solve() {
	int answer = 0;
	for (int i = 0; i < 16; i++) {
		if (calc(i) < calc(answer)) {
			answer = i;
		}
	}
	puts(name[answer].c_str());
}
int main() {
	for (; scanf("%d%d%d", &x, &y, &z) && ((x != -1) || (y != -1) || (z != -1)); solve());
}
