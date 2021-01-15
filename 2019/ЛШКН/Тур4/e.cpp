#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n, k;
void read() {
	cin >> n >> k;
}

vector<string> words;

void run() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			string s = "";
			s += 'A' + i;
			s += 'a' + j;
			words.push_back(s);
		}
	}

	vector<string> ans;

	for (int i = 0; i < k - 1; i++) {
		ans.push_back(words[i]);
	}


	int pos = k - 1;
	for (int i = 0; i < n - k + 1; i++) {
		string type;
		cin >> type;
		if (type == "YES") {
			ans.push_back(words[pos++]);
		}
		else {
			ans.push_back(ans[i]);
		}
	}
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	return 0;
}