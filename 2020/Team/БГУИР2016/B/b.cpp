#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 1e5 + 10;
mt19937 rnd(time(0));
// int n;
// vector<int> a;

// int stupid_solve() {
// 	int fans = 0;
// 	int pos = -1;
// 	int ans = -1e18;
// 	int l = 0, r = 0;
// 	int pref = 0;
// 	for (int i = 0; i < n; i++) {
// 		pref += a[i];
// 		if (pref - fans > ans) {
// 			ans = pref - fans;
// 			if (pos >= 0 && i - pos > 1) {
// 				l = i - 1, r = i;
// 			}
// 		}
// 	}
// }
struct test
{
	int n;
	vector<int> a;
	test(int an)
	{
		n = an;
		a.resize(n);
	}
};
test gen()
{
	int n = rnd() % 20 + 8;
	test ans = test(n);
	for(int i = 0 ;i < n;++i)
	{
		ans.a[i] = rnd() % 50 - 25;
	}
	return ans;
}
int stupid(vector<int> a)
{
	int ans = *min_element(all(a));
	int sum = 0;
	for(int i : a)
	{
		sum += i;
		ans = max(ans, sum);
		sum = max(sum, 0ll);
	}
	return ans;
}
int testsolve(test a)
{
	int tans = -1e18;
	int n = a.n;
	for(int i = 0 ; i< n;++i)
	{
		for(int j  = i+1;j< n;++j)
		{
			swap(a.a[i], a.a[j]);
			tans = max(tans, stupid(a.a));
			swap(a.a[i], a.a[j]);
		}
	}
	return tans;
}
pair<pair<int,int>, int> solve(test a)
{
	vector<int> arr=  a.a;
	int n = a.n;
//	in >> n;
//	vector<int> arr;
////	arr.resize(n);
//	for (auto &i : arr)
//		cin >> i;
	vector<int> prefl(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		prefl[i] = prefl[i - 1] + arr[i - 1];
	}
	vector<int> prefr(n + 1);
	for (int i = 1; i <= n; i++) {
		prefr[i] = prefr[i - 1] + arr[n - i];
	}
	int ans1 = -1e18;
	int l1 = -1;
	int r1 = -1;
	vector<int> indl(n);
	
	int ind1 = 0;
	
	for (int i = 1; i <= n; i++) {
		indl[i - 1] = i - ind1 - 1;
		if (prefl[i] - prefl[ind1] > ans1) {
			ans1 = prefl[i] - prefl[ind1];
			l1 = ind1 + 1;
			r1 = i;
		}
		if (prefl[i] <= prefl[ind1]) {
			ind1 = i;
		}
	}


	if (l1 == r1) {
		l1 = 1, r1 = 2;
	}

	vector<int> indr(n);
	int ind2 = 0;
	for (int i = 1; i <= n; i++) {
		indr[n - i] = i - ind2 - 1;
		if (prefr[i] <= prefr[ind2]) {
			ind2 = i;
		}
	}

	vector<pair<int, int>> maxl(n);
	vector<pair<int, int>> maxr(n);

	maxl[0] = {arr[0], 0};
	maxr[n - 1] = {arr[n - 1], - n + 1};

	for (int i = 1; i < n; i++) {
		maxl[i] = max(maxl[i - 1], {arr[i], i});
	}

	for (int i = n - 2; i >= 0; i--) {
		maxr[i] = max(maxr[i + 1], {arr[i], -i});
	}

	int ans2 = -1e18;
	int l2 = -1;
	int r2 = -1;



	for (int br = 0; br < n; br++) {
		int ln1 = indl[br];
		int ln2 = indr[br];


		if (ln1 > 0) {
			int l = br - ln1 + 1;
			int r = br + ln2;
			int ans = prefl[r + 1] - prefl[l];
			ans -= arr[br];
			ans += arr[br - ln1];
			if (ans > ans2) {
				ans2 = ans;
				l2 = br + 1;
				r2 = br - ln1 + 1;
			}
		}

		if (ln2 > 0) {
			int l = br - ln1;
			int r = br + ln2 - 1;
			int ans = prefl[r + 1] - prefl[l];
			ans -= arr[br];
			ans += arr[br + ln2];
			if (ans > ans2) {
				ans2 = ans;
				l2 = br + 1;
				r2 = br + ln2 + 1;
			}	
		}

		pair<int, int> mx = {-1e18, 0};
		if (br - ln1 != 0) {
			mx = max(mx, maxl[br - ln1 - 1]);
		}
		if (br + ln2 + 1 < n) {
			mx = max(mx, maxr[br + ln2 + 1]);
		}

		if (mx.first == -1e18) {
			continue;
		}
		int l = br - ln1;
		int r = br + ln2;
		int ans = prefl[r + 1] - prefl[l];
		ans -= arr[br];
		ans += mx.first;
		//cout << "br = " << br << " l = " << l << " r = " << r << " mx = " << mx.first << " " << mx.second << " ans = " << ans << endl;
		if (ans > ans2) {
			ans2 = ans;
			l2 = br + 1;
			r2 = abs(mx.second) + 1;
		}
	}

	//cout << ans1 << " " << ans2 << endl;

	if (ans1 > ans2) {
		return{{l1,r1},ans};
		cout << ans1 << endl;
		cout << l1 << " " << r1 << endl;
	} else {
		return{{l2,r2},ans};
		cout << ans2 << endl;
		cout << l2 << " " << r2 << endl;
	}
}
void print(test a)
{
	cout<<a.n<<endl;
	for(int i : a.a)
	{
		cout<<i<<' ';
	}
	cout<<endl;
}
void check(pair<pair<int,int>,int> ansos, test a)
{
	vector<int> ta = a.a;
	int jj = testsolve(a);
	ansos.first.first--;
	ansos.first.second--;
	swap(ta[ansos.first.first], ta[ansos.first.second]);
	if(stupid(ta)!= ansos.second  || ansos.second != jj)
	{
		cout<<"HALT"<<endl;
		print(a);
		while(1);
	}
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	while(1)
	{
		test keks = gen();
		auto kok = solve(keks);
		check(kok, keks);	
	}
	int n;
	cin >> n;
	vector<int> arr;
	arr.resize(n);
	for (auto &i : arr)
		cin >> i;
	vector<int> prefl(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		prefl[i] = prefl[i - 1] + arr[i - 1];
	}
	vector<int> prefr(n + 1);
	for (int i = 1; i <= n; i++) {
		prefr[i] = prefr[i - 1] + arr[n - i];
	}
	int ans1 = -1e18;
	int l1 = -1;
	int r1 = -1;
	vector<int> indl(n);
	
	int ind1 = 0;
	
	for (int i = 1; i <= n; i++) {
		indl[i - 1] = i - ind1 - 1;
		if (prefl[i] - prefl[ind1] > ans1) {
			ans1 = prefl[i] - prefl[ind1];
			l1 = ind1 + 1;
			r1 = i;
		}
		if (prefl[i] <= prefl[ind1]) {
			ind1 = i;
		}
	}

	if (n == 2) {
		cout << ans1 << endl;
		cout << 1 << " " << 2 << endl;
		return 0;
	}

	if (l1 == r1) {
		l1 = 1, r1 = 2;
	}

	vector<int> indr(n);
	int ind2 = 0;
	for (int i = 1; i <= n; i++) {
		indr[n - i] = i - ind2 - 1;
		if (prefr[i] <= prefr[ind2]) {
			ind2 = i;
		}
	}

	vector<pair<int, int>> maxl(n);
	vector<pair<int, int>> maxr(n);

	maxl[0] = {arr[0], 0};
	maxr[n - 1] = {arr[n - 1], - n + 1};

	for (int i = 1; i < n; i++) {
		maxl[i] = max(maxl[i - 1], {arr[i], i});
	}

	for (int i = n - 2; i >= 0; i--) {
		maxr[i] = max(maxr[i + 1], {arr[i], -i});
	}

	int ans2 = -1e18;
	int l2 = -1;
	int r2 = -1;



	for (int br = 0; br < n; br++) {
		int ln1 = indl[br];
		int ln2 = indr[br];


		if (ln1 > 0) {
			int l = br - ln1 + 1;
			int r = br + ln2;
			int ans = prefl[r + 1] - prefl[l];
			ans -= arr[br];
			ans += arr[br - ln1];
			if (ans > ans2) {
				ans2 = ans;
				l2 = br + 1;
				r2 = br - ln1 + 1;
			}
		}

		if (ln2 > 0) {
			int l = br - ln1;
			int r = br + ln2 - 1;
			int ans = prefl[r + 1] - prefl[l];
			ans -= arr[br];
			ans += arr[br + ln2];
			if (ans > ans2) {
				ans2 = ans;
				l2 = br + 1;
				r2 = br + ln2 + 1;
			}	
		}

		pair<int, int> mx = {-1e18, 0};
		if (br - ln1 != 0) {
			mx = max(mx, maxl[br - ln1 - 1]);
		}
		if (br + ln2 + 1 < n) {
			mx = max(mx, maxr[br + ln2 + 1]);
		}

		if (mx.first == -1e18) {
			continue;
		}
		int l = br - ln1;
		int r = br + ln2;
		int ans = prefl[r + 1] - prefl[l];
		ans -= arr[br];
		ans += mx.first;
		//cout << "br = " << br << " l = " << l << " r = " << r << " mx = " << mx.first << " " << mx.second << " ans = " << ans << endl;
		if (ans > ans2) {
			ans2 = ans;
			l2 = br + 1;
			r2 = abs(mx.second) + 1;
		}
	}

	//cout << ans1 << " " << ans2 << endl;

	if (ans1 > ans2) {
		cout << ans1 << endl;
		cout << l1 << " " << r1 << endl;
	} else {
		cout << ans2 << endl;
		cout << l2 << " " << r2 << endl;
	}
	return 0;
}

/*
5
1 -2 -3 4 -5

*/