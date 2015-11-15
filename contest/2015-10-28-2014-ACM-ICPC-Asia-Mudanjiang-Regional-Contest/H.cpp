#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <map>

using namespace std;

const int N = 111111;

string text, buffer;
pair<int, int> pos[N];
map<string, int> child[N];
int size;

__inline int match(const string &text, int pos, char a, char b) {
	int count = 0;
	for (; pos < (int)text.length(); pos++) {
		if (text[pos] == a) {
			count++;
		} else if (text[pos] == b) {
			count--;
		}
		if (count == 0) {
			return pos;
		}
	}
	return (int)text.length();
}

__inline int match(const string &text, int pos, char a) {
	for (; pos < (int)text.length(); pos++) {
		if (text[pos] == a) {
			return pos;
		}
	}
	return (int)text.length();
}

__inline string get(const string &text, int l, int r) {
	return text.substr(l, r - l + 1);
}

int dfs(int l, int r) {
	if (r - l + 1 < 2) {
		return 0;
	}

	int x = ++size;
	pos[x] = make_pair(l, r);
	child[x].clear();
	
	if (text[l] == '"' && text[r] == '"') {
		return x;
	}
	
	l++;
	r--;

	for (; l <= r; ) {
		l = match(text, l, '"');
		if (l >= (int)text.length()) {
			break;
		}
		
		int find = match(text, l + 1, '"');
		string str = get(text, l, find);

		find = min(match(text, find + 1, '"'), match(text, find + 1, '{'));
		if (find >= (int)text.length()) {
			break;
		}
		
		if (text[find] == '"') {
			l = match(text, find + 1, '"');
		} else {
			l = match(text, find, '{', '}');
		}
		child[x][str] = dfs(find, l);
		l++;
	}
	return x;
}

void solve(void) {
	cin >> text;
	
	size = 0;
	int root = dfs(0, (int)text.length() - 1);

	int q;
	for (cin >> q; q--; ) {
		cin >> buffer;
		
		bool error = false;
		int now = root;
		
		int length = (int)buffer.length();
		for (int i = 0; i < length; ) {
			int mat = match(buffer, i + 1, '"');
			string str = get(buffer, i, mat);
			if (child[now].count(str) == 0) {
				error = true;
				break;
			}
			now = child[now][str];
			if (now == 0) {
				error = true;
				break;
			}
			i = mat + 2;
		}
		
		
		if (error) {
			cout << "Error!" << endl;
		} else {
			cout << get(text, pos[now].first, pos[now].second) << endl;
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	int tests;
	for (cin >> tests; tests--; solve());
}
