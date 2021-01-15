#include <assert.h>
#include <cmath>
#include <iostream>
#include <numeric>

class Rational{
private:
    int _numerator, _denominator;

public:
    Rational() {
        _numerator = 0;
        _denominator = 1;
    }
    Rational(int numerator_, int denominator_) {
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
