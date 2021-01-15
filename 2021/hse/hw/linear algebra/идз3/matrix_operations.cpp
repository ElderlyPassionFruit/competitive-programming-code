#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Matrix{
    vector<vector<int>> a;
    Matrix() {}
    Matrix(vector<vector<int>> _a) : a(_a) {}
    Matrix(int n, int m) {
        a.assign(n, vector<int> (m, 0));
    }

    Matrix operator+(const Matrix& add) {
        Matrix ans = *this;
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[i].size(); ++j) {
                ans.a[i][j] += add.a[i][j];
            }
        }
        return ans;
    }

    Matrix operator-(const Matrix& add) {
        Matrix ans = *this;
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[i].size(); ++j) {
                ans.a[i][j] -= add.a[i][j];
            }
        }
        return ans;
    }

    Matrix operator*(int d) {
        Matrix ans = *this;
        for (auto& i : ans.a) {
            for (auto& j : i) {
                j *= d;
            }
        }
        return ans;
    } 

    Matrix operator*(const Matrix& mul) {
        Matrix ans(a.size(), mul.a[0].size());
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < mul.a[0].size(); ++j) {
                for (int k = 0; k < a[i].size(); ++k) {
                    ans.a[i][j] += a[i][k] * mul.a[k][j];
                }
            }
        }
        return ans;
    }

    Matrix Trans() {
        Matrix ans(a[0].size(), a.size());
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[0].size(); ++j) {
                ans.a[j][i] = a[i][j]; 
            }
        }
        return ans;
    }

    int tr() {
        int ans = 0;
        for (int i = 0; i < a.size(); ++i) {
            ans += a[i][i];
        }
        return ans;
    }

    void write() {
        for (auto i : a) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

/*

№1
 vector<vector<int>> A = {
        {1, -3, 2},
        {-6, -4, 5}
    };
    vector<vector<int>> B = {
        {-1, -4, 6},
        {2, -3, 2}
    };
    vector<vector<int>> C = {
        {6, 2},
        {-4, -1}
    };
    vector<vector<int>> D = {
        {6, -5},
        {-2, 3}
    };
    Matrix a(A), b(B), c(C), d(D);
    //Matrix ra = a.Trans();
    //a.write();
    //ra.write();
    Matrix a1 = a * a.Trans() * c * (-6);
    a1.write();
    Matrix a2 = (a - b) * (a.Trans() + b.Trans()) * (b.Trans() * B).tr();
    a2.write();
    Matrix a3 = c * c * (-5);
    a3.write();
    Matrix a4 = c * d * 10;
    a4.write();
    Matrix a5 = d * d * (-5);
    a5.write();
    cout << "ans = " << endl;
    (a1 + a2 + a3 + a4 + a5).write();

*/

void E1(vector<vector<int>>& matrix, int i, int j, int lambda) {
    for (int x = 0; x < matrix[0].size(); ++x) {
        matrix[i - 1][x] += matrix[j - 1][x] * lambda;
    }
}

void E2(vector<vector<int>>& matrix, int i, int j) {
    swap(matrix[i - 1], matrix[j - 1]);
}

void E3(vector<vector<int>>& matrix, int i, int lambda) {
    for (int x = 0; x < matrix[i - 1].size(); ++x) {
        matrix[i - 1][x] *= lambda;
    }
}

void e3(vector<vector<int>>& matrix, int i, int lambda) {
    for (int x = 0; x < matrix[i - 1].size(); ++x) {
        matrix[i - 1][x] /= lambda;
    }
}


void wr(vector<vector<int>> matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << matrix[i][j] << " ";
            if (j == 3) cout << "| ";
        }
        cout << endl;
    }
    cout << endl;
}
/*
    vector<vector<int>> matrix = {
        {-4, -6,  4, -1, 1, 0, 0, 0},
        { 3,  4, -6,  3, 0, 1, 0, 0},
        {-2, -5, -2,  3, 0, 0, 1, 0},
        { 0, -1, -1,  1, 0, 0, 0, 1}
    };
    wr(matrix);
    E1(matrix, 3, 1, -2);
    E3(matrix, 2, 2);
    E1(matrix, 3, 2, 3);
    wr(matrix);
    E2(matrix, 1, 3);
    E2(matrix, 2, 4);
    wr(matrix);
    E1(matrix, 2, 3, 4);
    E1(matrix, 2, 4, -7);
    wr(matrix);
    E3(matrix, 4, 4);
    E1(matrix, 3, 4, 11);
    wr(matrix);
    E3(matrix, 4, -1);
    E1(matrix, 4, 3, 3);
    E1(matrix, 4, 2, -1);
    E1(matrix, 4, 1, -3);
    wr(matrix);
    e3(matrix, 3, 4);
    E1(matrix, 3, 2, 1);
    E1(matrix, 3, 1, 2);
    wr(matrix);
    E3(matrix, 2, -1);
    E1(matrix, 2, 1, 5);
    e3(matrix, 1, -2);
    wr(matrix);

    vector<vector<int>> myMatrix = {
        {-4, -6,  4, -1},
        { 3,  4, -6,  3},
        {-2, -5, -2,  3},
        { 0, -1, -1,  1}
    };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i].erase(matrix[i].begin());
        }
    }
    (Matrix(matrix) * Matrix(myMatrix)).write();
*/

/*

vector<vector<int>> matrix = {
        {8, 0, 0, 11, 0, -8},
        {0, 8, -3, -7, 9, 3},
        {7, 2, -7, 0, 0, 0}
    };
    E3(matrix, 3, -8);
    E1(matrix, 1, 3, 7);
    for (auto i : matrix) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    E1(matrix, 2, 3, 2);
    for (auto i : matrix) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    E3(matrix, 2, 50);
    E1(matrix, 3, 2, 3);
    for (auto i : matrix) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;

*/

/*
    vector<vector<int>> a = {
        {20, -4, 3, -1, -95, 45, 76},
        {22, -7, 4, 2, -118, 41, 94},
        {5, -2, 1, 2, -31, 7, 23}
    };
    print(a);
    E3(a, 3, 4);
    E1(a, 1, 3, -1);
    E1(a, 1, 2, -1);
    print(a);
    E1(a, 2, 1, -10);
    E2(a, 1, 2);
    E1(a, 3, 2, 6);
    print(a);
    E1(a, 2, 3, 2);
    E1(a, 3, 2, -1);
    e3(a, 2, 2);
    print(a);
    E1(a, 3, 1, 1);
    E1(a, 2, 1, 3);
    e3(a, 1, 2);
    e3(a, 3, -1);
    print(a);*/

void e2(vector<vector<int>>& matrix, int I, int J) {
    for (int i = 0; i < matrix.size(); ++i) {
        swap(matrix[i][I - 1], matrix[i][J - 1]);
    }
}

void print(vector<vector<int>> a) {
    for (auto i : a) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void read() {
    cout << "L1 = " << endl;
    vector<vector<int>> a = {
        {1, -21, 3, 1},
        {4, 3, -3, 1},
        {-6, -19, 7, -1},
        {3, -5, -1, 1}
    };
    print(a);
    E1(a, 2, 1, -4);
    E1(a, 4, 1, -3);
    E1(a, 3, 1, 6);
    print(a);
    e3(a, 2, 3);
    e3(a, 4, 2);
    e3(a, 3, 5);
    print(a);
    E1(a, 3, 2, 1);
    E1(a, 4, 2, -1);
    print(a);
    cout << "L2 = " << endl;
    vector<vector<int>> b = {
        {4, 5, -3, -1},
        {3, -4, -1, 0},
        {2, -13, 1, 1},
        {-1, 22, -3, -2}
    };
    print(b);
    E2(b, 1, 4);
    print(b);
    E1(b, 2, 1, 3);
    E1(b, 4, 1, 4);
    E1(b, 3, 1, 2);
    print(b);
    e3(b, 2, 2);
    e3(b, 4, 3);
    print(b);
    E1(b, 3, 2, -1);
    E1(b, 4, 2, -1);
    print(b);
    vector<vector<int>> c = {a[0], a[1], b[0], b[1]};
    cout << "L1 and L2 = " << endl;
    print(c);
    E1(c, 3, 1, 1);
    E3(c, 3, 29);
    print(c);
    E1(c, 3, 2, -1);
    print(c);
    E3(c, 4, 29);
    print(c);
    E1(c, 4, 2, -31);
    print(c);
    E1(c, 4, 3, -2);
    print(c);
    vector<vector<int>> v1 = {a[0], a[1]};
    cout << "v = " << endl;
    print(v1);
    E3(v1, 1, -2);
    // E3(v1, 2, 29);
    E1(v1, 1, 2, -1);
    print(v1);
    vector<vector<int>> u1 = {b[0], b[1]};
    cout << "u = " << endl;
    print(u1);
    E3(u1, 1, 2);
    // E3(u1, 2, 29);
    E1(u1, 1, 2, -1);
    print(u1);
}

void run() {

}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
    read();
    run();
    write();
    return 0;
}