#include <bits/stdc++.h>

using namespace std;

unordered_map <string, int> a, b;
vector <int> s, t;

void read() {
	string x;
	int cnt;
	cnt = 0;
	while (true) {
		cin >> x;
		if (x == "$")
			break;
		if (!a.count(x))
			a[x] = cnt++;
		s.push_back(a[x]);
	}

	cnt = 0;
	while (true) {
		cin >> x;
		if (x == "$")
			break;
		if (!b.count(x))
			b[x] = cnt++;
		t.push_back(b[x]);
	}
}

int get(int s_i, int p_i) {
	if (s_i <= p_i)
		return s_i;
	return -1;
}

vector <int> prefix_function (vector <int> s) {
	int n = (int) s.size();
	vector <int> p(n);
	for (int i = 1; i < n; i++) {
		int j = p[i - 1];
		while (j > 0 && get(s[i], p[j]) != get(s[j], p[j])){
			j = p[j - 1];
		}
		if (get(s[i], p[j]) == get(s[j], p[j]))
			j++;
		p[i] = j;
	}
	return p;
}

int ans;
void run() {
	vector <int> help;
	for (auto i : t)
		help.push_back(i);
	help.push_back(-1);

	for (auto i : s)
		help.push_back(i);
	vector <int> last(help.size(), -1);
	vector <int> help_pos(help.size(), -1);

	for (int i = 0; i < help.size(); i++) {
		if (i == t.size()){
			help_pos[i] = -10;
			last.assign(help.size(), -1);
			continue;
		}
		if (last[help[i]] != -1)
			help_pos[i] = i - last[help[i]];
		last[help[i]] = i;
	}

	vector <int> prefix = prefix_function(help_pos);

	for (int i = 0; i < help.size(); i++) {
		if (prefix[i] == t.size()) {
			ans = i - t.size() * 2 + 1;
			return;
		}
	}
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