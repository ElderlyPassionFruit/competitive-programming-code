#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
string t;
int n, m;
void read() {
	cin >> s >> t;
	n = s.size();
	m = t.size();
}

const int MAXN = 26;

int cnt_s[MAXN], cnt_t[MAXN], cnt_q;
int cnt_ans[MAXN];

void run() {
	cnt_q = 0;
	for (auto i : s) {
		if (i == '?')
			cnt_q++;
		else
			cnt_s[i - 'a']++;
	}
	for (auto i : t) {
		cnt_t[i - 'a']++;
	}


	int can = 1e9;

	for (int i = 0; i < MAXN; i++) {
		if (cnt_t[i] > 0)
		chkmin(can, cnt_s[i] / cnt_t[i]);
	}

	for (int i = 0; i < MAXN; i++) {
		cnt_s[i] -= cnt_t[i] * can;
	}

	/*cout << "cnt_s = " << endl;
	for (int i = 0; i < MAXN; i++)
		cout << cnt_s[i] << " ";
	cout << endl; 

	cout << "cnt_t = " << endl;
	for (int i = 0; i < MAXN; i++)
		cout << cnt_t[i] << " ";
	cout << endl; 

	cout << cnt_q << endl; */
	
	for (int i = 0; i < cnt_q; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (cnt_s[j] < cnt_t[j]){
				cnt_ans[j]++;
				cnt_s[j]++;
				break;
			}
		}

		bool flag = true;
		for (int j = 0; j < MAXN; j++)
			flag &= (cnt_s[j] >= cnt_t[j]);
		//cout << "flag = " << flag << endl;
		if (flag) {
			for (int j = 0; j < MAXN; j++)
				cnt_s[j] -= cnt_t[j];
		}
	}

	/*cout << "ans = " << endl;
	for (int i = 0; i < MAXN; i++)
		cout << cnt_ans[i] << " ";
	cout << endl;*/
}

void write() {
	for (int i = 0; i < n; i++) {
		if (s[i] != '?')
			cout << s[i];
		else {
			for (int j = 0; j < MAXN; j++) {
				if (cnt_ans[j] != 0) {
					cout << (char)('a' + j);
					cnt_ans[j]--;
					break;
				}
			}
		}
	}
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