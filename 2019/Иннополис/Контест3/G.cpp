#include <bits/stdc++.h>

using namespace std;

#define int long long
int n;
map <int, vector<int> > a;
vector <int> b;
int k;
void read()
{
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		b.push_back(x);
	}
	cin >> k;
	for (int i = 0; i < n; i++)
	{
		a[i % k].push_back(b[i]);
	}
	sort(b.begin(), b.end());
}
int ans;
void run()
{
	ans = 0;
	for (int x = 0; x < k; x++)
	{
		for (int i = 0; i < a[x].size(); i++)
		{
			for (int j = 0; j < a[x].size() - 1; j++)
			{
				if (a[x][j] > a[x][j + 1])
				{
					swap(a[x][j], a[x][j + 1]);
					ans++;
				}
			}
		}
	}
	vector <int> fans;
	for (int i = 0; i < n; i++)
	{
		fans.push_back(a[i%k][i/k]);
	}
	if (fans != b)
	{
		ans = -1;
	}
}

void write()
{
	cout << ans << endl;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}