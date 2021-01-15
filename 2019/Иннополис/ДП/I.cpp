#include <bits/stdc++.h>

using namespace std;

#define int long long

const int base = 10;
typedef vector <int> lnum;
typedef vector <vector <int> > matrix;

lnum n;
int m, MOD;

lnum read(string s)
{
	lnum ans(s.size());
	for (int i = 0; i < s.size(); i++)
	{
		ans[i] = s[s.size() - 1 - i] - '0';
	}
	return ans;
}

lnum M(lnum n)
{
	for (int i = 0; i < n.size(); i++)
	{
		if (n[i] != 0)
		{
			n[i]--;
			break;
		}
		n[i] = 9;
	}
	for (int i = n.size() -  1; i >= 0; i--)
	{
		if (n[i] != 0)
			return n;
		n.pop_back();
	}
	return n;
}

lnum D(lnum n)
{
	for (int i = n.size() -  1; i >= 0; i--)
	{
		if (n[i] % 2 == 1)
		{
			n[i - 1] += 10;
		}
		n[i] /= 2;
	}
	
	for (int i = n.size() -  1; i >= 0; i--)
	{
		if (n[i] != 0)
			return n;
		n.pop_back();
	}
	return n;
}

bool is(lnum n)
{
	for (int i = 0; i < n.size(); i++)
	{
		if (n[i] != 0)
			return false;
	} 
	return true;
}


matrix mul(matrix a, matrix b)
{
	int n = a.size();
	int m = a[0].size();
	int k = b[0].size();
	matrix c (n, vector <int> (k, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k; j++)
		{
			for (int t = 0; t < m; t++)
			{
				c[i][j] += a[i][t] * b[t][j];
				c[i][j] %= MOD;
			}
		}
	}
	return c;
}

matrix fastpow(matrix a, lnum n)
{
	if (is(n))
	{
		matrix ans (a.size(), vector <int> (a.size(), 0));
		for (int i = 0; i < a.size(); i++)
			ans[i][i] = 1;
		return ans;
	}
	if (n[0] % 2 == 0)
	{
		matrix ans = fastpow(a, D(n));
		return mul(ans, ans);
	}
	else
	{
		matrix ans = fastpow(a, M(n));
		return mul(ans, a);
	}
}

int check(int a, int b)
{
	for (int i = 1; i < m; i++)
	{
		int cnt = 0;
		cnt += (a >> i) & 1;
		cnt += (a >> (i - 1)) & 1;
		cnt += (b >> i) & 1;
		cnt += (b >> (i - 1)) & 1;
		if (cnt == 4 || cnt == 0)
			return false;
	}
	return true;
}


signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	n = read(s);
	cin >> m >> MOD;
	matrix mat (1 << m, vector <int> (1 << m, 0));
	for (int i = 0; i < (1 << m); i++)
	{
		for (int j = 0; j < (1 << m); j++)
		{
			if (check(i, j))
				mat[i][j] = 1;
		}
	}
	n = M(n);
	mat = fastpow(mat, n);
	matrix bas (1 << m, vector <int> (1, 1));
	bas = mul(mat, bas);
	int ans = 0;
	for (int i = 0; i < (1 << m); i++)
	{
		ans += bas[i][0];
		ans %= MOD;
	}
	cout << ans << endl;
	return 0;	
}











