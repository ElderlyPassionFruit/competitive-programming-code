#include <algorithm>
#include <cmath>

class Complex{
private:
    double realPart;
    double imaginaryPart;

public:
    Complex(double _realPart)
        : realPart(_realPart)
        , imaginaryPart(0) {
    }

    Complex(double _realPart, double _imaginaryPart)
        : realPart(_realPart)
        , imaginaryPart(_imaginaryPart) {
    }

    Complex operator+(const Complex& add) const {
        return Complex(realPart + add.realPart, imaginaryPart + add.imaginaryPart);
    }

    Complex operator+(const double add) const {
        return *this + Complex(add);
    }

    Complex operator-(const Complex& add) const {
        return Complex(realPart - add.realPart, imaginaryPart - add.imaginaryPart);
    }

    Complex operator-(const double add) const {
        return *this - Complex(add);
    }

    Complex operator*(const Complex& mult) const {
        return Complex(
            realPart * mult.realPart - imaginaryPart * mult.imaginaryPart,
            imaginaryPart * mult.realPart + realPart * mult.imaginaryPart);
    }

    Complex operator*(const double mult) const {
        return *this * Complex(mult);
    }

    Complex operator/(const Complex& division) const {
        double denominator =
            division.realPart * division.realPart +
            division.imaginaryPart * division.imaginaryPart;
        return Complex(
            (realPart * division.realPart + imaginaryPart * division.imaginaryPart) / denominator,
            (imaginaryPart * division.realPart - realPart * division.imaginaryPart) / denominator);
    }

    double Re() const {
        return realPart;
    }

    double Im() const {
        return imaginaryPart;
    }

    Complex operator-() const {
        return Complex(-realPart, -imaginaryPart);
    }

    Complex operator+() const {
        return *this;
    }

    bool operator==(const Complex& a) const {
        return realPart == a.Re() && imaginaryPart == a.Im();
    }

    bool operator!=(const Complex& a) const {
        return !(*this == a);
    }
};

Complex operator*(const double mult, const Complex& a) {
    return a * mult;
}

double abs(const Complex& a) {
    return std::sqrt(a.Re() * a.Re() + a.Im() * a.Im());
}
