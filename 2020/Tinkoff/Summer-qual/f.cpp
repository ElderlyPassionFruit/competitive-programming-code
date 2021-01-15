#include <bits/stdc++.h>

using namespace std;

vector<int> month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

string make(int x) {
	if (x < 10) {
		string ans = " ";
		ans += '0' + x;
		return ans;
	}
	string ans = "";
	ans += x / 10 + '0';
	ans += x % 10 + '0';
	return ans;
}

vector<vector<string> > make(int pos, int cnt) {
	vector<vector<string> > ans(7, vector<string> ((cnt + 6 + pos) / 7, "  "));
	int pos_x = pos;
	int pos_y = 0;
	for (int i = 1; i <= cnt; i++) {
		ans[pos_x][pos_y] = make(i);
		pos_x++;
		if (pos_x == 7) {
			pos_x = 0;
			pos_y++;
		}
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<vector<vector<string> > > ans(12);
	int d, flag, x;
	cin >> d >> flag >> x;
	d--;
	month[1] += flag;
	for (int i = 0; i < 12; i++) {
		ans[i] = make(d, month[i]);
		d += month[i];
		d %= 7;
	}

	vector<int> len(x, 0);
	for (int i = 0; i < x; i++) {
		for (int j = i; j < 12; j += x) {
			len[i] = max(len[i], (int)ans[j][0].size());
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 7; j++) {
			while (ans[i][j].size() < len[i % x]) {
				ans[i][j].push_back("  ");
			}
		}
	}

	for (int i = 0; i < 12 / x; i++) {
		int len = 0;
		for (int pos = 0; pos < 7; pos++) {
			for (int j = i * x; j < (i + 1) * x; j++) {
				for (int k = 0; k < ans[j][pos].size(); k++) {
					cout << ans[j][pos][k];
					len+=2;
					if (k != ans[j][pos].size() - 1)
						cout << " ", len++;
				}
				if (j != (i + 1) * x - 1)
					cout << "   ", len += 3;
			}
			cout << endl;
		}
		len /= 7;
		if (i != 12 / x - 1) {
			while (len--)
				cout << " ";
			cout << endl;
		}
	}
	return 0;
}