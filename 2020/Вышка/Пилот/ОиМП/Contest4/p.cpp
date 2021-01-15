#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

template<typename T>
class Polynomial{
private:
    std::map<int, T> coefficients;
    void relax() {
        while (!coefficients.empty() && (--coefficients.end())->second == T(0)) {
            coefficients.erase(--coefficients.end());
        }
    }

public:
    Polynomial(const std::vector<T> _helpCoefficients)
        : coefficients() {
        for (size_t i = 0; i < _helpCoefficients.size(); ++i) {
            if (_helpCoefficients[i] != T(0)) {
                coefficients[i] = _helpCoefficients[i];
            }
        }
        relax();
    }

    Polynomial(T x = T(0))
        : coefficients() {
        coefficients[0] = x;
        relax();
    }

    template<typename Iterator>
    Polynomial(Iterator first, Iterator last)
        : coefficients() {
        for (int i = 0; first != last; ++first, ++i) {
            if (*first != T(0)) {
                coefficients[i] = *first;
            }
        }
        relax();
    }

    Polynomial(const std::map<int, T>& _coefficients)
        : coefficients(_coefficients) {
        if (coefficients.empty()) {
            return;
        }
        relax();
    }

    bool operator==(const Polynomial& a) const {
        return coefficients == a.coefficients;
    }

    bool operator!=(const Polynomial& a) const {
        return coefficients != a.coefficients;
    }

    Polynomial operator+(const Polynomial& a) const {
        std::map<int, T> answer = coefficients;
        for (const auto& i : a.coefficients) {
            answer[i.first] += i.second;
            if (answer[i.first] == T(0)) {
                answer.erase(i.first);
            }
        }
        return Polynomial(answer);
    }

    Polynomial operator-(const Polynomial& a) const {
        std::map<int, T> answer = coefficients;
        for (const auto& i : a.coefficients) {
            answer[i.first] -= i.second;
            if (answer[i.first] == T(0)) {
                answer.erase(i.first);
            }
        }
        return Polynomial(answer);
    }

    Polynomial& operator+=(const Polynomial& a) {
        *this = *this + a;
        return *this;
    }

    Polynomial& operator-=(const Polynomial& a) {
        *this = *this - a;
        return *this;
    }

    Polynomial operator*(const Polynomial& a) const {
        std::map<int, T> answer;
        for (const auto& i : coefficients) {
            for (const auto& j : a.coefficients) {
                answer[i.first + j.first] += i.second * j.second;
                if (answer[i.first + j.first] == T(0)) {
                    answer.erase(i.first + j.first);
                }
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
        int deg = Degree();
        for (int i = 0; i <= deg; ++i) {
            auto it = coefficients.find(i);
            if (it != coefficients.end()) {
                answer += power * it->second;
            }
            power *= a;
        }
        return answer;
    }

    int Degree() const {
        if (coefficients.empty()) {
            return -1;
        }
        return (--coefficients.end())->first;
    }

    T operator[](int x) const {
        if (Degree() < x || x < 0) {
            return T(0);
        }
        auto it = coefficients.find(x);
        if (it == coefficients.end()) {
            return T(0);
        }
        return it->second;
    }

    Polynomial operator&(const Polynomial& a) const {
        Polynomial answer;
        Polynomial forMul(T(1));
        for (int i = 0; i <= Degree(); ++i) {
            auto it = coefficients.find(i);
            if (it != coefficients.end()) {
                answer += forMul * Polynomial(it->second);
            }
            forMul *= a;
        }
        return answer;
    }

    Polynomial operator/(const Polynomial& a) const {
        if (a.Degree() > Degree()) {
            return Polynomial();
        }
        Polynomial now = *this;

        std::map<int, T> answer;

        for (int it = now.Degree(); it >= a.Degree(); --it) {
            auto add = now[it] / a[a.Degree()];
            if (add == T(0)) {
                continue;
            }
            answer[it - a.Degree()] = add;
            std::map<int, T> forAns;
            forAns[it - a.Degree()] = add;
            now -= a * Polynomial(forAns);
        }
        return Polynomial(answer);
    }

    Polynomial operator%(const Polynomial& a) const {
        return *this - *this / a * a;
    }

    Polynomial operator,(Polynomial a) const {
        Polynomial b = *this;
        while (b != Polynomial()) {
            a = a % b;
            std::swap(a, b);
        }
        a = a / a[a.Degree()];
        return a;
    }

    auto begin() const {
        return coefficients.cbegin();
    }

    auto end() const {
        return coefficients.cend();
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
            auto myA = a[i];
            if (myA == T(0)) {
                continue;
            }
            forOutput(out, a[i], deg == i, i);
        }
    }
    return out;
}