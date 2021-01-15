#include "classifiers.h"
#include <string>

class CombinedClassifier{
private:
    std::string hard;
    FastClassifier* fastClassifier;
    MainClassifier* mainClassifier;

public:
    CombinedClassifier(const std::string& _simple, const std::string& _hard)
        : fastClassifier(new FastClassifier(_simple))
        , hard(_hard)
        , mainClassifier(nullptr) {
    }
    double classify(const string& s) {
        double ans;
        try {
            ans = fastClassifier->classify(s);
        } catch (TooHardObjectException&) {
            if (mainClassifier == nullptr) {
                mainClassifier = new MainClassifier(hard);
            }
            ans = mainClassifier->classify(s);
        }
        return ans;
    }
    ~CombinedClassifier() {
        delete fastClassifier;
        delete mainClassifier;
    }
};