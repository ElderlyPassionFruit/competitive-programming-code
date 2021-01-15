#include <bits/stdc++.h>

using namespace std;
#define int long long

struct event {
	int type;
	string code;
	int reliability;
	int n;
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> q;
	vector <event> help;
	for (int test = 0; test < q; test++) {
		string type;
		cin >> type;
		event add;
		if (type == "ISSUE") {
			string code;
			cin >> code;
			add.type = 1;
			add.code = code;
		}
		else if (type == "DELETE") {
			string code;
			cin >> code;
			add.type = 2;
			add.code = code;
		}
		else if (type == "RELIABILITY") {
			string code;
			int reliability;
			cin >> code;
			cin >> reliability;
			add.type = 3;
			add.code = code;
			add.reliability = reliability;
		}
		else if (type == "FIND") {
			int n;
			cin >> n;
			add.type = 4;
			add.n = n;
		}
		help.push_back(add);
	}
	vector <pair <int, int> > pos;
	map <int, pair <int, int> > have;
	map <int, string> id_code;
	set <string> find;
	int id = 0;
	for (int test = 0; test < q; test++) {
		auto x = help[test];
		if (x.type == 1) {
			if (find.find(x.code) == find.end()) {
				have[x.code] = make_pair(0, id);
				id_code[id] = x.code;
				find.insert(x.code);
				pos.push_back(have[x.code]);
				id++;
			}
		} 
		else if (x.type == 2) {
			find.erase(x.code);
		}
		else if (x.type == 3) {
			if (find.find(x.code) != find.end()) {
				have[x.code] = make_pair(x.reliability, have[x.code].second);
				pos.push_back(have[x.code]);
			}
		}
	}

	sort(pos.begin(), pos.end());
	vector <int> fans(pos.size());
	
	have.clear();
	find.clear();
	id = 0;
	for (int test = 0; test < q; test++) {
		auto x = help[test];
		if (x.type == 1) {
			if (find.find(x.code) == find.end()) {
				have[x.code] = make_pair(0, id);
				cout << "CREATED " << id << " " << 0 << endl;
				find.insert(x.code); 
			}
			else { 
				cout << "EXISTS " << have[x.code].second << " " << have[x.code].first << endl; 
			}
		}
		else if (x.type == 2) {
			if (find.find(x.code) == find.end()) {
				cout << "BAD REQUEST" << endl;
			}
			else {
				cout << "OK " << have[x.code].second << " " << have[x.code].first << endl;
				find.erase(x.code);
			}
		}
		else if (x.type == 3) {
			if (find.find(x.code) == find.end()) {
				cout << "BAD REQUEST" << endl;
			}
			else {

			}
		}
		else if (x.type == 4) {

		}
	}

	return 0;
}