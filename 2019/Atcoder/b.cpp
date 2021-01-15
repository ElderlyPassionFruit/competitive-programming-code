#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n, m;
void read() {
	cin >> n >> m;
}

set<vector<int> > make(vector<int> have) {
	set <vector<int> > ans;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				continue;
			have[i] += 2;
			have[j] += 1;
			ans.insert(have);
			have[i] -= 2;
			have[j] -= 1;
		}
	}
	return ans;
}

void merge(set <vector<int> > & a, set <vector<int> > b) {
	for (auto i : b) {
		a.insert(i);
	}
}

set<vector<int> > make(set<vector<int> > have) {
	set <vector<int> > ans;
	for (auto i : have) {
		merge(ans, make(i));
	}
	return ans;
}

void run() {
	vector<int> start(n, 0);
	set <vector<int> > have;
	have.insert(start);
	for (int i = 0; i < m; i++) {
		have = make(have);
		cout << "i = " << i << " ";
		cout << "have.size() = " << have.size() << endl;
	}
}

void write() {

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