#include <bits/stdc++.h>

using namespace std;
#define int long long

void wr(int num, int s) {
	cout << "Case #" << num << ": " << s << endl;  	
}

bool make(int x, int y, int r, int c, vector <vector <char> > & help, char type) {
	vector <vector <char > > fhelp = help;
	if (type == 'H') {
		if (fhelp[x][y] != '.')
			return false;
		fhelp[x][y] = 'H';
		for (int i = x + 1; i < r; i++) {
			if (fhelp[i][y] == '#')
				return false;
			if (fhelp[i][y] != '.')
				break;
			fhelp[i][y] = 'H';
		}
		for (int i = x - 1; i >= 0; i--) {
			if (fhelp[i][y] == '#')
				return false;
			if (fhelp[i][y] != '.')
				break;
			fhelp[i][y] = 'H';	
		}
		help = fhelp;
		return true;
	}
	if (type == 'V') {
		if (fhelp[x][y] != '.')
			return false;
		fhelp[x][y] = 'V';
		for (int i = y + 1; i < c; i++) {
			if (fhelp[x][i] == '#')
				return false;
			if (fhelp[x][i] != '.')
				break;
			fhelp[x][i] = 'V';
		}
		for (int i = y - 1; i >= 0; i--) {
			if (fhelp[x][i] == '#')
				return false;
			if (fhelp[x][i] != '.')
				break;
			fhelp[x][i] = 'V';
		}
		help = fhelp;
		return true;
	}
	return true;
}

vector <char> types = {'H', 'V'};

void wr(vector <vector <char > > help) {
	cout << "help = " << endl;
	for (auto i : help) {
		for (auto j : i) {
			cout << j;
		}
		cout << endl;
	}
	cout << endl;
}
	
bool check(int x, int y, int r, int c, vector <vector <char > > help, char type) {
	bool flag = make(x, y, r, c, help, type); 
	if (!flag)
		return false;

//	wr(help);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (auto t : types) {
				if (check(i, j, r, c, help, t)) {
					return false;
				}
			}		
		}
	}

	return true;
}

void solve(int num) {
	int r, c;
	cin >> r >> c;
	vector <vector <char> > help(r, vector <char> (c, '#'));
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			cin >> help[i][j];
	int ans = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (auto t : types) {
			//	cout << "start = " << i << " " << j << " " << t << endl;
				bool flag = check(i, j, r, c, help, t);
			//	cout << flag << endl; 
				if (flag) {
					ans++;
				}
			}
		}
	}
	wr(num, ans);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//vector <vector <char > > help = {{'H', '.'}, {'H', '#'}};
	//cout << make(0, 1, 2, 2, help, 'V') << endl;
	//wr(help);
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		solve(i);
	}
	return 0;
}