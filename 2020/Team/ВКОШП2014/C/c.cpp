#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

typedef vector<int> lnum;

int k, n, r;

lnum make(int x) {
	lnum ans;
	int l = 2;
	for (int i = 0; i < n; i++) {
		if (l >= x) {
			ans.push_back(1);
			l -= x;
			l *= 2;
		} 
		else {
			ans.push_back(0);
			l *= 2;
		}
	}
	while(!ans.back()) ans.pop_back();
	return ans;
}

lnum operator*(lnum a, int x) {
	lnum tkek;
	for(int  i = 0; i < 10;++i)
	{
		if((1<<i) &  x) tkek.push_back(1);
		else tkek.push_back(0);
	}
	//reverse(all(tkek));
	while(tkek.size() >1 && ! tkek.back()) tkek.pop_back();
	reverse(all(tkek));
	cout<<"x = " ;
	for(int i: tkek) cout<<i<<' ';
	cout<<endl;
	cout<<"a = ";
	for(int i  : a) cout<<i<<' ';
	cout<<endl;
	vector<int> c(a.size()  +  tkek.size());
	for(int i = 0 ; i< a.size();++i)
	{
		for(int j =0 ; j < tkek.size();++j)
		{
			c[i+j]  += a[i] * tkek[j];
		}
	}
	reverse(all(c));
	for(int i = 0 ; i< c.size();++i)
	{
		int x = c[i] / 2;
		c[i] %=2;
		if( x && i == c.size() - 1)
		{
			c.push_back(x);
		}
		else
		{
			c[i+1] += x;
		}
	}
	reverse(all(c));
	return c;
}

bool check(int x) {
	lnum a = make(x);
	/*cout<<"a = ";
	for(int i: a)
	{
		cout<<i<<' ';
	}
	cout<<endl;*/
	a = a * x;
	/*cout<<"a = ";
	for(int i: a)
	{
		cout<<i<<' ';
	}
	cout<<endl;*/
	int kekos = a[0];
	cout<<"kekos = "<< kekos<<endl;
	//if(!kekos) return 1;
	if(a[k+1])
	{
		a[k] ++;
		for(int j = k + 1; j < a.size();++j) a[j] = 0;
	}
	else
	{
		for(int j = k+ 1;j < a.size();++j) a[j] = 0;
	}
	for(int i = 1;i <=k; ++i)
	{
		if( a[i]) return 1;
	}
	return 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	vector<int> ans;
	cin >> n >> k >> r;
	for (int i = 2; i <= r; i++)
		if (check(i))
			ans.push_back(i);
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	return 0;
}