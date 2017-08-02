#include <iostream>
#include <vector>

class Node {
public:
    Node *child[26], *fail;
    int counter;

    Node();
};

std::vector<Node *> pool;

Node::Node() : fail(NULL), counter(0) {
    pool.push_back(this);
    memset(child, NULL, sizeof child);
}

Node *root;

void insert(Node *x, char *text) {
    int length = (int)strlen(text);
    for (int i = 0; i < length; i++) {
        int token = text[i] - 'a';
        if (!x->child[token]) {
            x->child[token] = new Node();
        }
        x = x->child[token];
    }
    x->counter++;
}

void build() {
    std::vector<Node *> queue;
    queue.push_back(root->fail = root);
    for (int head = 0; head < (int)queue.size(); ++head) {
        Node *x = queue[head];
        for (int token = 0; token < 26; ++token) {
            if (x->child[token]) {
                x->child[token]->fail = (x == root) ? root : x->fail->child[token];
                x->child[token]->counter += x->child[token]->fail->counter;
                queue.push_back(x->child[token]);
            } else {
                x->child[token] = (x == root) ? root : x->fail->child[token];
            }
        }
    }
}

const int N = 666666;

int n, m;
std::string texta[N];

void solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        static char text[N];
        scanf("%s", text);
        texta[i] = text;
    }

    root = new Node();

    for (int i = 1; i <= m; i++) {
        static char text[N];
        scanf("%s", text);
        insert(root, text);
    }

    build();
    long long ans = 0;
    int len;
    for (int i = 1; i <= n; i++) {
        ans = 0;
        Node *now = root;
        for (int j = 0; j < (int)texta[i].length(); j++) {
            now = now->child[texta[i][j] - 'a'];
            ans += now->counter;
        }
        printf("%I64d\n", ans);
    }

    for (int i = 0; i < (int)pool.size(); ++i) {
        delete pool[i];
    }
    pool.clear();
}

int main() {
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
    return 0;
}
