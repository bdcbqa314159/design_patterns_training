#include <iostream>

class SandwichOrder
{
public:
    int cost = 0;
    SandwichOrder() = default;
    virtual ~SandwichOrder() = default;
    virtual int price() const = 0;
    virtual std::string components() const = 0;
    virtual std::unique_ptr<SandwichOrder> clone() const = 0;
};

class BasicSandwich : public SandwichOrder
{
public:
    BasicSandwich()
    {
        cost = 5;
    }

    virtual int price() const override
    {
        return cost;
    }

    virtual std::string components() const override
    {
        return "basic bread and meat";
    }

    virtual std::unique_ptr<SandwichOrder> clone() const override
    {
        return std::make_unique<BasicSandwich>(*this);
    }
};

class DeluxeSandwich : public SandwichOrder
{
public:
    DeluxeSandwich()
    {
        cost = 8;
    }

    virtual int price() const override
    {
        return cost;
    }

    virtual std::string components() const override
    {
        return "organic bread, organic meat, cheese, salad";
    }

    virtual std::unique_ptr<SandwichOrder> clone() const override
    {
        return std::make_unique<DeluxeSandwich>(*this);
    }
};

class Decorator : public SandwichOrder
{
public:
    std::unique_ptr<SandwichOrder> order;

    Decorator() = default;
    Decorator(std::unique_ptr<SandwichOrder> &order)
    {
        this->order = order->clone();
    }

    virtual int price() const override
    {
        return this->order->price();
    }

    virtual std::string components() const override
    {
        return this->order->components();
    }

    virtual std::unique_ptr<SandwichOrder> clone() const override
    {
        std::unique_ptr<Decorator> out = std::make_unique<Decorator>();
        out->order = this->order->clone();
        return out;
    }
};

class CondimentDecorator : public Decorator
{

public:
    std::string condiment;
    CondimentDecorator()
    {
        cost = 1;
    }

    CondimentDecorator(std::string condiment, std::unique_ptr<SandwichOrder> &order) : condiment(condiment)
    {
        cost = 1;
        this->order = order->clone();
    }

    virtual int price() const override
    {
        return this->order->price() + cost;
    }

    virtual std::string components() const override
    {
        return this->order->components() + " and " + condiment;
    }

    virtual std::unique_ptr<SandwichOrder> clone() const override
    {
        std::unique_ptr<Decorator> out = std::make_unique<Decorator>();
        out->order = this->order->clone();
        out->cost = this->cost;
        return out;
    }
};

void serveOrder(std::unique_ptr<SandwichOrder> &order)
{
    std::cout << "Total costs: " << order->price() << "\n";
    std::cout << "Ingredients: " << order->components() << "\n";
}

int main()
{
    std::unique_ptr<SandwichOrder> sandwich = std::make_unique<BasicSandwich>();
    std::unique_ptr<SandwichOrder> decorator = std::make_unique<Decorator>(sandwich);

    serveOrder(decorator);

    decorator = std::make_unique<CondimentDecorator>("tomatoes", sandwich);
    serveOrder(decorator);

    return 0;
}