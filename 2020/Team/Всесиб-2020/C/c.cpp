#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

string s;

const int MAXN = (1 << 24) + 5;
uint8_t a[MAXN];
uint8_t pr[MAXN];

struct obj {
    int val, dp, ind;
};

bool operator<(const obj& A, const obj& B){
    if (A.val != B.val)
        return A.val > B.val;
    return A.dp > B.dp;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
    freopen("input.bin", "r", stdin);
    freopen("output.bin", "w", stdout);
    uint8_t c;
    int n = 0;
    while (cin >> c){
        ++n;
        a[n] = c;
    }
    deque<pair<int, int>> dp_vals;
    dp_vals.push_back({0, 1});
    //{dp[j - 1], j}
    priority_queue<obj> pq;
    pq.push({1 + a[1], 0, 1});
    
    deque<int> dp = {0, (int)1e9};
    //{a[j] + j, dp[j - 1], j}
    

    int last_dp = 1e9;
    for (int i = 2; i <= n; ++i){
        int dp_val = 1e9;
        int ln_now = -1;
        
        //a[i] - correct
        int ind = 257 - (a[i] + 2);
        if (ind < dp.size() && ind >= 0){
            dp_val = dp[ind];
            if (a[i - a[i] + 2] != a[i])
                dp_val++;
            ln_now = a[i];
        }
        
        //a[j] - correct
        while (pq.size() > 0){
            auto res = pq.top();
            if (res.val < i - 1){
                pq.pop();
                continue;
            }
            if (res.val > i - 1){
                break;
            }
            if (dp_val > res.dp + 1){
                dp_val = res.dp + 1;
                ln_now = a[res.ind];
            }
            break;
        }

        //both fucking bad
        while (!dp_vals.empty()){
            auto res = dp_vals[0];
            if (i - res.second - 2 <= 255){
                if (dp_val > res.first + 2){
                    dp_val = res.first + 2;
                    ln_now = i - res.second - 2;
                    //break;
                }
                break;
            }
            dp_vals.pop_front();
        }
        pq.push({a[i] + i, last_dp, i});
        while (!dp_vals.empty()){
            if (dp_vals.back().first >= last_dp){
                dp_vals.pop_back();
                continue;
            }
            break;
        }
        dp_vals.push_back({last_dp, i});
        dp.push_back(dp_val);
        if (dp.size() > 256){
            dp.pop_front(); 
        }
        last_dp = dp_val;
        pr[i] = ln_now;
    }
    vector<int> ans;
    int now = n;
    while (now != 0){
        ans.push_back(now);
        now = now - (pr[now] + 2);
    }
    reverse(ans.begin(), ans.end());
    for (auto elem : ans){
        uint8_t a, b, c;
        uint8_t ln = pr[elem];
        c = elem & 0b11111111;
        elem >>= 8;
        b = elem & 0b11111111;
        elem >>= 8;
        a = elem;
        cout << a << " " << b << " " << c << " " << ln << " "; 
    }
	return 0;
}