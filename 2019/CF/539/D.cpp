#include <bits/stdc++.h>

using namespace std;

string s;
int n;
	
bool check(int pos){
	string fans = "";
	for (int i = pos + 1; i < n; i++)
		fans += s[i];
	for (int i = 0; i <= pos; i++)
	{
		fans += s[i];
	}
	string help = fans;
	reverse(help.begin(), help.end());
	return help == fans && s != help;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> s;
	n = s.length();

	bool flag = true;
	for (int i = 1; i < n; i++)
	{
		if (s[i] != s[i - 1])
		{
			if (n % 2 == 0 || abs(i - n / 2) > 1)
			{
				flag = false;
				break;
			}
		}
	}

	if (flag)
	{
		cout << "Impossible" << endl;
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		if (check(i))
		{
			cout << 1 << endl;
			return 0;
		}
	}

	cout << 2 << endl;
	return 0;
}