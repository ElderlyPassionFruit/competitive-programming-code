#include <iostream>

class TimeLogger{
private:
    long start_time;
public:
    TimeLogger() {
        start_time = Now();
    }
    ~TimeLogger() {
        auto elapsed_time = Now() - start_time;
        std::cout << elapsed_time << " milliseconds\n";
    }
};
