#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
int n;
vector <int> a;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		//x *= 2;
		a.push_back(x);
	}
	sort(a.begin(), a.end());
}

vector <int> pref, suff;

void make() {
	pref.assign(n, 1e9);
	suff.assign(n, 1e9);
	pref[0] = 0;
	suff[n - 1] = 0;
	for (int i = 1; i < n; i++) {
		pref[i] = min(pref[i], max(pref[i - 1] + 1, a[i] - a[i - 1] + 1));
		int j = i + 1;
		while (j < n && a[j] - a[i] <= pref[i]) {
			pref[j] = pref[i] + 1;
			j++;
		}
		j--;
		j--;
		i = max(j, i);
		/*for (int j = 0; j < i; j++) {
			pref[i] = min(pref[i], max(pref[j] + 1, a[i] - a[j] + 1));
			if (pref[i] == pref[i - 1])
				break;
		}*/
	}

	for (int i = n - 2; i >= 0; i--) {
		suff[i] = min(suff[i], max(suff[i + 1] + 1, a[i + 1] - a[i] + 1));
		int j = i - 1;
		while (j >= 0 && a[i] - a[j] <= suff[i]) {
			suff[j] = suff[i] + 1;
			j--;
		}
		j++;
		j++;
		i = min(i, j);
		/*for (int j = i + 1; j < n; j++) {
			suff[i] = min(suff[i], max(suff[j] + 1, a[j] - a[i] + 1));
			if (suff[i] == suff[i + 1])
				break;
		}*/
	}

}

bool check(double r) {
	for (int i = 0; i < n; i++) {
		int pos = (--upper_bound(a.begin(), a.end(), (a[i] + 2 * r))) - a.begin();
		int fans = max(pref[i], suff[pos]);
		//cout << "i = " << i << " pos = " << pos << " r = " << r << " fans = " << fans << endl;
		if (fans <= r)
			return true;
	}
	return false;
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
double ans;
void binary_search(){
	int l = 0, r = 1e10 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	//cout << "l = " << l << " r = " << r << endl;
//	cout << check(l) << " " << check(l + 0.5) << " " << check(r) << endl;
	for (double i = l; i <= r; i += 0.5)
		if (check(i)){
			ans = i;
			break;
		}
}


void run() {
	make();
	//wr();
	binary_search();
	//cout << check(3.0) << endl;
}

void write() {
	//cout << "ans = " << ans << endl;
	//double fans = ans / 2.0;
	cout << fixed << setprecision(1) << ans << endl;
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}