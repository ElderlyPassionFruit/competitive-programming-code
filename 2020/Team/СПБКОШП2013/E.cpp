#pragma GCC optimize("unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,avx,mmx,avx2,popcnt,tune=native,abm")
#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
 
int len(int n) {
	int ans = 0;
	while(n) {
		ans++;
		n /= 10;
	}
	return max(ans, 1LL);
}
 
vector<int> getd(int n) {
	if(n == 0) return {0};
	vector<int> ans;
	while(n) {
		ans.push_back(n % 10);
		n /= 10;
	}
	reverse(all(ans));
	return ans;
}
 
int check(int a, int b) {
	int ans = 0;
	while (a) {
		ans += (a % 10) != (b % 10);
		a /= 10;
		b /= 10;
	}
	return ans;
}
 
int pww(int a, int b) {
	int res = 1;
	while(b--) {
		res *= a;
	}
	return res;
}
 
int siberian(const vector<int> & a, const vector<int> & b) {
	int ans= 0 ;
	for(int i = 0; i < (int)a.size(); ++i) {
		ans += a[i] != b[i];
	}
	return ans;
}
 
int fff(const vector<int> & a)
{
	int ans = 0;
	for(int i : a) {
		ans *= 10, ans += i;
	}
	return ans;
}
 
int n,m;
vector<int> kekes;
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//cout.precision(20);
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	cin>>n>>m;
	if(len(n) < len(m)) {
		if(len(n) == 1) {
			cout << 0;
			return 0;
		}
		cout << -1;
		return 0;
	}
 
	if(n % m == 0) {
		cout << n;
		return 0;
	}
 
	kekes = getd(n);
	if(m >= 10000)
	{
		int x = pww(10, len(n) - 1);
		int lol = (x + m - 1) / m * m;
		int ans = 1234, ans2 = 0 ;
		int y = pww(10, len(n));
		for(; lol < y; lol += m) {
			int tans = check(n, lol);
			if( tans < ans)	{
				ans  = tans, ans2 = lol;
			}
		}
 
		if(ans==1234) {
			cout << -1;
			return 0 ;
		}
		cout << ans2;
	}	
	else {
		int ans = 1234, ans2 = 0;
		for(int chg = 1; chg <= min(4ll, len(n)); ++chg) {
			vector<int> perm(len(n));
			for(int j = perm.size() - 1; j >= (int)perm.size() - chg; --j)
				perm[j] = 1;
			vector<vector<int>> numsos;
			int x = pww(10, chg);
			for(int  i = 0; i < x; ++i) {
				auto getdd = getd(i);
				reverse(all(getdd));
				while(getdd.size() < chg)
					getdd.push_back(0);
				numsos.push_back(getdd);
			}
 
			do {
				for (vector<int> & i : numsos) {
					auto ttx = kekes;
					int sock =1;
 					for(int j = 0; j < (int)perm.size(); ++j) {
 						if(perm[j]) {
 							ttx[j] = i[i.size() - sock];
 							++sock;
 						}
 					}
 
 					int numnum = fff(ttx);
 					if(numnum % m|| len(numnum) < len(n)) continue;				
 					int xxx = siberian(ttx, kekes);
 
 					if( xxx < ans) {
 						ans = xxx, ans2 = numnum;
 					}
				}
			} while(next_permutation(all(perm)));
		}
		if(ans == 1234){
			cout << -1;
		}
		else {
			cout << ans2;
		}
	}
	return 0;
}