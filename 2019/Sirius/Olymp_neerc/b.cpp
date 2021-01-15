#include <bits/stdc++.h>

using namespace std;

//#define int long long
string s;
int n;
void read() {
	cin >> s;	
	n = s.length();
}
int l1, r1, l2, r2;
const int INF = 1e9;


bool check(int len) {
	int sum = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] == '1')
			sum++;
	}
	vector <int> fans(n + 1);
	fans[sum]++;
	for (int i = len; i < n; i++) {
		if (s[i] == '1')
			sum++;
		if (s[i - len] == '1')
			sum--;
		fans[sum]++;
	}
	for (int i = 0; i < n + 1; i++) {
		if (fans[i] >= 2) {
			return true;
		}
	}
	return false;
}

pair <int, int> check2(int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '1')
            sum++;
    }
    unordered_map <int, vector <int> > fans;
    fans[sum].push_back(0);
    for (int i = len; i < n; i++) {
        if (s[i] == '1')
            sum++;
        if (s[i - len] == '1')
            sum--;
        fans[sum].push_back(i - len + 1);
    }
    for (auto i : fans) {
        if (i.second.size() >= 2) {
            return {i.second[0], i.second[1]};
        }
    }
    return {INF, INF};
}

void run() {
	int l = 0, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	if (l == 0) {
		cout << -1 << endl;
		exit(0);
	}
	//cout << l << endl;
	auto p = check2(l);
	l1 = p.first;
	l2 = p.second;
	//cout << l1 << " " << l2 << endl;
	r1 = l + l1 - 1;
	r2 = l + l2 - 1; 
}

void write() {
	cout << l1 + 1 << " " << r1 + 1 << " " << l2 + 1 << " " << r2 + 1 << endl;
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