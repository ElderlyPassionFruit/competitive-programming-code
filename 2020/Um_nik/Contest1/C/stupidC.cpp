#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e7 + 100;

int lp[N], simples[N], simsz;
long long cnt[N];
bool ok(long long mid) {
	bool can = true;
	for(int i = 0; i < simsz && can; i++) {
		long long tmp = mid, f = 0;
		while(tmp) {
			tmp /= simples[i];
			f += tmp;
		}
		if (f < cnt[i])
			can = false;
	}
	return can;
}	
int main() {
	int n, max = 0;
	scanf("%d", &n);
	long long rg = 0, lf = 1;
	for(int i = 0; i < n; ++i) {
		int a;
		scanf("%d", &a);
		if (a > max)
			max = a;
		rg += a;
		++cnt[a];
	}
	for(int i = 2; i <= max; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			simples[simsz++] = i;
		}
		for(int j = 0; j < simsz && simples[j] <= lp[i] && (long long)i*simples[j]<=max; ++j) {
			lp[i * simples[j]] = simples[j];
		}
	}
	for(int i = max; i>=2; i--)
		cnt[i] += cnt[i+1];
	for(int i = max; i>=2; i--) {
		if (lp[i] != i) 
			cnt[lp[i]] += cnt[i];
		cnt[i / lp[i]] += cnt[i];
	}
        for(int i = 0; i < simsz; i++) {
		cnt[i] = cnt[simples[i]];
	}
	while (rg != lf) {
		long long mid = (rg+lf)>>1;
		if (ok(mid)) {
			rg = mid;
		} else lf = mid + 1;
	}
	cout << lf << endl;
}