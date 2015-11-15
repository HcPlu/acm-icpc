#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>

const int N = 222222;

class Node {
public:
	int sum, max, lmax, rmax;
	
	Node() {
		sum = max = lmax = rmax = INT_MAX;
	}
	
	Node(int val, int len) {
		sum = val * len;
		max = lmax = rmax = std::max(val * len, val);
	}
	
	Node(int sum, int max, int lmax, int rmax) : sum(sum), max(max), lmax(lmax), rmax(rmax) {}
	
	Node reverse() const {
		return Node(sum, max, rmax, lmax);
	}
	
	void print() const {
		printf("sum = %d; max = %d; lmax = %d; rmax = %d\n", sum, max, lmax, rmax);
	}	
	
	friend Node operator + (const Node &a, const Node &b) {
		if (a.sum == INT_MAX) {
			return b;
		}
		if (b.sum == INT_MAX) {
			return a;
		}
		Node c;
		c.sum = a.sum + b.sum;
		c.lmax = std::max(a.lmax, a.sum + b.lmax);
		c.rmax = std::max(b.rmax, b.sum + a.rmax);
		c.max = std::max(a.max, b.max);
		c.max = std::max(c.max, a.rmax + b.lmax);
		return c;
	}
	
	Node& operator += (const Node &other) {
		(*this) = (*this) + other;
		return *this;
	}
};

int n, q;
std::vector<int> edge[N];
int father[N], height[N], size[N], son[N], top[N], pos[N], data[N], value[N];

Node tree[N << 2];
int tag[N << 2], len[N << 2];

void modify(int x, int val) {
	tree[x] = Node(val, len[x]);
	tag[x] = val;
}

void release(int x) {
	if (tag[x] != INT_MAX) {
		modify(x << 1, tag[x]);
		modify(x << 1 | 1, tag[x]);
		tag[x] = INT_MAX;
	}
}

void update(int x) {
	tree[x] = tree[x << 1] + tree[x << 1 | 1];
}

void modify(int x, int l, int r, int ql, int qr, int val) {
	if (qr < l || r < ql) {
		return;
	}
	if (ql <= l && r <= qr) {
		modify(x, val);
		return;
	}
	release(x);
	int mid = l + r >> 1;
	modify(x << 1, l, mid, ql, qr, val);
	modify(x << 1 | 1, mid + 1, r, ql, qr, val);
	update(x);
}

Node query(int x, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) {
		return Node();
	}
	if (ql <= l && r <= qr) {
		return tree[x];
	}
	release(x);
	int mid = l + r >> 1;
	return query(x << 1, l, mid, ql, qr) + query(x << 1 | 1, mid + 1, r, ql, qr);
}

void build(int x, int left, int right) {
	len[x] = right - left + 1;
	tag[x] = INT_MAX;
	if (left == right) {
		tree[x] = Node(data[left], 1);
	} else {
		int mid = left + right >> 1;
		build(x << 1, left, mid);
		build(x << 1 | 1, mid + 1, right);
		update(x);
	}
}

void build(int root) {
	std::vector<int> queue;
	father[root] = -1;
	height[root] = 0;
	queue.push_back(root);
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (y != father[x]) {
				father[y] = x;
				height[y] = height[x] + 1;
				queue.push_back(y);
			}
		}
	}
	for (int index = n - 1; index >= 0; --index) {
		int x = queue[index];
		size[x] = 1;
		son[x] = -1;
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (y != father[x]) {
				size[x] += size[y];
				if (son[x] == -1 || size[son[x]] < size[y]) {
					son[x] = y;
				}
			}
		}
	}
	std::fill(top, top + n, 0);
	int counter = 0;
	for (int index = 0; index < n; ++index) {
		int x = queue[index];
		if (top[x] == 0) {
			for (int y = x; y != -1; y = son[y]) {
				top[y] = x;
				pos[y] = ++counter;
				data[counter] = value[y];
			}
		}
	}
	build(1, 1, n);
}

void modify(int x, int y, int val) {
	while (true) {
		if (top[x] == top[y]) {
			if (x == y) {
				modify(1, 1, n, pos[x], pos[y], val);
			} else {
				if (height[x] < height[y]) {
					modify(1, 1, n, pos[x], pos[y], val);
				} else {
					modify(1, 1, n, pos[y], pos[x], val);
				}
			}
			break;
		}
		if (height[top[x]] > height[top[y]]) {
			modify(1, 1, n, pos[top[x]], pos[x], val);
			x = father[top[x]];
		} else {
			modify(1, 1, n, pos[top[y]], pos[y], val);
			y = father[top[y]];
		}
	}
}

int query(int x, int y) {
	Node answerx = Node(), answery = Node();
	while (true) {
		if (top[x] == top[y]) {
			if (x == y) {
				answerx += query(1, 1, n, pos[x], pos[y]).reverse();
			} else {
				if (height[x] < height[y]) {
					answery += query(1, 1, n, pos[x], pos[y]).reverse();
				} else {
					answerx += query(1, 1, n, pos[y], pos[x]).reverse();
				}
			}
			break;
		}
		if (height[top[x]] > height[top[y]]) {
			answerx += query(1, 1, n, pos[top[x]], pos[x]).reverse();
			x = father[top[x]];
		} else {
			answery += query(1, 1, n, pos[top[y]], pos[y]).reverse();
			y = father[top[y]];
		}
	}

//	answerx.print();
//	answery.print();
	return (answerx + answery.reverse()).max;
}

int main(void) {
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", value + i);
	}
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	build(1);
	for (int i = 1; i <= q; ++i) {
		int type, a, b, c;
		scanf("%d%d%d%d", &type, &a, &b, &c);
		if (type == 1) {
			modify(a, b, c);
		} else {
			printf("%d\n", query(a, b));
		}
	}
}
