#include <iostream>

class Action
{

public:
    Action() = default;
    virtual ~Action() = default;

    virtual void turn() const = 0;
    virtual std::unique_ptr<Action> clone() const = 0;
};

class Trigger
{
public:
    std::unique_ptr<Action> myAction;
    Trigger() = default;
    Trigger(std::unique_ptr<Action> anAction) : myAction(std::move(anAction)) {}
    void setAction(std::unique_ptr<Action> &anAction)
    {
        myAction = anAction->clone();
    }

    void turn() const
    {
        myAction->turn();
    }
};

class TurnRight : public Action
{
    virtual void turn() const override
    {
        std::cout << "turning right...\n";
    }

    virtual std::unique_ptr<Action> clone() const override
    {
        return std::make_unique<TurnRight>(*this);
    }
};

class TurnLeft : public Action
{
    virtual void turn() const override
    {
        std::cout << "turning left...\n";
    }

    virtual std::unique_ptr<Action> clone() const override
    {
        return std::make_unique<TurnLeft>(*this);
    }
};

int main()
{
    std::unique_ptr<Action> turning = std::make_unique<TurnRight>();
    std::unique_ptr<Trigger> trigger = std::make_unique<Trigger>(turning->clone());
    trigger->turn();
    turning = std::make_unique<TurnLeft>();
    trigger->setAction(turning);
    trigger->turn();

    return 0;
}