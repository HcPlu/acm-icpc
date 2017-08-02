#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

const int mod = 2012;
const int N = 1111111;

class Node {
public:
    Node *child[11], *parent;
    int length, degree, answer, count;

    Node(int length);

    Node *extend(Node *start, int token) {
        Node *p = this;
        Node *np = new Node(length + 1);
        for (; p && !p->child[token]; p = p->parent) {
            p->child[token] = np;
        }
        if (!p) {
            np->parent = start;
        } else {
            Node *q = p->child[token];
            if (p->length + 1 == q->length) {
                np->parent = q;
            } else {
                Node *nq = new Node(p->length + 1);
                memcpy(nq->child, q->child, sizeof(q->child));
                nq->parent = q->parent;
                np->parent = q->parent = nq;
                for (; p && p->child[token] == q; p = p->parent) {
                    p->child[token] = nq;
                }
            }
        }
        return np;
    }
};

std::vector<Node *> state;

Node::Node(int length = 0) : parent(NULL), length(length), degree(0), answer(0), count(0) {
    memset(child, NULL, sizeof(child));
    state.push_back(this);
}

int n;

/*
int id(Node *x) {
	for (int i = 0; i < (int)state.size(); ++i) {
		if (x == state[i]) {
			return i;
		}
	}
	return -1;
}
*/
void solve(void) {
    Node *start = new Node();
    Node *last = start;

    for (int i = 0; i < n; ++i) {
        static char text[N];
        scanf("%s", text);

        int length = (int)strlen(text);
        for (int j = 0; j < length; ++j) {
            last = last->extend(start, text[j] - '0');
        }
        last = last->extend(start, 10);
    }

    for (int i = 0; i < (int)state.size(); ++i) {
        Node *x = state[i];
        for (int token = 0; token <= 10; ++token) {
            Node *y = x->child[token];
            if (!y) {
                continue;
            }
            y->degree++;
        }
    }
    /*
    printf("%d\n", (int)state.size());
    for (int i = 0; i < (int)state.size(); ++i) {
        for (int token = 0; token <= 10; ++token) {
            if (state[i]->child[token]) {
                printf("%d ", id(state[i]->child[token]));
            } else {
                printf("# ");
            }
        }
        puts("");
    }

    for (int i = 0; i < (int)state.size(); ++i) {
        printf("%d ", state[i]->degree);
    }
    puts("");
    */
    std::vector<Node *> queue;
    queue.push_back(start);
    for (int head = 0; head < (int)queue.size(); ++head) {
        Node *x = queue[head];
        for (int token = 0; token <= 10; ++token) {
            Node *y = x->child[token];
            if (!y) {
                continue;
            }
            if (--y->degree == 0) {
                //puts("xxxx");
                queue.push_back(y);
            }
        }
    }
    /*
    for (int i = 0; i < (int)queue.size(); ++i) {
        printf("%d ", id(queue[i]));
    }
    puts("");
    */
    start->count = 1;

    for (int i = 0; i < (int)queue.size(); ++i) {
        Node *x = queue[i];

        for (int token = 0; token < 10; ++token) {
            if (x == start && token == 0) {
                continue;
            }
            Node *y = x->child[token];
            if (!y) {
                continue;
            }
            y->count += x->count;
            y->count %= mod;

            y->answer += (x->answer * 10 + token * x->count) % mod;
            y->answer %= mod;
        }
    }

    int answer = 0;
    for (int i = 0; i < (int)state.size(); ++i) {
        answer += state[i]->answer;
        answer %= mod;
    }

    printf("%d\n", answer);

    for (int i = 0; i < (int)state.size(); ++i) {
        delete state[i];
    }
    state.clear();
}

int main(void) {
    for (; ~scanf("%d", &n); solve()) {
    }
}
