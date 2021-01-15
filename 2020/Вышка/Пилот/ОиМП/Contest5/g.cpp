#include "tokenizer.h"
#include <iostream>
#include <string>

class myCallbackBase: public CallbackBase{
public:
    int cntTokens;
    size_t maxSize;
    myCallbackBase() {
        cntTokens = 0;
        maxSize = 0;
    }
    void OnToken(const char*, size_t length) override {
        ++cntTokens;
        if (length > maxSize) {
            maxSize = length;
        }
    }
};

int main() {
    std::string text;
    std::getline(std::cin, text);
    Tokenizer tokenizer;
    myCallbackBase ans;
    CallbackBase* myCallback = &ans;
    tokenizer.Tokenize(text, myCallback);
    std::cout << ans.cntTokens << ' ' << ans.maxSize << '\n';
    return 0;
}
