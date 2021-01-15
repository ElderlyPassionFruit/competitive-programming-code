#include <string>
#include <string_view>

bool NextToken(std::string_view& sv, char delimiter, std::string_view& token) {
    if (sv.empty()) return false;
    auto pos = sv.find(delimiter);
    if (pos == std::string_view::npos) {
        token = sv;
        sv = "";
        return true;
    }
    token = sv.substr(0, pos);
    sv = sv.substr(pos + 1, sv.size() - pos - 1);
    return true;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    string_view sv = "Hello world and good bye";
    const char delimiter = ' ';
    string_view token;
    while (NextToken(sv, delimiter, token)) {
        // обрабатываем очередной token
        // например, печатаем его на экране:
        cout << token << "\n";
        //cout << sv << endl;
        //break;
    }

    return 0;
}