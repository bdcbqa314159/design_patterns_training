#include <iostream>

class DrinkPreparation
{
public:
    virtual ~DrinkPreparation() = default;

    virtual void prepare() const = 0;
    virtual std::unique_ptr<DrinkPreparation> clone() const = 0;
};

class DrinkContainer
{
public:
    virtual ~DrinkContainer() = default;

    virtual void serve() const = 0;
    virtual std::unique_ptr<DrinkContainer> clone() const = 0;
};

class Drink
{
public:
    std::unique_ptr<DrinkPreparation> thePreparation;
    std::unique_ptr<DrinkContainer> theContainer;

    Drink() = default;
    ~Drink() = default;

    Drink(std::unique_ptr<DrinkPreparation> &preparation, std::unique_ptr<DrinkContainer> &container)
    {
        thePreparation = preparation->clone();
        theContainer = container->clone();
    }

    void prepare()
    {
        thePreparation->prepare();
    }

    void serve()
    {
        theContainer->serve();
    }
};

class Glass : public DrinkContainer
{
public:
    virtual void serve() const override
    {
        std::cout << "serving in a glass...\n";
    }

    virtual std::unique_ptr<DrinkContainer> clone() const override
    {
        return std::make_unique<Glass>(*this);
    }
};

class Mug : public DrinkContainer
{
public:
    virtual void serve() const override
    {
        std::cout << "serving in a mug...\n";
    }

    virtual std::unique_ptr<DrinkContainer> clone() const override
    {
        return std::make_unique<Mug>(*this);
    }
};

class Jar : public DrinkContainer
{
public:
    virtual void serve() const override
    {
        std::cout << "serving in a jar...\n";
    }

    virtual std::unique_ptr<DrinkContainer> clone() const override
    {
        return std::make_unique<Jar>(*this);
    }
};

class Coffee : public DrinkPreparation
{
public:
    virtual void prepare() const override
    {
        std::cout << "preparing coffee\n";
    }

    virtual std::unique_ptr<DrinkPreparation> clone() const override
    {
        return std::make_unique<Coffee>(*this);
    }
};

class Juice : public DrinkPreparation
{
public:
    virtual void prepare() const override
    {
        std::cout << "preparing juice\n";
    }

    virtual std::unique_ptr<DrinkPreparation> clone() const override
    {
        return std::make_unique<Juice>(*this);
    }
};

class Tea : public DrinkPreparation
{
public:
    virtual void prepare() const override
    {
        std::cout << "preparing tea\n";
    }

    virtual std::unique_ptr<DrinkPreparation> clone() const override
    {
        return std::make_unique<Tea>(*this);
    }
};

class HotChocolate : public DrinkPreparation
{
public:
    virtual void prepare() const override
    {
        std::cout << "preparing hot chocolate\n";
    }

    virtual std::unique_ptr<DrinkPreparation> clone() const override
    {
        return std::make_unique<HotChocolate>(*this);
    }
};

int main()
{
    std::cout << "we could use a builder here also\n";

    std::unique_ptr<DrinkPreparation> preparation = std::make_unique<Coffee>();
    std::unique_ptr<DrinkContainer> container = std::make_unique<Jar>();

    std::unique_ptr<Drink> aDrink = std::make_unique<Drink>(preparation, container);

    aDrink->prepare();
    aDrink->serve();

    return 0;
}