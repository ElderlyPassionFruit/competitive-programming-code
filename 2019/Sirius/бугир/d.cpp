#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, k;
vector <pair <int, int> > a;
void read() {
	cin >> n >> k;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end());
}

vector <int> get(int pos1) {
	deque <int> fans;
	if (pos1 == -1)
		return {};
	int sz = 0;
	int s = pos1 - 1, f = n;
	for (int i = pos1; i < n; i++) {
		if (a[i].first != a[pos1].first){
			f = i;
			break;
		}
		fans.push_back(i);
		sz++;
	}
	while (true) {
		bool flag = true;
		if (s >= 0) {
			fans.push_front(s);
			if (a[fans[(fans.size() + 1) / 2 - 1]].first == a[pos1].first) {
				flag = false;
				s--;
				sz++;
			}
			else {
				fans.pop_front();
			}
		}
		if (f < n) {
			fans.push_back(f);
			if (a[fans[(fans.size() + 1) / 2 - 1]].first == a[pos1].first) {
				flag = false;
				f++;
				sz++;
			} 
			else {
				fans.pop_back();
			}
		}
		if (flag)
			break;
	}
	vector <int> freturn;
	for (int i = 0; i < sz; i++) {
		freturn.push_back(a[fans[i]].second);
	}
	return freturn;
}


vector <int> ans;
void run() {
	int mod1 = 1e18, pos1 = 0;
	int mod2 = 1e18, pos2 = -1;
	for (int i = 0; i < n; i++) {
		int fmod = abs(a[i].first - k);
		if (fmod < mod1) {
			mod1 = fmod;
			pos1 = i;
		}
	}
	for (int i = 0; i < n; i++) {
		int fmod = abs(a[i].first - k);
		if (fmod == mod1 && a[i].first != a[pos1].first) {
			mod2 = fmod;
			pos2 = i;
			break;
		}
	}
	vector<int> fans1 = get(pos1);
	vector<int> fans2 = get(pos2);
	if (fans1.size() > fans2.size())
		ans = fans1;
	else 
		ans = fans2;
}

void write() {
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << endl;
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