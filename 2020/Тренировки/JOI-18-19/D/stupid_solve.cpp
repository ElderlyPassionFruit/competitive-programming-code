
#include<cstdio>
#include<algorithm>
using namespace std;
int n, C[101000][2];
long long res;
struct point {
	int x, y;
}w[101000];
void Make(int &x, int b, int e) {
	if (x < b)res += b - x, x = b;
	if (x > e)res += x - e, x = e;
}
void Do(int pv) {
	if (pv == n + 1)return;
	int t1 = C[pv][0] - 1;
	int t2 = C[pv][1] - 1;
	if(1ll*t1*t2<0){
		int t = min(abs(t1), abs(t2));
		if (t1 < 0)t1 += t; else t1 -= t;
		if (t2 < 0)t2 += t; else t2 -= t;
		res += t;
	}
	res += abs(t1) + abs(t2);
	C[pv + 1][0] += t1, C[pv + 1][1] += t2;
	Do(pv + 1);
}
int main() {
	int i, x, y;
	scanf("%d", &n);
	for (i = 1; i <= 2*n; i++) {
		scanf("%d%d", &x, &y);
		Make(x, 1, n);
		Make(y, 1, 2);
		C[x][y - 1]++;
	}
	Do(1);
	printf("%lld\n", res);
}