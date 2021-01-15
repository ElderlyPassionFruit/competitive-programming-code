#include <bits/stdc++.h>

using namespace std;
#define int long long

int n;
vector <int> a;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	sort(a.begin(), a.end());
}

vector <int> pref, suff;

void wr() {
	cout << "a = " << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	cout << "pref = " << endl;
	for (auto i : pref)
		cout << i << " ";
	cout << endl;
	cout << "suff = " << endl;
	for (auto i : suff) 
		cout << i << " ";
	cout << endl;
}

void run() {
	pref.assign(n, 1e9);
	suff.assign(n, 1e9);
	pref[0] = 0;
	suff[n - 1] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			pref[i] = min(pref[i], max(pref[j] + 1, a[i] - a[j] + 1));
		}
	}

	for (int i = n - 2; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			suff[i] = min(suff[i], max(suff[j] + 1, a[j] - a[i] + 1));
		}
	}
	wr();
}

void write() {

}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}