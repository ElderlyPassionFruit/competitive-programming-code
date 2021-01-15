#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
vector<int> dx{1,-1,0,0};
vector<int> dy{0,0,1,-1};
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n,m;
	cin>>n>>m;
	vector<vector<char>> a(n, vector<char> (m));
	int ti1 =0, tj1 = 0, ti2 = 0, tj2 = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> a[i][j];
			if(a[i][j] == 'f') {
				ti1 = i, tj1 = j;
			}
			if(a[i][j] == 's') {
				ti2 = i, tj2 = j;
			}
		}
	}
	bool f1 = false, f2 = false;
	vector<vector<bool>> used(n, vector<bool> (m));
	used[ti1][tj1] = 1;
	queue<pair<int,int> > q;
	q.push({ti1, tj1});
	while(q.size()) {
		pair<int,int> v = q.front();
		q.pop();
		for(int i = 0; i < 4; i++) {
			int nx = v.first + dx[i];
			int ny = v.second + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
				if (a[nx][ny] != '#') {
					if (i < 2)
						f1 = true;
					else
						f2 = true;
				}
				if(!used[nx][ny] && a[nx][ny] !='#')
				{
					used[nx][ny] = 1;
					q.push({nx,ny});
				}
			}
		}
	}
	if(!used[ti2][tj2]) {
		cout << -1;
		return 0;
	}
	
	if (f1 && f2)
		cout << (abs(abs(ti1 - ti2) - abs(tj1 - tj2))) % 2;
	else
		cout << (abs(abs(ti1 - ti2) - abs(tj1 - tj2)));	
	return 0;
}