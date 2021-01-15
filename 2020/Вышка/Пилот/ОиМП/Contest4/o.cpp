#include <algorithm>
#include <assert.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

template<typename T>
class Polynomial{
private:
    std::vector<T> coefficients;
    void relax() {
        while (!coefficients.empty() && coefficients.back() == T(0)) {
            coefficients.pop_back();
        }
    }

public:
    Polynomial(const std::vector<T> _coefficients)
        : coefficients(_coefficients) {
        relax();
    }

    Polynomial(T x = T(0))
        : coefficients(1, x) {
        relax();
    }

    template<typename Iterator>
    Polynomial(Iterator first, Iterator last)
        : coefficients(first, last) {
        relax();
    }

    bool operator==(const Polynomial& a) const {
        return coefficients == a.coefficients;
    }

    bool operator!=(const Polynomial& a) const {
        return coefficients != a.coefficients;
    }

    Polynomial operator+(const Polynomial& a) const {
        std::vector<T> answer(std::max(coefficients.size(), a.coefficients.size()), T(0));
        for (size_t i = 0; i < answer.size(); ++i) {
            if (i < coefficients.size()) {
                answer[i] += coefficients[i];
            }
            if (i < a.coefficients.size()) {
                answer[i] += a.coefficients[i];
            }
        }
        return Polynomial(answer);
    }

    Polynomial& operator+=(const Polynomial& a) {
        *this = *this + a;
        return *this;
    }

    Polynomial operator-(const Polynomial& a) const {
        std::vector<T> answer(std::max(coefficients.size(), a.coefficients.size()), T(0));
        for (size_t i = 0; i < answer.size(); ++i) {
            if (i < coefficients.size()) {
                answer[i] += coefficients[i];
            }
            if (i < a.coefficients.size()) {
                answer[i] -= a.coefficients[i];
            }
        }
        return Polynomial(answer);
    }

    Polynomial& operator-=(const Polynomial& a) {
        *this = *this - a;
        return *this;
    }

    Polynomial operator*(const Polynomial& a) const {
        std::vector<T> answer(coefficients.size() + a.coefficients.size(), T(0));
        for (size_t i = 0; i < coefficients.size(); ++i) {
            for (size_t j = 0; j < a.coefficients.size(); ++j) {
                answer[i + j] += coefficients[i] * a.coefficients[j];
            }
        }
        return Polynomial(answer);
    }

    Polynomial& operator*=(const Polynomial& a) {
        *this = *this * a;
        return *this;
    }

    T operator()(T a) const {
        T answer = T(0);
        T power = T(1);
        for (auto i : coefficients) {
            answer += power * i;
            power *= a;
        }
        return answer;
    }

    int Degree() const {
        return static_cast<int32_t>(coefficients.size()) - 1;
    }

    T operator[](int x) const {
        if (Degree() < x || x < 0) {
            return T(0);
        }
        return coefficients[x];
    }

    auto begin() const {
        return coefficients.cbegin();
    }

    auto end() const {
        return coefficients.cend();
    }

    Polynomial operator&(const Polynomial& a) const {
        Polynomial answer;
        Polynomial forMul(T(1));
        for (size_t i = 0; i < coefficients.size(); ++i) {
            answer += forMul * Polynomial<T>(coefficients[i]);
            forMul *= a;
        }
        return answer;
    }

    Polynomial operator/(const Polynomial& a) const {
        if (a.Degree() > Degree()) {
            return Polynomial();
        }
        Polynomial now = *this;
        std::vector<T> answer;
        std::vector<T> forAns(now.Degree() - a.Degree() + 1);

        for (int it = now.Degree(); it >= a.Degree(); --it) {
            auto add = now[it] / a[a.Degree()];
            if (add == T(0)) {
                forAns.pop_back();
                answer.push_back(T(0));
                continue;
            }
            answer.push_back(add);
            forAns.pop_back();
            forAns.push_back(add);
            now -= a * Polynomial(forAns);
            forAns.pop_back();
        }
        std::reverse(answer.begin(), answer.end());
        return Polynomial(answer);
    }

    Polynomial operator%(const Polynomial& a) const {
        if (a.Degree() > Degree()) {
            return *this;
        }
        Polynomial now = *this;
        std::vector<T> forAns(now.Degree() - a.Degree() + 1);

        for (int it = now.Degree(); it >= a.Degree(); --it) {
            auto add = now[it] / a[a.Degree()];
            if (add == T(0)) {
                forAns.pop_back();
                continue;
            }
            forAns.pop_back();
            forAns.push_back(add);
            now -= a * Polynomial(forAns);
            forAns.pop_back();
        }
        return now;
    }

    Polynomial operator,(Polynomial a) const {
        Polynomial b = *this;
        while (b != Polynomial()) {
            a = a % b;
            std::swap(a, b);
        }
        a = a / (*--a.end());
        return a;
    }
};

template<typename T>
void forOutput(std::ostream& out, const T& a, bool first, int deg) {
    if (a == T(0)) {
        assert(!first);
    } else if (a > T(0)) {
        if (!first) {
            out << "+";
        }
        if (a != T(1) || deg == 0) {
            out << a;
            if (deg != 0) {
                out << "*";
            }
        }
        if (deg > 1) {
            out << "x^" << deg;
        } else if (deg == 1) {
            out << "x";
        }
    } else {
        if (a != T(-1) || deg == 0) {
            out << a;
            if (deg != 0) {
                out << "*";
            }
        } else {
            out << "-";
        }
        if (deg > 1) {
            out << "x^" << deg;
        } else if (deg == 1) {
            out << "x";
        }
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& a) {
    if (a.Degree() == -1) {
        out << 0;
    } else {
        int deg = a.Degree();
        for (int i = deg; i >= 0; i--) {
            forOutput(out, a[i], deg == i, i);
        }
    }
    return out;
}
