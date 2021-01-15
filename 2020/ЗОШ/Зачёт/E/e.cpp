#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<string> make(string s) {
	string now = "";
	vector<string> ans;
	for (auto i : s) {
		if (i == ' ') {
			ans.push_back(now);
			now = "";
			continue;
		}
		now += i;
	}
	if (now != "")
		ans.push_back(now);
	return ans;
}

bool check_function(string s) {
	return make(s).size() == 3;
}

bool check_trow(string s) {
	return s == "throw";
}

bool check_name(string s) {
	return s.back() == ')';
}

bool check_type(string s) {
	return make(s).size() == 2;
}

map<string, vector<string> > g;

void build() {
	string s;
	string now = "";
	while(getline(cin, s)) {
		if (check_function(s)) {
			now = make(s)[1];
			continue;
		}
		if (s == "}") continue;
		g[now].push_back(s);
	}
}

bool dfs(string v) {
	vector<string> have;
	for (auto i : g[v]) {
		if (g.count(i)) {
			if (dfs(i)) {
				while (!have.empty()){
					cout << "~" << have.back() << "()" << "\n";
					have.pop_back();
				}
				return 1;
			}
		}
		if (check_trow(i)) {
			cout << "throw" << "\n";
			while (!have.empty()){
				cout << "~" << have.back() << "()" << "\n";
				have.pop_back();
			}
			return 1;	
		}
		if (check_type(i)) {
			cout << make(i)[0] << "()" << "\n";
			have.push_back(make(i)[0]);
		}
	}
	while (!have.empty()){
		cout << "~" << have.back() << "()" << "\n";
		have.pop_back();
	}

	return 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	/*cout << "g = " << endl;
	for (auto i : g) {
		cout << "v = " << i.first << endl;
		for (auto j : i.second) {
			cout << j << " | ";
		}
		cout << endl;
	}*/
	dfs("main()");
	return 0;
}










