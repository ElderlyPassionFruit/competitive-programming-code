#include <exception>
#include <functional>
#include <optional>

template <typename Result, typename Exception = std::exception>
std::optional<Result> DoWithRetry(
    std::function<Result()> func,
    int retryCount,
    int sleepTime,
    bool throwLast) {
    for (int it = 0; it <= retryCount; ++it) {
        Result result;
        try {
            result = func();
        } catch (Exception& a) {
            if (it != retryCount) {
                Sleep(sleepTime);
                continue;
            }
            if (throwLast) {
                throw a;
            } else {
                return  std::nullopt;
            }
        }
        return result;
    }
}

int main() {

}