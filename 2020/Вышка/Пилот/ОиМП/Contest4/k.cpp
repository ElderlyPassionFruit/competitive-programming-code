#include <algorithm>
#include <vector>

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

    Polynomial& operator+=(const Polynomial& a) {
        *this = *this + a;
        return *this;
    }

    Polynomial& operator-=(const Polynomial& a) {
        *this = *this - a;
        return *this;
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
};