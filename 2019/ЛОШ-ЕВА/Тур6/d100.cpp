#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

const int MAXN = 1e5 + 10;

string s;
int l;
int n, q;
vector<long long> ans;
vector<int> len;

const int MOD1 = 1e9 + 7;
const int MOD2 = 998244353;

const int b1 = 31;
const int b2 = 47;

int pows1[MAXN], pows2[MAXN], h1[MAXN], h2[MAXN];

int get_hash1(string &s) {
	int ans = 0;
	int n = s.size();
	for (int i = 1; i <= n; i++) 
		ans = ((long long)ans + ((long long)s[i - 1] - 'a' + 1) * pows1[i]) % MOD1;
	return (long long)ans * pows1[l - n] % MOD1;
}

int get_hash2(string &s) {
	int ans = 0;
	int n = s.size();
	for (int i = 1; i <= n; i++)
		ans = ((long long)ans + ((long long)s[i - 1] - 'a' + 1) * pows2[i]) % MOD2;
	return (long long)ans * pows2[l - n] % MOD2;
}

int get_hash1(int l1, int r1) {
	return (((long long)h1[r1] - h1[l1 - 1]) + MOD1) * (long long)pows1[l - r1] % MOD1;
}

int get_hash2(int l2, int r2) {
	return (((long long)h2[r2] - h2[l2 - 1]) + MOD2) * (long long)pows2[l - r2] % MOD2;
}

void make_hashs() {
	pows1[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pows1[i] = (long long)pows1[i - 1] * b1 % MOD1;

	h1[0] = 0;
	for (int i = 1; i <= l; i++)
		h1[i] = ((long long)h1[i - 1] + ((long long)s[i - 1] - 'a' + 1) * pows1[i]) % MOD1;

	pows2[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pows2[i] = (long long)pows2[i - 1] * b2 % MOD2;

	h2[0] = 0;
	for (int i = 1; i <= l; i++)
		h2[i] = ((long long)h2[i - 1] + ((long long)s[i - 1] - 'a' + 1) * pows2[i]) % MOD2;
}

bool cmp(string & a, string & b) {
	return a.length() < b.length();
}

vector<string> str;
vector<pair <int, int> > fq;
void read() {
	cin >> s;
	l = s.size();
	make_hashs();
	cin >> n;
	set<int> help_len;
	for (int i = 0; i < n; i++) {
		string x;
		cin >> x;
		if (x.length() > l) continue;
		str.push_back(x);
		help_len.insert((int)x.length());
	}

	sort(str.begin(), str.end(), cmp);
	
	for (auto i : help_len) {
		len.push_back(i);
	}

	cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		fq.push_back({l, r});
	}
}

int pref[MAXN];

int get_ans(int len, int r1, int l1) {
	if (r1 - len + 1 < l1) return 0;
	return pref[r1 - len + 1] - pref[l1 - 1]; 
}	

void run() {
	ans.resize(q);
	int pos = 0;
	for (auto i : len) {
		cc_hash_table<int, int> hashs1;
		cc_hash_table<int, int> hashs2;

		while (pos < n && str[pos].length() == i) {
			hashs1[get_hash1(str[pos])] = 1;
			hashs2[get_hash2(str[pos])] = 1;
			pos++;
		}

		for (int j = 1; j + i - 1 <= l; j++) {
			pref[j] = pref[j - 1];
			if (hashs1.find(get_hash1(j, i + j - 1)) != hashs1.end() && hashs2.find(get_hash2(j, i + j - 1)) != hashs2.end())
				pref[j]++;
		}

		for (int j = 0; j < q; j++) {
			ans[j] = ans[j] + get_ans(i, fq[j].second, fq[j].first);
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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