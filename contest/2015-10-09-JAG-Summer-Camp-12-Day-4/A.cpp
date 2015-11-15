#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>


using namespace std;

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {-1, 1, 0, 0};

struct State{
	char x, y;
	bool level;
	int state;
	State() {}
	State(char x, char y, int state, bool level) : x(x), y(y), state(state), level(level) {}
};
int sx, sy, ex, ey, n, m;
int dist[52][52][1 << 10][2];
char g[52][52];
long long change[12][52], level[1 << 10][52], origin[52];

int bfs() {
	memset(dist, -1, sizeof dist);
	vector<State> queue;
	queue.push_back(State(sx, sy, 0, 0));
	dist[sx][sy][0][0] = 0;
	for (int nows = 0; nows < (int)queue.size(); nows++) {
		State now = queue[nows];
		int x = now.x, y = now.y, lv = now.level;
		int state = now.state;
		int nowdist = dist[x][y][state][lv];		
		
		if (x == ex && y == ey) return nowdist;
		if (g[x][y] == '|') {
			if (dist[x][y][state][lv ^ 1] == -1) {
				queue.push_back(State(x, y, state, lv ^ 1));
				dist[x][y][state][lv ^ 1] = nowdist + 1;
			}
		}
		if ((g[x][y] >= 'a' && g[x][y] <= 'j') || (g[x][y] >= 'A' && g[x][y] <= 'J')) {
				int num;
				if (g[x][y] >= 'a' && g[x][y] <= 'j') {
					num = g[x][y] - 'a' + 1;
				}
				if (g[x][y] >= 'A' && g[x][y] <= 'J') {
					num = g[x][y] - 'A' + 1;
				}
				int nstate = state ^ (1 << num - 1);
				int nlv = (level[nstate][x] & (1LL << y)) > 0;
				if (dist[x][y][nstate][nlv] == -1) {
					queue.push_back(State(x, y, nstate, nlv));
					dist[x][y][nstate][nlv] = nowdist + 1;
				}
		}
		
		for (int dir = 0; dir < 4; dir++) {
			int nx = x + dx[dir], ny = y + dy[dir], nstate = state, nlv = lv;
			if (nx < 1 || nx > n || ny > m || ny < 1) continue;
			if (g[nx][ny] == '#') continue;
			if (g[nx][ny] == '|') {
				if (dist[nx][ny][state][lv] == -1) {		
					queue.push_back(State(nx, ny, state, lv));
					dist[nx][ny][state][lv] = nowdist + 1;
				}
				continue;
			}
			if ((level[state][nx] & (1LL << ny)) == ((1LL * nlv) << ny)) {
				if (dist[nx][ny][state][nlv] == -1) {
					queue.push_back(State(nx, ny, state, nlv));
					dist[nx][ny][state][nlv] = nowdist + 1;
				}				
			}
		}
	}
	return -1;
}

void solve() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", g[i] + 1);
	}
	for (int i = 1; i <= n; i++) {
		long long num;
		for (int j = 1; j <= m; j++) {
			if (g[i][j] == '_' || (g[i][j] >= 'a' && g[i][j] <= 'j') || g[i][j] == '%' || g[i][j] == '&') {
				num = 0;
			} else num = 1;
			origin[i] ^= (num << j);
		}
	}
	int switches;
	scanf("%d", &switches);
	char str[55];
	for (int i = 1; i <= switches; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%s", str + 1);
			change[i][j] = 0;
			for (int k = 1; k <= m; k++) {
				if (str[k] == '*') {
					change[i][j] ^= (1LL << k);
				}
			}
		}
	}
	
	for (int state = 0; state < (1 << switches); state++) {
		for (int j = 1; j <= n; j++) {
			level[state][j] = origin[j];
		}
		
		for (int j = 1; j <= switches; j++) {
			if (1 << j - 1 & state) {
				for (int k = 1; k <= n; k++) {
					level[state][k] ^= change[j][k];
				}
			}
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (g[i][j] == '%') {
				sx = i;
				sy = j;
			}
			if (g[i][j] == '&') {
				ex = i;
				ey = j;
			}
		}
	}
	printf("%d\n", bfs());
}

int main() {
	solve();
	return 0;
}
