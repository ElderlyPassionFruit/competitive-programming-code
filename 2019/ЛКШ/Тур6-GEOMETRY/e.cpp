#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

pair <int, int> query(int x1, int y1, int x2, int y2) {
	cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	pair <int, int> q;
	cin >> q.first >> q.second;
	return q;
}

void out(vector<pair <int, int> > ans) {
	cout << "Ready!\n";
	for (auto i : ans)
		cout << i.first << " " << i.second << "\n";
	cout.flush();
}

int L, R;

vector<pair <int, int> > ans;

pair <int, int> find(int l, int r, int pos) {
	pair <int, int> q;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		q = query(mid, pos, R, pos + 1);
		if (q.first == ans.size())
			l = mid;
		else
			r = mid;
	}
	return {l, pos};
}

void solve() {
	int n, MAXC;
	cin >> n >> MAXC;
	L = MAXC * (-4);
	R = MAXC * 4;

	int up = MAXC * 5;

	while (ans.size() < n) {
		int r = up, l = L;
		pair <int, int> q;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			q = query(L, mid, R, mid);
			if (q.first <= ans.size())
				r = mid;
			else
				l = mid;
		}

		q = query(L, r, R, r);
	
		if (q.first + q.second == n - 1) {
			pair <int, int> new_point = find(L, R, r);
			ans.push_back(new_point);
		}
		else {
			pair <int, int> new_point = find(L, R, r);
			ans.push_back(new_point);
			new_point = find(new_point.first + 1, R, r);
			ans.push_back(new_point);
		}

		up = r - 1;		
	}

	out(ans);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}