#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

const int N = 1111111;

class Node {
public:
    Node *child[2], *father;
    int size;
    long long key, sum, max;

    Node(long long key = 0);

    int side() {
        return father->child[1] == this;
    }

    void set(Node *son, int dir) {
        child[dir] = son;
        son->father = this;
    }

    void update() {
        size = child[0]->size + 1 + child[1]->size;
        sum = child[0]->sum + key + child[1]->sum;
        max = std::max(std::max(child[0]->max, child[1]->max), key);
    }
};

Node *null, *root;

Node::Node(long long key) : size(1), key(key), sum(key), max(key) {
    child[0] = child[1] = father = null;
}

void rotate(Node *x) {
    int dir = x->side();
    Node *p = x->father;
    p->set(x->child[dir ^ 1], dir);
    p->father->set(x, p->side());
    x->set(p, dir ^ 1);
    if (p == root) {
        root = x;
    }
    p->update();
    x->update();
}

void splay(Node *x, Node *target = null) {
    for (; x->father != target; ) {
        if (x->father->father == target) {
            rotate(x);
        } else {
            x->side() == x->father->side() 
            ? (rotate(x->father), rotate(x))
            : (rotate(x), rotate(x));
        }
    }
    x->update();
}

Node* kth(int size) {
    Node *x = root;
    for (; x->child[0]->size + 1 != size; ) {
        if (x->child[0]->size + 1 > size) {
            x = x->child[0];
        } else {
            size -= x->child[0]->size + 1;
            x = x->child[1];
        }
    }
    return x;
}

int rank(Node *x) {
	splay(x);
	return x->child[0]->size + 1;
}

void select(int left, int right) {
    splay(kth(right + 2));
    splay(kth(left), root);
}

void remove(Node *x) {
	int r = rank(x);
//printf("!!!%d\n", r);
	splay(kth(r - 1));
	splay(kth(r + 1), root);
	root->child[1]->child[0] = null;
	root->child[1]->update();
	root->update();
}

Node* insert(int pos, long long key) {
    select(pos, pos - 1);
    Node *x = root->child[0];
    Node *now = new Node(key);
    x->set(now, 1);
    splay(now);
    return now;
}

void build() {
    null = new Node();
    null->size = 0;
    root = new Node();
    Node *blank = new Node();
    root->set(blank, 1);
    splay(blank);
}

void print(Node *root) {
	if (root == null) {
		return;
	}
	print(root->child[0]);
	printf("%d ", root->key);
	print(root->child[1]);
}

int n;
Node *positive[N], *negative[N];

void solve(void) {
	std::set<int> set;
	for (int i = 1; i <= n; ++i) {
		set.insert(i);
	}
	
	build();
	for (int i = 1; i <= n; ++i) {
		static char type[111];
		int number;
		scanf("%s%d", type, &number);
		
		if (!strcmp(type, "insert")) {
			int x = *set.begin();
			set.erase(x);

			positive[x] = insert(number + 1, x);

			splay(positive[x]);
			Node *now = root;

			if (now->child[1] == null || now->child[1]->max <= 0) {
				negative[x] = insert(root->size - 1, -x);
			} else {
				for (now = now->child[1]; now; ) {
					if (now->child[0] != null && now->child[0]->max > 0) {
						now = now->child[0];
					} else if (now->key > 0) {
						break;
					} else {
						now = now->child[1];
					}
				}
				
				negative[x] = insert(rank(negative[now->key]) - 1, -x);
			}
		} else if (!strcmp(type, "remove")) {
			set.insert(number);
			remove(positive[number]);
			remove(negative[number]);
		} else if (!strcmp(type, "query")) {
			int left = rank(positive[number]) - 1;
			int right = rank(negative[number]) - 1;
			select(left, right);
			printf("%I64d\n", root->child[0]->child[1]->sum);
		}
/*
print(root);
puts("");
*/	}
}

int main(void) {
	for (int tests = 1; ~scanf("%d", &n); ++tests) {
		printf("Case #%d:\n", tests);
		solve();
	}
}
