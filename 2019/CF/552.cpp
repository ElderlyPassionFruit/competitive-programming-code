#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, k;
vector <int> a;
void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
}
vector <int> ans;

void run() {
	ans.resize(n);
	set <pair <int, int> > have;
	set <pair <int, int> > num;
	for (int i = 0; i < n; i++) {
		have.insert({i, a[i]});
		num.insert({-a[i], i});
	}

	int now = -1;
	while (!have.empty() && !num.empty()) {
		cout << "have" << endl;
		for (auto i : have)
			cout << i.first << " " << i.second << endl;
			cout << endl;
		cout << "num" << endl;
		for (auto i : num)  {
			cout << i.first << " " << i.second << endl;
		} 
		cout << endl;
		now++;
		auto x = *num.begin();
		int pos = x.second;
		int val = -x.first;
		num.erase(num.begin());
		auto it = have.find({pos, val});
		int cnt = k;
		vector <pair <int, int> > fdel;

		while (cnt >= 0 && (it != have.end())) {
			auto x = *it;
			fdel.push_back(x);
			ans[x.second] = now % 2 + 1;
			cnt--;
			it++;
		}
	
		it = have.find({pos, val});
		cnt = k;
	
		while (cnt >= 0 && it != have.begin()) {
			auto x = *it;
			fdel.push_back(x);
			ans[x.second] = now % 2 + 1;
			cnt--;
			it--;
		}
	
		for (auto i : fdel) {
			have.erase(i);
			num.erase({-i.second, i.first});
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i;
	cout << endl;
	cout << "good" << endl;
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