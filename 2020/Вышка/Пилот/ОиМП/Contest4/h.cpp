#include <tuple>
#include <stdexcept>
#include <vector>

const std::vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date{
private:
    int counter;

    bool checkBissextile(int year) const {
        return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
    }

    bool checkCorrectYear(int year) const {
        return year >= 1970 && year <= 2099;
    }

    bool checkCorrectMonth(int month) const {
        return month >= 1 && month <= 12;
    }

    bool checkCorrectDay(int day, int month, int year) const {
        return day >= 1 && day <= months[month - 1] + (month == 2 && checkBissextile(year));
    }

    int getCounter(int day, int month, int year) const {
        int answer = 0;
        int myDay = 1, myMonth = 1, myYear = 1970;
        while (day != myDay || month != myMonth || year != myYear) {
            ++myDay;
            ++answer;
            if (checkCorrectDay(myDay, myMonth, myYear)) {
                continue;
            }
            ++myMonth;
            myDay = 1;
            if (checkCorrectMonth(myMonth)) {
                continue;
            }
            ++myYear;
            myMonth = 1;
        }
        return answer;
    }

    void getData(int& day, int& month, int& year) const {
        day = 1, month = 1, year = 1970;
        for (int i = 0; i < counter; ++i) {
            ++day;
            if (checkCorrectDay(day, month, year)) {
                continue;
            }
            ++month;
            day = 1;
            if (checkCorrectMonth(month)) {
                continue;
            }
            ++year;
            month = 1;
        }
    }

public:
    Date(int day, int month, int year) {
        if (!checkCorrectYear(year)) {
            throw std::invalid_argument("incorrect year");
        }
        if (!checkCorrectMonth(month)) {
            throw std::invalid_argument("incorrect month");
        }
        if (!checkCorrectDay(day, month, year)) {
            throw std::invalid_argument("incorrect day");
        }
        counter = getCounter(day, month, year);
    }

    int GetDay() const {
        int day, month, year;
        getData(day, month, year);
        return day;
    }

    int GetMonth() const {
        int day, month, year;
        getData(day, month, year);
        return month;
    }

    int GetYear() const {
        int day, month, year;
        getData(day, month, year);
        return year;
    }

    Date& operator++() {
        ++counter;
        return *this;
    }

    Date& operator--() {
        --counter;
        return *this;
    }

    Date operator+(int add) {
        auto ans = *this;
        ans.counter += add;
        return ans;
    }

    Date operator-(int add) {
        add = -add;
        return *this + add;
    }

    int operator-(Date a) {
        return counter - a.counter;
    }
};