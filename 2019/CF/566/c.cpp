#include <bits/stdc++.h>

using namespace std;
#define int long long

set <char> good = {'a', 'e', 'o', 'i', 'u'};

int n;

int cnt(string s) {
	int ans = 0;
	for (auto i : s)
		ans += good.count(i);
	return ans;
}

char last(string s) {
	reverse(s.begin(), s.end());
	for (auto i : s) {
		if (good.count(i))
			return i;
	}
}

multiset<string> help1;
map <pair <int, char>, vector<string> > help2;


void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int c = cnt(s);
		int l = last(s);
		help1.insert(s);
		help2[{c, l}].push_back(s);
	}
}

vector<pair <string, string> > ans;

multiset <pair <string, string> > good_pairs, help_good_pairs;

map <int, vector<string> > fout;

void run() {
	for (auto i : help2) {
		for (int j = 0; j < i.second.size() - 1; j += 2) {
			good_pairs.insert({i.second[j], i.second[j + 1]});
		}
	}

	/*cout << endl;

	cout << "good_pairs = " << endl;
	for (auto i : good_pairs) {
		cout << i.first << " " << i.second << endl;
	}

	cout << endl;*/

	for (auto i : good_pairs) {
		help1.erase(help1.find(i.first));
		help1.erase(help1.find(i.second));
	}

	for (auto i : help1) {
		int c = cnt(i);
		fout[c].push_back(i);
	}

	/*cout << "fout = " << endl;
	for (auto i : fout) {
		cout << i.first << endl;
		for (auto j : i.second)
			cout << j << " ";
		cout << endl;
	}*/

	for (auto i : fout) {
		for (int j = 0; j < i.second.size() - 1; j += 2) {
			help_good_pairs.insert({i.second[j], i.second[j + 1]});
		}
	}

	/*cout << endl;
	cout << "help_good_pairs = " << endl;
	for (auto i : help_good_pairs) {
		cout << i.first << " " << i.second << endl;
	}

	cout << endl;*/

	while (!good_pairs.empty()) {
		auto h = *good_pairs.begin();
		good_pairs.erase(good_pairs.begin());

		if (!help_good_pairs.empty()) {
			auto w = *help_good_pairs.begin();
			help_good_pairs.erase(help_good_pairs.begin());
			ans.push_back({w.first, h.first});
			ans.push_back({w.second, h.second});
			continue;
		}
		else {
			if (!good_pairs.empty()) {
				auto w = * good_pairs.begin();
				good_pairs.erase(good_pairs.begin());
				ans.push_back({w.first, h.first});
				ans.push_back({w.second, h.second});
				continue;
			}
		}
		break;
	}
}

void write() {
	cout << ans.size() / 2 << endl;
	for (auto i : ans)
		cout << i.first << " " << i.second << endl;
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