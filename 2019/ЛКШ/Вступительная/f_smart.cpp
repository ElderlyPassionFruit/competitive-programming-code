#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

vector <int> a;
int n;
vector <int> pref, suff;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	sort(a.begin(), a.end());
}

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
	pref.resize(n, 0);
	suff.resize(n, 0);
	for (int i = 1; i < n; i++) {
		pref[i] = max(pref[i - 1] + 1, a[i] - a[i - 1] + 1);
		int j = i + 1;
		while (j < n && a[j] - a[i] <= pref[i] + 1) {
			pref[j] = pref[i] + 1;
			j++;
		}
		j--;
		i = j;
	}

	for (int i = n - 2; i >= 0; i--) {
		suff[i] = max(suff[i + 1] + 1, a[i + 1] - a[i] + 1);
		int j = i - 1;
		while (j >= 0 && a[i] - a[j] <= suff[i] + 1) {
			suff[j] = suff[i] + 1;
			j--;
		}
		j++;
		i = j;
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