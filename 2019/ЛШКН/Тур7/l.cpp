#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n;
void read() {
	cin >> n;
}

const int MAXN = 3e5 + 10;

int t[MAXN];
int ans = 0;
void run() {
	int need = 1;
	int last_add = 0;
	int last_shuffle = 0;
	vector<int> st;
	for (int i = 1; i <= 2 * n; i++) {
		string type;
		cin >> type;
		if (type == "add") {
			int x;
			cin >> x;
			t[x] = i;
			last_add = i;
			st.push_back(i);
		}
		else {
			if (last_add > last_shuffle && last_add > t[need]) {
				last_shuffle = i;
				ans++;
			}
			else {
				if (last_add == t[need]) {
					st.pop_back();
					last_add = 0;
					if (!st.empty())
						last_add = st.back();
				}
			}
			need++;
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