#include <bits/stdc++.h>

using namespace std;
#define int long long

void wr(int num, string s) {
	cout << "Case #" << num << ": " << s << endl;  	
	char ans;
	cin >> ans;
	if (ans == 'N') {
		exit(0);
	}
}

int rnd() {
	return (rand() << 16) + rand();
}

bool check(vector <char> a, vector <char> b) {
	for (int i = 0; i < 5; i++) {
		if (a[i] == '.')
			continue;
		if (a[i] != b[i])
			return false;
	}
	return true;
}

int to_int(vector <char> s) {
	//reverse(s.begin(), s.end());
	int ans = 0;
	for (int i = 0; i < s.size(); i++) {
		ans *= 10;
		ans += s[i] - 'A' + 1;
	}
	return ans;
}

string to_str(int a) {
	string ans = "";
	while (a) {
		ans += 'A' + a % 10 - 1;
		a /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

bool check(int a) {
	set <int> nums;
	while (a) {
		if (a % 10 < 1 || a % 10 > 5)
			return false;
		if (nums.count(a % 10)) return false;
		nums.insert(a % 10);
		a /= 10;
	}
	return true;
}

void solve(int num, int f) {
	vector <vector <char> > s;
	vector <char> x = {'A', 'B', 'C', 'D', 'E'};
	do {
		s.push_back(x);
	} while (next_permutation(x.begin(), x.end()));
	
	vector <vector <char> > help(119, vector <char> (5, '.'));
	set <int> used;
	int mx_num = 595;
	for (int i = 0; i < f; i++) {
		int fout = rnd() % mx_num;
		while (used.count(fout)) {
			fout = rnd() % mx_num;
		}
		used.insert(fout);
		cout << fout + 1 << endl;
		char fans;
		cin >> fans;
		help[fout / 5][fout % 5] = fans;
	}
	map <vector <char>, int> help2;
	for (auto i : help) {
		help2[i]++;
	}

	used.clear();
	for (auto i : help2) {
		for (auto j : s) {
			if (check(i.first, j)) {
				used.insert(to_int(j));			
			}
		}
	}

	for (int i = 12345; i < 1e6; i++) {
		if (!check(i)) continue;
		if (used.count(i)) continue;
		wr(num, to_str(i));
		return;
	}
}	

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	/*while (true) {
		string t;
		cin >> t;
		vector <char> s;
		for (auto i : t)
			s.push_back(i);
		cout << to_int(s) << " " << to_str(to_int(s)) << endl;
	}*/
	int t, f;
	cin >> t >> f;
	for (int i = 1; i <= t; i++) {
		solve(i, f);
	}
	return 0;
}