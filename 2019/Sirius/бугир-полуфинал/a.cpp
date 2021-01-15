#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double

const int MAXN = 1e5 + 10;
double n, a, b;
double x[MAXN], v[MAXN];

void read() {
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> v[i];
	}
}

double ans;
void run() {

    for (int i = 0; i < n; i++) {
    	double s = x[i + 1] - x[i];
    	double v_finish = sqrt(v[i] * v[i] + a * s * 2);
    	
    	if (v_finish < v[i + 1]) {
    		v[i + 1] = v_finish;
    	}
    }

   	cout << "v = ";
    for (int i = 0; i <= n; i++)
    	cout << v[i] << " ";
    cout << endl;
    for (int i = n; i > 1; i--) {
    	double s = x[i] - x[i - 1];
    	double v_finish = sqrt(v[i] * v[i] + b * s * 2);
    	
    	if (v_finish < v[i - 1]) {
    		v[i - 1] = v_finish;
    	}
    }

    cout << "v = ";
    for (int i = 0; i <= n; i++)
    	cout << v[i] << " ";
    cout << endl;
    ans = 0;

    for (int i = 0; i < n; i++) {
    	double dv = 0;
    	double t = 0;
    	double s = x[i + 1] - x[i];
    	if (v[i] <= v[i + 1]) {
    		dv = v[i + 1] - v[i];
    		t = dv / a;
    		double s1 = v[i] * t + ((a * t * t) / 2);
    		double t2 = (s - s1) / v[i + 1];
    		cout << "t = " << t << endl;
    		cout << "t2 = " << t2 << endl;
    		cout << "s = " << s << " s1 = " << s1 << endl;
    		ans += t + t2;
    	}
    	/*else {
    		dv = v[i] - v[i + 1];
    		t = dv / b;
    		double s1 = v[i] * t - ((b * t * t) / 2);
    		double t2 = (s - s1) / v[i];
    		ans += t + t2;
    	}*/
    	cout << ans << endl;
    }
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(20);
	read();
	run();
	write();
	return 0;
}