#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int cnt[10];
int cnt1[6][10];
int pws[3];
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	pws[2]=  100;
	pws[1]= 10;
	pws[0] = 1;
	string s;
	int k;
	cin>>s>>k;
	for(auto i : s) cnt[i - '0'] += k;
	if(s.size() % 6==0)
	{
		for(int i =  s.size() -1;i>=0;--i)
		{
			cnt1[(s.size() - i -1 ) % 6][s[i] - '0'] += k;
		}
	}
	else
	{
		if(k >=6)
		{
			string ts = s+s+s + s +s + s;
			for(int i = ts.size() -1;i >=0;--i)
			{
				cnt1[(ts.size() - i - 1)%6][ts[i] - '0'] += k/6;
			}
		}
		k%=6;
		string ts = s;
		s= "";
		while(k--)s += ts;
		for(int i  = (int)s.size() - 1;i >=0;--i)
		{
			cnt1[(s.size() - i - 1) % 6][s[i] -'0'] ++;
		}
		s = ts;
	}
//	for(int i = 0; i<3;++i)
//	{
//		for(int j =0 ; j< 10;++j)
//		{
//			cout<<cnt1[i][j]<<' ';
//		}
//		cout<<endl;
//	}
	int ans = 0;/*
	if((s.back() - '0') %2 == 0)
	{
		int sum1 = 0;
		int sum = 0;
		for(int i = 0; i< 10;++i)
		{//18111198
			sum1 += cnt[i] * i;
		}
		if(sum1% 3==0)
		{
			for(int i = 0; i< 10;++i)
			{
				for(int j = 0; j< 6;++j)
				{
					if(j <3)
					{
						//if((1<<i) & mask) sum += pws[j % 3] *num * cnt1[j][i];
						sum += pws[j % 3] * i * cnt1[j][i];
					}
					else
					{
						//if((1<<i) & mask) sum -= pws[j % 3] *num * cnt1[j][i];
						sum -= pws[j% 3] * i * cnt1[j][i];
					}
				}	
			}
		 	if(sum % 7 == 0) ans++;
		}
	}*/
	for(int mask = 1; mask < (1<<10);++mask)
	{
		bool f = 0;
		for(int kekos = 0; kekos< 10;++kekos)
		{
			if(!cnt[kekos] && ((1<<kekos) & mask))
			{
				f=  1;
				break;
			}
		}
		if(f) continue;
		for(int num = 0 ; num<10;++num)
		{
			if((1<<num) & mask) continue;
			
			int lds = s.back() - '0';
			if( (mask & (1<<lds)) && num% 2) continue;
			if(lds % 2)
			{
				if( !(	(1<<lds) & mask)) continue;
				if(num %2) continue;
			}
			ll sum = 0 ;
			for(int  i = 0; i<10;++i)
			{
				if(mask &(1<<i)) sum+= num * cnt[i];
				else sum += i * cnt[i];
			}
			if(sum % 3) continue;
			sum = 0;
			for(int i = 0; i< 10;++i)
			{
				for(int j = 0; j< 6;++j)
				{
					if(j <3)
					{
						if((1<<i) & mask) sum += pws[j % 3] *num * cnt1[j][i];
						else sum += pws[j % 3] * i * cnt1[j][i];
					}
					else
					{
						if((1<<i) & mask) sum -= pws[j % 3] *num * cnt1[j][i];
						else sum -= pws[j% 3] * i * cnt1[j][i];
					}
				}	
			}
		//	cout<<mask<<' '<< num <<' ' << sum<<endl;
			if(abs(sum) % 7) continue;
			ans++;
			//cout<<mask<<' '<< num<<endl;
		}
	}
	cout<<ans;
	return 0;
}