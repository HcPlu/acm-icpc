#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

int main() {    
    pair<int, int> now = make_pair(0, 0);
    for(int i = 30; i >= 0; i--) {
        pair<int, int> temp = now;
        temp.first += (1 << i);
        if(temp.first >= 1000000000) {
            continue;
        }
        printf("%d %d\n", temp.first, temp.second);
        fflush(stdout);
        int flag;
        scanf("%d", &flag);
        printf("%d %d\n", temp.first + 1, temp.second);
        fflush(stdout);
        scanf("%d", &flag);
        if(flag == 1) {
            now = temp;
        }
    }
    
    for(int i = 30; i >= 0; i--) {
        pair<int, int> temp = now;
        temp.second += (1 << i);
        if(temp.second >= 1000000000) {
            continue;
        }
        printf("%d %d\n", temp.first, temp.second);
        fflush(stdout);
        int flag;
        scanf("%d", &flag);
        printf("%d %d\n", temp.first, temp.second + 1);
        fflush(stdout);
        scanf("%d", &flag);
        if(flag == 1) {
            now = temp;
        }
    }
    pair<int, int> ans = make_pair(0, 0);
    for(int i = 0; i <= 1; i++)
        for(int j = 0; j <= 1; j++) {
            int flag;
            printf("%d %d\n", ans.first, ans.second);
            fflush(stdout);
            scanf("%d", &flag);
            printf("%d %d\n", now.first + i, now.second + j);
            fflush(stdout);
            scanf("%d", &flag);
            if(flag == 1) {
                ans = make_pair(now.first + i, now.second + j);
            }
        }
    printf("A %d %d\n", ans.first, ans.second);
    return 0;
}
