#include <bits/stdc++.h>

using namespace std;

bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.second > b.second || (a.second == b.second && a.first > b.first);
}


bool operator<(pair <int, int> a, pair <int, int> b) {
	return a.second > b.second || (a.second == b.second && a.first > b.first);
}

int n, m, k;
vector<pair<int,int> > help;
void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		help.push_back({a, b});
	}
}


bool check(pair <int, int> a, pair <int, int> b) {
	return a.first <= b.first && a.second <= b.second;
}

int ans = 0;
void run() {
	sort(help.begin(), help.end(), cmp);
	set <pair <int, int> > coords;
	for (auto i : help) {
		bool flag = false;
		pair <int, int> good = {-1, -1};
		for (auto j : coords) {
			if (check(i, j)){
				good = j;
				break;
			}
		}
		if (good != make_pair(-1, -1)) {
			coords.erase(good);
			coords.insert(i);
			flag = true;
		}
		if (flag) continue;
		coords.insert(i);
	}
	ans = coords.size();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}