#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using matrix = vector<vector<ll>>;

matrix gaussianEliminationDown(matrix a) {
    int n = a.size();
    int m = a[0].size();
    int last = 0;
    swap(a[0], a[n - 1]);
    for (int i = 0; i < m; ++i) {
        bool ok = false;
        for (int j = last; j < n; ++j) {
            if (a[j][i] != 0) {
                swap(a[last], a[j]);
                ++last;
                ok = true;
                break;
            }
        }
        if (!ok) continue;
        ll g = 0;
        for (int j = i; j < m; ++j) {
            g = __gcd(g, abs(a[last - 1][j]));
        }
        if (g != 0) {
            for (int j = i; j < m; ++j) {
                a[last - 1][j] /= g;
            }
        }
        cerr << "a = " << endl;
        for (auto i : a) {
            for (auto j : i) {
                cerr << j << " ";
            }
            cerr << endl;
        }
        for (int j = last; j < n; ++j) {
            if (a[j][i] == 0) continue;
            ll coeff = a[last - 1][i] / __gcd(a[last - 1][i], a[j][i]);
            ll myCoeff = a[j][i] / __gcd(a[last - 1][i], a[j][i]);

            for (int k = i; k < m; ++k) {
                a[j][k] = a[j][k] * coeff - a[last - 1][k] * myCoeff;    
            }
        }
    }
    return a;
}

matrix gaussianEliminationUp(matrix a) {
    int n = a.size();
    int m = a[0].size();
    for (int i = n - 1; i >= 0; --i) {
        int pos = 0;
        while (pos < m && a[i][pos] == 0) ++pos;
        if (pos == m) continue;
        cerr << "a = " << endl;
        for (auto x : a) {
            for (auto y : x) {
                cerr << y << " ";
            }
            cerr << endl;
        }
        for (int j = i - 1; j >= 0; --j) {
            ll coeff = a[i][pos] / __gcd(abs(a[i][pos]), abs(a[j][pos]));
            ll myCoeff = a[j][pos] / __gcd(abs(a[i][pos]), abs(a[j][pos]));            
            cerr << "i = " << i << " coeff = " << coeff << " myCoeff = " << myCoeff << endl;
            for (int k = pos; k < m; ++k) {
                a[j][k] = a[j][k] * coeff - a[i][k] * myCoeff;    
            }
        }
    }
    return a;
}

void make(matrix a) {
    auto ans = gaussianEliminationDown(a);
    
    for (int i = 0; i < 5; ++i) {
        ans[1][i] *= -1;
    }
    cerr << "matrix = " << endl;
    for (auto i : ans) {
        for (auto j : i) {
            cerr << j << " ";
        }
        cerr << endl;
    }
    ans = gaussianEliminationUp(ans);
    cerr << "matrix = " << endl;
    for (auto i : ans) {
        for (auto j : i) {
            cerr << j << " ";
        }
        cerr << endl;
    }
    
}

matrix operator+(const matrix& a, const matrix& b) {
    matrix ans(a.size(), vector<ll>(a[0].size(), 0));
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            ans[i][j] = a[i][j] + b[i][j];
        }
    }
    return ans;
}

matrix operator-(const matrix& a, const matrix& b) {
    matrix ans(a.size(), vector<ll>(a[0].size(), 0));
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            ans[i][j] = a[i][j] - b[i][j];
        }
    }
    return ans;
}

int main() {
    matrix a = {
        {-1, 5, -16, -5, 11},
        {1, 1, 3, 5, -3},
        {3, 5, 6, -1, -1},
        {1, -7, 21, -3, -11},
        {2, 6, -2, 2, 2}
    };
    make(a);
    matrix x1 = {
        {-1, 0, 0, -67, 25},
        {1, 0, 0, 67, -25},
        {3, 0, 0, 201, -75},
        {1, 0, 0, 67, -25},
        {2, 0, 0, 134, -50}
    };

    matrix x2 = {
        {0, 5, 0, -130, 50},
        {0, 1, 0, -26, 10},
        {0, 5, 0, -130, 50},
        {0, -7, 0, 182, -70},
        {0, 6, 0, -156, 60}        
    };

    matrix x3 = {
        {0, 0, -16, 192, -64},
        {0, 0, 3, -36, 12},
        {0, 0, 6, -72, 24},
        {0, 0, 21, -252, 84},
        {0, 0, -2, 24, -8}
    };

    auto ans = a - (x1 + x2 + x3);
    cerr << "ans = " << endl;
    for (auto i : ans) {
        for (auto j : i) {
            cerr << j << " ";
        }
        cerr << endl;
    }
}