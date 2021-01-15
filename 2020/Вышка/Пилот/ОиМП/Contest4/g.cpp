#include <tuple>
#include <stdexcept>
#include <vector>

const std::vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date{
private:
    int day, month, year;
    bool checkBissextile(int year) {
        return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
    }

    bool checkCorrectYear() {
        return year >= 1970 && year <= 2099;
    }

    bool checkCorrectMonth() {
        return month >= 1 && month <= 12;
    }

    bool checkCorrectDay() {
        return day >= 1 && day <= months[month - 1] + (month == 2 && checkBissextile(year));
    }

    void relax() {
        if (checkCorrectDay()) {
            return;
        }
        if (day == 0) {
            --month;
            if (checkCorrectMonth()) {
                day = months[month - 1] + (month == 2 && checkBissextile(year));
                return;
            }
            month = 12;
            day = months[month - 1];
            --year;
        } else {
            ++month;
            if (checkCorrectMonth()) {
                day = 1;
                return;
            }
            month = 1;
            day = 1;
            ++year;
        }
    }

public:
    Date(int _day, int _month, int _year)
        : day(_day)
        , month(_month)
        , year(_year) {
        if (!checkCorrectYear()) {
            throw std::invalid_argument("incorrect year");
        }
        if (!checkCorrectMonth()) {
            throw std::invalid_argument("incorrect month");
        }
        if (!checkCorrectDay()) {
            throw std::invalid_argument("incorrect day");
        }
    }

    int GetDay() const {
        return day;
    }

    int GetMonth() const {
        return month;
    }

    int GetYear() const {
        return year;
    }

    Date& operator++() {
        ++day;
        relax();
        return *this;
    }

    Date& operator--() {
        --day;
        relax();
        return *this;
    }

    Date operator+(int add) {
        Date ans = *this;
        if (add > 0) {
            for (int i = 0; i < add; ++i) {
                ++ans;
            }
        } else if (add < 0) {
            add = -add;
            for (int i = 0; i < add; ++i) {
                --ans;
            }
        }
        return ans;
    }

    Date operator-(int add) {
        add = -add;
        return *this + add;
    }

    int operator-(Date a) {
        int answer = 0;
        while (std::tie(a.year, a.month, a.day) < std::tie(year, month, day)) {
            ++answer;
            ++a;
        }
        while (std::tie(a.year, a.month, a.day) > std::tie(year, month, day)) {
            --answer;
            --a;
        }
        return answer;
    }
};