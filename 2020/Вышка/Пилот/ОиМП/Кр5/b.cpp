class Figure{
public:
    virtual ~Figure() {}
    virtual int Perimeter() const = 0;
};

class Rectangle : public Figure{
private:
    int w, h;
public:
    Rectangle(int _w, int _h)
        : w(_w)
        , h(_h) {
    }
    int Perimeter() const override {
        return 2 * (w + h);
    }
};

class Triangle : public Figure{
private:
    int a, b, c;
public:
    Triangle(int _a, int _b, int _c)
        : a(_a)
        , b(_b)
        , c(_c) {
    }
    int Perimeter() const override {
        return a + b + c;
    }
};
#include <bits/stdc++.h>
#include <iostream>

int main() {
    std::vector<Figure*> figures;

    std::string type;

    while (std::cin >> type) {
        if (type == "Triangle") {
            int a, b, c;
            std::cin >> a >> b >> c;
            figures.push_back(new Triangle(a, b, c));
        } else if (type == "Rectangle") {
            int a, b;
            std::cin >> a >> b;
            figures.push_back(new Rectangle(a, b));
        }
    }

    for (Figure * f : figures)
        std::cout << f->Perimeter() << "\n";

    for (Figure * f : figures)
        delete f;
}