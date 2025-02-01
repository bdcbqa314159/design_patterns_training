#include <iostream>

class Context;
class State
{
public:
    Context *context = nullptr;
    State() = default;
    State(Context *context) : context(context) {}
    void setContext(Context *context) { this->context = context; }

    virtual void handle_first_type() = 0;
    virtual void handle_second_type() = 0;

    virtual std::unique_ptr<State> clone() const = 0;

    virtual ~State() = default;
};

class Context
{
public:
    std::unique_ptr<State> state;
    Context() = default;
    Context(std::unique_ptr<State> state) : state(std::move(state))
    {
        this->state->setContext(this);
    }

    void transition(std::unique_ptr<State> state)
    {
        std::cout << "changing of state...\n";
        this->state = std::move(state);
        this->state->setContext(this);
    }

    void handle_first_type()
    {
        this->state->handle_first_type();
    }

    void handle_second_type()
    {
        this->state->handle_second_type();
    }
};

class Solid : public State
{
public:
    virtual void handle_first_type() override;
    virtual void handle_second_type() override
    {
        std::cout << "solid status\n";
    }
    virtual std::unique_ptr<State> clone() const override
    {
        return std::make_unique<Solid>(*this);
    }
};

class Liquid : public State
{
public:
    virtual void handle_first_type() override
    {
        std::cout << "liquid status\n";
    }
    virtual void handle_second_type() override
    {
        this->context->transition(std::make_unique<Solid>());
    }
    virtual std::unique_ptr<State> clone() const override
    {
        return std::make_unique<Liquid>(*this);
    }
};

void Solid::handle_first_type()
{
    this->context->transition(std::make_unique<Liquid>());
}

int main()
{
    std::unique_ptr<State> liquid = std::make_unique<Liquid>();

    Context context(liquid->clone());

    context.handle_first_type();
    context.handle_second_type();
    context.handle_second_type();
    context.handle_first_type();

    return 0;
}