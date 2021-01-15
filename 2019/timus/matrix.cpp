#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class matrix {
    int n;
    vector<vector<int> > data;

public:

    matrix(vector<vector<int> >);

    int size() const { return n; };

    matrix operator+(matrix);

    matrix operator*(int);

    matrix operator*(matrix);

    matrix t();

    const vector<int>& operator[](const int i) const { return data[i]; };

    friend ostream& operator<<(ostream&, const matrix&);

};

matrix::matrix(vector<vector<int> > vect) {
    data = vect;
    n = vect.size();
}

matrix matrix::operator+(matrix b) {
    vector<vector<int> > res(data.size(), vector<int>(data[0].size()));
    if (b.data.size() == data.size() && b.data[0].size() == data[0].size()) {
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[0].size(); ++j) {
                res[i][j] = data[i][j] + b.data[i][j];
            }
        }
    }
    return matrix(res);
}

matrix matrix::operator*(int k) {
    vector<vector<int> > res(data.size(), vector<int>(data[0].size()));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            res[i][j] = data[i][j] * k;
        }
    }
    return matrix(res);
}

matrix matrix::operator*(matrix b) {
    vector<vector<int> > res(data.size(), vector<int>(b.data[0].size()));
    if (b.data.size() == data[0].size()) {
        int result;
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < b.data[0].size(); ++j) {
                result = 0;
                for (int k = 0; k < data[0].size(); ++k) {
                    result += data[i][k] * b.data[k][j];
                }
                res[i][j] = result;
            }
        }
    }
    return matrix(res);
}

matrix matrix::t() {
    vector<vector<int> > res(data[0].size(), vector<int>(data.size()));
    for (int i = 0; i < data[0].size(); ++i) {
        for (int j = 0; j < data.size(); ++j) {
            res[i][j] = data[j][i];
        }
    }
    return matrix(res);
}

ostream& operator<<(ostream& out, const matrix& data) {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            out << data[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

const double EPS = 1e-9;
const int INF = 1e9;

int gauss(vector<vector<double> > a, vector<double> & ans) {
    int n = a.size();
    
    vector<int> pos (n, -1);
    for (int c = 0, r = 0; c < n && r < n; ++c) {
        int my = r;
        for (int i = r; i < n; ++i) {
            if (abs(a[i][c]) > abs(a[my][c])) {
                my = i;
            }
        }
        if (abs(a[my][c]) < EPS) {
            continue;
        }
        for (int i = c; i <= n; ++i) {
            swap(a[my][i], a[r][i]);
        }
        pos[c] = r;
 
        for (int i = 0; i < n; ++i)
            if (i != r) {
                double C = a[i][c] / a[r][c];
                for (int j = c; j <= n; ++j) {
                    a[i][j] -= a[r][j] * C;
                }
            }
        ++r;
    }
    ans.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (pos[i] != -1) {
            ans[i] = a[pos[i]][n] / a[pos[i]][i];
        }
    }
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += ans[j] * a[i][j];
        }
        if (abs(sum - a[i][n]) > EPS) {
            return 0;
        }
    }
 
    for (int i = 0; i < n; ++i) {
        if (pos[i] == -1) {
            return INF;
        }
    }
    return 1;
}

signed main() {
    int n;
    cin >> n;
    vector<vector<double> > vect(n, vector<double>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> vect[i][j];
        }
    }

    vector<double> ans;
    int solutions = gauss(vect, ans);
    cout.precision(20);
    cout.setf(ios::fixed);

    if (solutions == 1) {
        for (auto i : ans) {
            cout << i << " ";
        }
        cout << endl;
    } else if (solutions == 0) {
        cout << "No solution" << endl;
    } else {
        cout << "INF" << endl;
    }
}
