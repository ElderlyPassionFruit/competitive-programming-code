#include <iostream>
#include <string>

using namespace std;

class NotifierBase{
public:
    void Notify(const std::string& message) {
        cout << message << endl;
    }
};

void Notify(const NotifierBase& notifier, const std::string& message) {
    notifier.Notify(message);
}

int main() {
    return 0;
}