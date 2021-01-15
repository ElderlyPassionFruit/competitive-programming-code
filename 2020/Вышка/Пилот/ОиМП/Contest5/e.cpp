//#include "quadrature.h"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

template <typename F>
class IntegrationMethod{
public:
    IntegrationMethod() {}
    virtual double Integrate(F f, double x, double y, int n) = 0;
};

template <typename F>
class RectangleRule: public IntegrationMethod<F>{
private:
    double getX(double a, double b, int n, int k) {
        return a + (b - a) * k / n;
    }
public:
    virtual double Integrate(F f, double x, double y, int n) {
        double answer = 0;
        for (int i = 0; i < n; ++i) {
            double now = getX(x, y, n, i);
            double nxt = getX(x, y, n, i + 1);
            double arg = (now + nxt) / 2.0;
            answer += f(arg) * (nxt - now);
        }
        return answer;
    }
};

template <typename F>
class TrapezoidalRule: public IntegrationMethod<F>{
private:
    double getX(double a, double b, int n, int k) {
        return a + (b - a) * k / n;
    }
public:
    virtual double Integrate(F f, double x, double y, int n) {
        double answer = 0;
        for (int i = 0; i < n; ++i) {
            double now = getX(x, y, n, i);
            double nxt = getX(x, y, n, i + 1);
            answer += (f(now) + f(nxt)) * (nxt - now);
        }
        return answer / 2.0;
    }
};

int main() {
    using F = decltype(cos);

    std::string input;
    std::cin >> input;
    std::unique_ptr<IntegrationMethod<F>> method;
    if (input == "rectangle")
        method.reset(new RectangleRule<F>);
    else
        method.reset(new TrapezoidalRule<F>);

    double x, y;
    std::cin >> x >> y;

    int n;
    std::cin >> n;

    std::cout << method->Integrate(cos, x, y, n) << "\n";
    std::cout << method->Integrate(sin, x, y, n) << "\n";
}