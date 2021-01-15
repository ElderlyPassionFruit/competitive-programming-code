#include <bits/stdc++.h>

using namespace std;

#define int long long
string s;
void read()
{
	cin >> s;
	s += "aaaa";
}

string ans;
void run()
{
	string fans = "";
	bool plus = true;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == 'a')
			break;
		if (s[i] == '+')
		{
			plus = true;
		}

		if (s[i] == '-')
		{
			plus = false;
		}

		if (plus || s[i] == '-')
		{
			fans += s[i];
			continue;
		}

		if (!plus)
		{
			fans += s[i];
			if (s[i + 1] != '-' && s[i + 1] != '+' && s[i + 1] != 'a')
				fans += "+";
			while (s[i + 1] == '0')
			{
				fans += s[i + 1];
				if (s[i + 2] != '-' && s[i + 2] != '+' && s[i + 2] != 'a')
					fans += "+";
				i++;
			}
			plus = true;
		}
	}
	ans = fans;
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