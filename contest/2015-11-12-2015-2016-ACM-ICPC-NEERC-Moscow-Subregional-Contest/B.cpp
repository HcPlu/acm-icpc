#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

const int N = 1500005;

char c1[N], c2[N];

char c[N];
int a[N], b[N];
int front[N], tail[N];
int bel[N];

struct Seg {    
    int l, r, Max;
}tree[N << 2];

void build(int root, int l, int r) {
    tree[root].l = l;
    tree[root].r = r;
    tree[root].Max = 0;
    if(l == r) {
        tree[root].Max = front[l];
        bel[l] = root;
        return ;
    }
    int mid = l + r >> 1;
    build(root << 1, l, mid);
    build(root << 1 | 1, mid + 1, r);
    tree[root].Max = max(tree[root << 1].Max, tree[root << 1 | 1].Max);
    return ;
}

void solve(char *text, int length, int *next) { 
    int j = 0, k = 1;
    for (; j + 1 < length && text[j] == text[j + 1]; j++);
    next[0] = length - 1;
    next[1] = j;
    for (int i = 2; i < length; i++) {  
        int far = k + next[k] - 1;
        if(next[i - k] < far - i + 1) {
            next[i] = next[i - k];
        } else {
            j = max(far - i + 1, 0);
            for(; i + j < length && text[j] == text[i + j]; j++);
            next[i] = j;
            k = i;
        }
    }   
}

int find(int root, int limit) { 
    if(tree[root].l == tree[root].r) {
        return tree[root].l;
    }
    if(tree[root << 1 | 1].Max >= limit) {  
        return find(root << 1 | 1, limit);
    } else {
        return find(root << 1, limit);  
    }
}

void update(int root, int x) {
    if(tree[root].l == tree[root].r) {  
        tree[root].Max = 0;
        return ;
    }
    int mid = tree[root].l + tree[root].r >> 1;
    if(x <= mid) {
        update(root << 1, x);
    } else {
        update(root << 1 | 1, x);
    }
    tree[root].Max = max(tree[root << 1].Max, tree[root << 1 | 1].Max);
    return ;
}

int main() {
    scanf("%s", c1 + 1);
    scanf("%s", c2 + 1);
    int len1 = strlen(c1 + 1);
    int len2 = strlen(c2 + 1);
    if(len2 > len1) {
        puts("-1");
        return 0;
    }
    int len = 0;
    for(int i = 1; i <= len2; i++)
        c[len++] = c2[i];
    c[len++] = '$';
    for(int i = 1; i <= len1; i++) 
        c[len++] = c1[i];
    for(int i = 1; i <= len1; i++) 
        c[len++] = c1[i];
    solve(c, len, a);   
    len = 0;
    for(int i = len2; i >= 1; i--)
        c[len++] = c2[i];
    c[len++] = '$';
    for(int i = len1; i >= 1; i--)
        c[len++] = c1[i];
    for(int i = len1; i >= 1; i--) 
        c[len++] = c1[i];
    solve(c, len, b);
    for(int i = 0; i < len1 * 2; i++) {
        front[i + 1] = a[i + len2 + 1];  
    }
    for(int i = 0; i < len1 * 2; i++) { 
        tail[i + 1] = b[i + len2 + 1];
    }
    reverse(tail + 1, tail + 1 + len1 * 2);
    
    build(1, 1, len1 * 2);

    int ans = -1;
    for(int i = 1; i <= len1 * 2; i++) {    
        
        if(tail[i] == 0) {  
            continue;
        }
        if(tail[i] == len2) {   
            ans = len1;
            break;
        }
        int L = i - tail[i] + 1;
        int res = tail[i];
        res = len2 - res; 
        int R = L + len1 - 1;
        R = R - res + 1;
        int root = bel[R];
        int id = -1;
    

        update(1, i);
        
        while(root) {   
            int temp = root >> 1;
            if((temp << 1 | 1) == root && tree[temp << 1].Max >= res) {
                id = temp << 1;
                break;
            }
            root >>= 1;
        }
        
        if(tree[bel[R]].Max >= res) {   
            id = bel[R];
        }
        
        if(id != -1) {
            int t = find(id, res);
            ans = max(ans, t + res - L);
        }
    }
    printf("%d\n", ans);
    return 0;
}
