#include <bits/stdc++.h>

using namespace std;

class Rational{
private:
    int _numerator, _denominator;

public:
    Rational() {
        _numerator = 0;
        _denominator = 1;
    }
    Rational(int numerator_, int denominator_ = 1) {
        _numerator = numerator_;
        _denominator = denominator_;
        assert(_denominator != 0);
        int myGcd = std::gcd(abs(_numerator), abs(_denominator));
        _numerator /= myGcd;
        _denominator /= myGcd;
        if (_denominator < 0) {
            _numerator = -_numerator;
            _denominator = -_denominator;
        }
    }

    int numerator() const {
        return _numerator;
    }

    int denominator() const {
        return _denominator;
    }

    Rational operator+(const Rational& a) const {
        return Rational(_numerator * a.denominator() + a.numerator() * _denominator,
            a.denominator() * _denominator);
    }

    Rational operator+(int a) const {
        return *this + Rational(a, 1);
    }

    Rational operator-(const Rational& a) const {
        return Rational(_numerator * a.denominator() - a.numerator() * _denominator,
            a.denominator() * _denominator);
    }

    Rational operator-(int a) const {
        return *this - Rational(a, 1);
    }

    Rational operator*(const Rational& a) const {
        return Rational(_numerator * a.numerator(), _denominator * a.denominator());
    }

    Rational operator*(int a) const {
        return *this * Rational(a, 1);
    }

    Rational operator/(const Rational& a) const {
        return *this * Rational(a.denominator(), a.numerator());
    }

    Rational operator/(int a) const {
        return *this / Rational(a, 1);
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-_numerator, _denominator);
    }

    Rational& operator+=(const Rational& a) {
        *this = *this + a;
        return *this;
    }

    Rational& operator+=(int a) {
        *this = *this + a;
        return *this;
    }

    Rational& operator-=(const Rational& a) {
        *this = *this - a;
        return *this;
    }

    Rational& operator-=(int a) {
        *this = *this - a;
        return *this;
    }

    Rational& operator*=(const Rational& a) {
        *this = *this * a;
        return *this;
    }

    Rational& operator*=(int a) {
        *this = *this * a;
        return *this;
    }

    Rational& operator/=(const Rational& a) {
        *this = *this / a;
        return *this;
    }

    Rational& operator/=(int a) {
        *this = *this / a;
        return *this;
    }

    bool operator==(const Rational& a) const {
        return a.numerator() == _numerator && a.denominator() == _denominator;
    }

    bool operator==(int a) const {
        return *this == Rational(a, 1);
    }

    bool operator!=(const Rational& a) const {
        return a.numerator() != _numerator || a.denominator() != _denominator;
    }

    bool operator!=(int a) const {
        return *this != Rational(a, 1);
    }

    Rational& operator++() {
        *this += 1;
        return *this;
    }

    Rational operator++(int) {
        auto temp = *this;
        *this += 1;
        return temp;
    }

    Rational& operator--() {
        *this -= 1;
        return *this;
    }

    Rational operator--(int) {
        auto temp = *this;
        *this -= 1;
        return temp;
    }
};

Rational operator+(int a, const Rational& b) {
    return b + a;
}

Rational operator-(int a, const Rational& b) {
    return b - a;
}

Rational operator*(int a, const Rational& b) {
    return b * a;
}

Rational operator/(int a, const Rational& b) {
    return Rational(a, 1) / b;
}

bool operator==(int a, const Rational& b) {
    return b == a;
}

bool operator!=(int a, const Rational& b) {
    return b != a;
}

using matrix = vector<vector<Rational>>;

matrix gaussDown(matrix a) {
    int n = a.size();
    int m = a[0].size();
    int lastRaw = 0;
    for (int col = 0; col < m; ++col) {
        bool ok = false;
        for (int raw = lastRaw; raw < n; ++raw) {
            if (a[raw][col] != 0) {
                ok = true;
                swap(a[raw], a[lastRaw]);
                break;
            }
        }
        if (!ok) continue;
        for (int nxtRaw = lastRaw + 1; nxtRaw < n; ++nxtRaw) {
            if (a[nxtRaw][col] != 0) {
                auto myCoeff = a[nxtRaw][col];
                auto nxtCoeff = a[lastRaw][col];
                for (int nxtCol = col; nxtCol < m; ++nxtCol) {
                    a[nxtRaw][nxtCol] = a[nxtRaw][nxtCol] * nxtCoeff - a[lastRaw][nxtCol] * myCoeff;
                }
            }
        }
        ++lastRaw;
    }
    return a;
}

int main() {
    return 0;

}