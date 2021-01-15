class NotifierBase{
public:
    virtual void Notify(const std::string& message) const = 0;
};

class SmsNotifier: public NotifierBase{
private:
    std::string number;
public:
    SmsNotifier(const std::string& _number) : number(_number) {};
    void Notify(const std::string& message) const override {
        SendSms(number, message);
    }
};

class EmailNotifier: public NotifierBase{
private:
    std::string email;
public:
    EmailNotifier(const std::string& _email) : email(_email) {};
    void Notify(const std::string& message) const override {
        SendEmail(email, message);
    }
};