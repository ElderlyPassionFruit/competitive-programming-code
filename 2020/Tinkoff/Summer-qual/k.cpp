#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

const int Maxn = 10010;
int n, k;
vector <int> pro, ans;
//int mi = 0;
//double ma = 1e18 + 228;
int siz, q;
int ans1;
int my;
//int summ;

/*	if (pro[q] < ma && siz != q){
		mi = pro[q];
		ma = (siz - q - 1) * (double)k / (q + 1) + mi;
		q++;
		searth();
	}*/


int searth(){
	int x;
	x = 1;
	//cout << siz <<' ';
	if (q + 1 == siz){return q;}
	for (int i = q + 1; i + 1 < siz && pro[i] == pro[i + 1]; i++){x++;}
	while ((q + 1) * (pro[q + 1] - pro[q]) <= k * x){
		//cout << " q = " << q << ' ';
		q++;
		if (q + 1 == siz){return q;}
		x = 1;
		for (int i = q + 1; i + 1 < siz && pro[i] == pro[i + 1]; i++){x++;}
	}
	return q;
}

signed main(){
	cin >> n >> k;
	int val;
	for (int i = 0; i < n; i++){
		cin >> val;
		pro.push_back(val);
	}
	sort(pro.begin(), pro.end());
	siz = pro.size();
	while(!pro.empty()){
		//mi = 0;
		//ma = 1e18 + 228;
		q = 0;
		searth();
		//cout << "siz = " << siz << ' ';
		ans1 += siz * (k + pro[q]);
		ans.push_back(pro[q]);
		my = pro[q];

		for (int i = 0; i < siz; i++){
			pro[i] -= my;
			//cout << pro[i] << ' ' << i << ' ';
		}


		for (int i = 0; i < n; i++){
			if (siz > 0 && pro[0] <= 0){
				pro.erase(pro.begin());
				siz -= 1;
			} else {break;}
		}
	}
	//for(auto i: ans){
	//	cout << i << ' ';
	//}
	cout << ans1;	
}