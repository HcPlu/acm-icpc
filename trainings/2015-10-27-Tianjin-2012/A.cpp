#include <iostream>
#include <vector>

using namespace std;
int cnt[5][10], backup[5][10];
int id[222], tp[222];

int check2() {
    int ret = 0;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 9; j++) {
            backup[i][j] = cnt[i][j];
        }
    }

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (backup[i][j] >= 3) {
                ret++;
                backup[i][j] -= 3;
            }
            while (backup[i][j] && backup[i][j + 1] && backup[i][j + 2]) {
                backup[i][j]--;
                backup[i][j + 1]--;
                backup[i][j + 2]--;
                ret++;
            }
        }
    }

    for (int i = 1; i <= 7; i++) {
        if (backup[4][i] == 3) {
            ret++;
        }
    }

    if (ret == 4) {
        return 1;
    } else {
        return 0;
    }

}

int check(vector<pair<int, int> > card) {
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < 14; i++) {
        ++cnt[card[i].first][card[i].second];
    }

    int flg = 1;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 9; j++) {
            if (cnt[i][j] > 0 && cnt[i][j] != 2) {
                flg = 0;
            }
        }
    }
    for (int i = 1; i <= 7; i++) {
        if (cnt[4][i] > 0 && cnt[4][i] != 2) {
            flg = 0;
        }
    }

    if (flg) {
        return 1;
    }

    int flg1 = 1;
    int flg2 = 0;
    for (int i = 1; i <= 3; i++) {
        if (cnt[i][9] < 1 || cnt[i][1] < 1) {
            flg1 = 0;
        }
        if (cnt[i][1] > 1 || cnt[i][9] > 1) {
            flg2 = 1;
        }
    }

    for (int i = 1; i <= 7; i++) {
        if (cnt[4][i] < 1) {
            flg1 = 0;
        }
        if (cnt[4][i] > 1) {
            flg2 = 1;
        }
    }
    if (flg1 && flg2) {
        return 1;
    }

    for (int i = 0; i < 14; i++) {
        if (cnt[card[i].first][card[i].second] >= 2) {
            cnt[card[i].first][card[i].second] -= 2;
            if (check2()) {
                return 1;
            }
            cnt[card[i].first][card[i].second] += 2;
        }
    }
    return 0;
}

vector<pair<int, int> > card;
int counter[5][10];

void solve() {
    char text[111];
    card.clear();
    memset(counter, 0, sizeof counter);
    for (int i = 0; i < 13; i++) {
        scanf("%s", text);
        card.push_back(make_pair(id[text[1]], text[0] - '0'));
        ++counter[card[i].first][card[i].second];
    }
    vector<pair<int, int> > answer;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= (i < 4 ? 9 : 7); j++) {
            if ((i < 4 && j != 1 && j != 9) || (i == 4 && j != 1 && j != 7)) {
                if (counter[i][j] == 0 && counter[i][j + 1] == 0 && counter[i][j - 1] == 0) {
                    continue;
                }
            }
            if (counter[i][j] == 4) {
                continue;
            }
            card.push_back(make_pair(i, j));
            if (check(card)) {
                answer.push_back(make_pair(i, j));
            }
            card.pop_back();
        }
    }

    sort(answer.begin(), answer.end());

    if (answer.size() == 0) {
        puts("Nooten");
        return;
    }

    printf("%d", (int)answer.size());
    for (int i = 0; i < (int)answer.size(); i++) {
        printf(" %d%c", answer[i].second, tp[answer[i].first]);
    }
    puts("");
}

int main() {
    int tests;
    id['m'] = 1;
    id['s'] = 2;
    id['p'] = 3;
    id['c'] = 4;
    tp[1] = 'm';
    tp[2] = 's';
    tp[3] = 'p';
    tp[4] = 'c';
    scanf("%d", &tests);
    for (int i = 1; i <= tests; i++) {
        solve();
    }
    return 0;
}
