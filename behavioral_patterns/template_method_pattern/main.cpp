#include <iostream>

class CoffeeMaker
{

public:
    void makingCoffee()
    {
        start();
        pouring();
        serving();
        type();
        size();
        milk();
        chocolate();
    }

    void start() const
    {
        std::cout << "turning the machine on...\n";
    }

    void pouring() const
    {
        std::cout << "pouring coffee...\n";
    }

    void serving() const
    {
        std::cout << "serving coffee...\n";
    }

    virtual void type() const = 0;
    virtual void size() const = 0;

    virtual void milk() const {}
    virtual void chocolate() const {}
};

class LargeCoffee : public CoffeeMaker
{

public:
    virtual void type() const = 0;

    virtual void size() const
    {
        std::cout << "large coffee...\n";
    }

    virtual void milk() const {}
    virtual void chocolate() const {}
};

class SmallCoffee : public CoffeeMaker
{

public:
    virtual void type() const = 0;

    virtual void size() const
    {
        std::cout << "small coffee...\n";
    }

    virtual void milk() const {}
    virtual void chocolate() const {}
};

class LargeAmericano : public LargeCoffee
{

    virtual void type() const
    {
        std::cout << "americano\n";
    }
};

class LargeLatte : public LargeCoffee
{

    virtual void type() const
    {
        std::cout << "latte\n";
    }
};

class LargeLatteOatMilk : public LargeLatte
{

    virtual void type() const
    {
        std::cout << "latte\n";
    }

    virtual void milk() const
    {
        std::cout << "oat milk\n";
    }
};

int main()
{
    LargeAmericano coffee1;
    LargeLatteOatMilk coffee2;

    std::cout << "=== large americano ===\n";
    coffee1.makingCoffee();

    std::cout << "=== large oat milk latte ===\n";
    coffee2.makingCoffee();

    return 0;
}