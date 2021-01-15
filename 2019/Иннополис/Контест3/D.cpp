#include <bits/stdc++.h>

using namespace std;

#define int long long
int n;
void read()
{
	cin >> n;	
}

void run()
{
	int must = 10;
	int cnt = 0;
	for (int i = 0; i < must; i++)
	{
		vector <int> t(must);
		for (int j = 0; j < i; j++)
		{
			t[must - 1 - j] = 1;
		}
		do
		{
			for (int j = 0; j < must; j++)
			{
				if (t[j] == 0)
					cout << "edHs";
				else
					cout << "edIT";
			}
			cout << '\n';
			cnt++;
			if (cnt == n)
				return;
		}while(next_permutation(t.begin(), t.end()));
	}
	cout << "puhh\n";
}

void write()
{
	
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