#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a, b;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	b.resize(n);
	for (auto &i : b)
		cin >> i;
}


vector<int> z_function(vector<int> s) {
	int n = s.size();
	vector<int> z(n, 0);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (r >= i)
			z[i] = min(z[i - l], r - i + 1);
		while (z[i] + i < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		} 
	}
	return z;
}	

vector<int> ans;

int gen_lcp(vector<int> a, vector<int> b) {
	reverse(all(b));
	//reverse(all(a));
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) return ans;
		ans++;
	}
	return ans;
}
vector<int> checkL;
vector<int> checkR;
int lcp;

bool check(int k) {
	int len_pref = n + 1 - k;
	if (checkL[len_pref - 1] != len_pref) return false;
	//cout << k << endl;
	int x = (n + k) % 2;
	//cout << "x = " << x << endl;
	if (!x) {
		return lcp >= k - 1;
	}
	else {
		int len_suff = n - len_pref;
		if (!len_suff) return true;
		//cout << "len_suff = " << len_suff << endl;
		return checkR[len_suff - 1] == len_suff;
	}
}

void run() {
	lcp = gen_lcp(a, b);
	
	for (auto i : b)
		checkL.push_back(i);
	checkL.push_back(0);
	for (auto i : a)
		checkL.push_back(i);
	/*cout << "checkL = " << endl;
	for (auto i : checkL)
		cout << i << " ";
	cout << endl;*/

	checkL = z_function(checkL);
	/*cout << "checkL = " << endl;
	for (auto i : checkL)
		cout << i << " ";
	cout << endl;*/

	reverse(all(checkL));

	for (auto i : a)
		checkR.push_back(i);
	checkR.push_back(0);
	for (auto i : b)
		checkR.push_back(i);
	/*cout << "checkR = " << endl;
	for (auto i : checkR)
		cout << i << " ";
	cout << endl;*/

	checkR = z_function(checkR);
	/*cout << "checkR = " << endl;
	for (auto i : checkR)
		cout << i << " ";
	cout << endl;*/
	reverse(all(checkR));
	//cout << "lcp = " << lcp << endl;
	//cout << endl;

	for (int i = 1; i <= n; i++) {
		if (check(i)) {
			ans.push_back(i);
		}
	} 
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i << " ";
	cout << "\n";
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