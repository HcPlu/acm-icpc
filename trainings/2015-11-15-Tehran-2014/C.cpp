#include <iostream>

using namespace std;
const int N = 22222;
int hassolved[22], solved[22][222], number[222], total, N;
int teams, problems, n;

struct Submission {
    int id, prob, ok;
    string happen;

    Submission() {
    }

    Submission(int id, int prob, string happen, int ok) : id(id), prob(prob), happen(happen), ok(ok) {
    }
} submission[N];

int calc(const string &text) {
    return ((text[0] - '0') * 10 + (text[1] - '0')) * 3600 + ((text[3] - '0') * 10 + (text[4] - '0')) * 60 +
           (text[6] - '0') * 10 + (text[7] - '0');
}

bool cmp(Submission p1, Submission p2) {
    return calc(p1.happen) < calc(p2.happen);
}

int check() {
    int flag = 1;
    flag = flag && (total == teams);
    flag = flag && (N < problems);
    int tmp = 1;
    for (int i = 0; i < problems; i++) {
        if (!hassolved[i]) {
            tmp = 0;
            break;
        }
        if (hassolved[i] == teams) {
            tmp = 0;
            break;
        }
    }
    flag = flag && tmp;
    return flag;
}

void solve() {
    for (int i = 0; i < n; i++) {
        int id;
        static char text1[11], text2[11], text3[111];
        scanf("%d %s %s ", &id, text1, text2);
        gets(text3);
        string tmp = text2;
        submission[i] = Submission(id, text1[0] - 'A', tmp, text3[0] == 'Y' ? 1 : 0);
    }
    sort(submission, submission + n, cmp);
    string left = "--:--:--";
    string right = "--:--:--";
    total = 0;
    N = 0;
    memset(hassolved, 0, sizeof hassolved);
    memset(solved, 0, sizeof solved);
    memset(number, 0, sizeof number);
    int hasbegin = 0;

    for (int i = 0; i < n; i++) {
        int t = submission[i].id;
        int prob = submission[i].prob;
        int ok = submission[i].ok;
        if (!ok)
            continue;
        if (!solved[prob][t]) {
            solved[prob][t] = 1;
            if (!number[t]) {
                number[t]++;
                total++;
            } else {
                number[t]++;
            }
            hassolved[prob]++;
            N = max(number[t], N);

        }
        int flag = check();
        if (flag) {
            if (!hasbegin) {
                hasbegin = 1;
                left = submission[i].happen;
            }
        }
        if (hasbegin && (flag == 0)) {
            right = submission[i].happen;
            break;
        }
    }
    printf("%s %s\n", left.c_str(), right.c_str());
}

int main() {
    for (; scanf("%d%d%d", &teams, &problems, &n) == 3 && (teams || problems || n); solve());
}
