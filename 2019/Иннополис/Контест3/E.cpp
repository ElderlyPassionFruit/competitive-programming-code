#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, g;
vector <vector <int> > a;
vector <bool> used;
void read()
{
	cin >> n >> g;
	for (int i = 0; i < g; i++)
	{
		a.push_back({});
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; j++)
		{
			int x;
			cin >> x;
			a[i].push_back(x);
		}
		used.push_back(false);
	}
	sort(a.begin(), a.end());
}

int ans;
void run()
{
	unordered_set <int> have;
	have.insert(1);
	while (true)
	{
		bool flag = true;
		for (int i = 0; i < g; i++)
		{
			if (!used[i])
			{
				int cnt = 0;
				int num = 1;
				for (int j = 0; j < a[i].size(); j++)
				{
					if (have.find(a[i][j]) == have.end())
					{	
						cnt ++;
						num = a[i][j];
					}
				}
				if (cnt == 1)
				{
					have.insert(num);
					used[i] = true;
					flag = false;
				}
			}
		}
		if (flag)
			break;
	}
	ans = have.size();
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
	freopen("invite.in", "r", stdin);
	freopen("invite.out", "w", stdout);
	read();
	run();
	write();
	return 0;
}