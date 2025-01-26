#include <iostream>

class Action
{
public:
    virtual ~Action() = default;
    Action() = default;

    virtual void turnOn() const = 0;
    virtual void turnOff() const = 0;

    virtual std::unique_ptr<Action> clone() const = 0;
};

class Alarm : public Action
{
public:
    virtual void turnOn() const override
    {
        std::cout << "Alarm on\n";
    }

    virtual void turnOff() const override
    {
        std::cout << "Alarm off\n";
    }

    virtual std::unique_ptr<Action> clone() const override
    {

        return std::make_unique<Alarm>(*this);
    }
};

class Heat : public Action
{
public:
    virtual void turnOn() const override
    {
        std::cout << "Heat on\n";
    }

    virtual void turnOff() const override
    {
        std::cout << "Heat off\n";
    }

    virtual std::unique_ptr<Action> clone() const override
    {

        return std::make_unique<Heat>(*this);
    }
};

class TV : public Action
{
public:
    virtual void turnOn() const override
    {
        std::cout << "TV on\n";
    }

    virtual void turnOff() const override
    {
        std::cout << "TV off\n";
    }

    virtual std::unique_ptr<Action> clone() const override
    {

        return std::make_unique<TV>(*this);
    }
};

class HouseHold
{

public:
    std::unique_ptr<Action> alarm = std::make_unique<Alarm>();
    std::unique_ptr<Action> heat = std::make_unique<Heat>();
    std::unique_ptr<Action> tv = std::make_unique<TV>();

    HouseHold() = default;
    ~HouseHold() = default;

    HouseHold(std::unique_ptr<Action> &alarm, std::unique_ptr<Action> &heat, std::unique_ptr<Action> &tv)
    {
        this->alarm = alarm->clone();
        this->heat = heat->clone();
        this->tv = tv->clone();
    }

    void goToWork()
    {
        std::cout << "going to work, we need to:\n";
        heat->turnOff();
        tv->turnOff();
        alarm->turnOn();
    }

    void comeHome()
    {
        std::cout << "coming back home, we need to:\n";
        heat->turnOn();
        tv->turnOn();
        alarm->turnOff();
    }
};

int main()
{
    HouseHold house;
    house.goToWork();
    house.comeHome();
    return 0;
}