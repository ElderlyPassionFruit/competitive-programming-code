#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<pair <int, int> > a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first >> i.second;
}

vector<pair <int, int> > ans;

void run() {
	vector<vector<int> > pos(n + 10);
	for (int i = 0; i < n; i++) {
		pos[a[i].first].push_back(a[i].second);
	}

	set<pair <int, int> > help;
	
	vector<int> max_num(n + 10);
	
	set<int> used;
	
	for (int i = n - 1; i >= 0; i--) {
		if (!used.count(a[i].first)) {
			help.insert({a[i].second, a[i].first});
			max_num[a[i].first] = a[i].second;
			used.insert(a[i].first);
		}
	}

	int q;
	cin >> q;
	for (int test = 0; test < q; test++) {
		int k;
		cin >> k;
		vector<int> nums(k);
		for (auto &i : nums)
			cin >> i;
		for (auto i : nums) {
			help.erase({max_num[i], i});
		}

		if (help.size() == 0) {
			ans.push_back({0, 0});
		}
		if (help.size() == 1) {
			if (pos[help.begin()->second].empty())
				ans.push_back({0, 0});
			else
				ans.push_back({pos[help.begin()->second][0], help.begin()->second});
		}
		if (help.size() >= 2) {
			auto it1 = --help.end();
			auto it2 = it1;
			it2--;
			int x = it2->first;
			auto fans = lower_bound(pos[it1->second].begin(), pos[it1->second].end(), x);
			if (fans == pos[it1->second].end())
				ans.push_back({0, 0});
			else
				ans.push_back({*fans, it1->second});
		}

		for (auto i : nums) {
			help.insert({max_num[i], i});
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i.second << " " << i.first << "\n";
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