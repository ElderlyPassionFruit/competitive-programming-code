#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long
int t;
void read()
{
	cin >> t;
}
vector <int> ans;

int get(int n)
{
	return n*(n + 1) / 2;
}

void run()
{
	for (int i = 0; i < t; i++)
	{
		int n, k;
		cin >> n >> k;
		int x1 = (k - 1) / 2;
		int x2 = (k + 1) / 2;
		int ans1 = get(x1);
		int ans2 = 0;
		if (x2 <= n)
			ans2 = k * (min(n, k - 1) - x2 + 1) - get(min(n, k - 1)) + ans1;
	//	cout << endl << endl;
	//	cout << "get: " << ans1 <<  " " << ans2 << endl;
	//	cout << "x1, x2 " << x1 << " " << x2 << endl; 
		ans.push_back(ans1 + ans2);
	}
}


void write()
{
	for (auto i : ans)
		cout << i << endl;
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