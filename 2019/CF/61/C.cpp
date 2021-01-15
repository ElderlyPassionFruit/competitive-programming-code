#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, q;
vector < pair <int, int> > t;
void read() {
	cin >> n >> q;
	t.resize(q);
	for (int i = 0; i < q; i++) {
		cin >> t[i].first >> t[i].second;
	}
	sort(t.begin(), t.end());
}

const int MAXN = 5010;
int arr[MAXN];
int pref1[MAXN], pref2[MAXN];


void run() {
	map <int, int> help;

	for (int i = 0; i < q; i++) {
		help[t[i].first]++;
		help[t[i].second + 1]--;
	}
	int cnt = 0;
	int sum = 0;
	for (int i = 0; i < MAXN; i++) {
		cnt += help[i];
		arr[i] = cnt;
		if (arr[i] > 0)
			sum++;
	}
//	cout << "sum = " << sum << endl;
//	cout << "arr = " << endl;
//	for (int i = 1; i <= n; i++)
//		cout << arr[i] << " ";
//	cout << endl;
	for (int i = 1; i <= n; i++) {
		pref1[i] = pref1[i - 1];
		if (arr[i] == 1)
			pref1[i]++;
		pref2[i] = pref2[i - 1];
		if (arr[i] == 2)
			pref2[i]++;
	}
	int ans = 1e18;
	for (int i = 0; i < q; i++) {
		for (int j = i + 1; j < q; j++) {
			int l1, r1, l2, r2, l1_2 = -1, r1_2 = -1;
			l1 = t[i].first;
			r1 = t[i].second;
			l2 = t[j].first;
			r2 = t[j].second;
		//				cout << "help1" << endl;
		//	cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
		//	cout << l1_2 << " " << r1_2 << endl;
			int fans;
			if (l2 <= r1) {
				l1_2 = l2, r1_2 = r1;
				r1 = l1_2 - 1;
				l2 = r1_2 + 1;
				fans = 0;
				if (l1 <= r1)
					fans += pref1[r1] - pref1[l1 - 1];
				if (l2 <= r2)
					fans += pref1[r2] - pref1[l2 - 1];
				fans += pref2[r1_2] - pref2[l1_2 - 1];
			}
			else
			{
				fans = 0;
				if (l1 <= r1)
					fans += pref1[r1] - pref1[l1 - 1];
				if (l2 <= r2)
					fans += pref1[r2] - pref1[l2 - 1];
			}
		//	cout << "help2" << endl;
		//	cout << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
		//	cout << l1_2 << " " << r1_2 << endl;
		//	cout << fans << endl;
			ans = min(ans, fans);
		}
	}
	cout << sum - ans << endl;
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