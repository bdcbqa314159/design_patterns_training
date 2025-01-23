#include <iostream>
#include <string>

class Product
{

public:
    virtual ~Product() {}
    virtual std::string Operation() const = 0;
};

class ConcreteProduct1 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product
{
public:
    std::string Operation() const override
    {
        return "{Result of the ConcreteProduct2}";
    }
};

class Creator
{
public:
    virtual ~Creator() {};
    virtual Product *FactoryMethod() const = 0;

    std::string SomeOperation() const
    {
        Product *product = this->FactoryMethod();
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct1();
    };
};

class ConcreteCreator2 : public Creator
{
public:
    Product *FactoryMethod() const override
    {
        return new ConcreteProduct2();
    };
};

void ClientCode(const Creator &creator)
{
    std::cout << "Client: I am not aware of the creator's class, but it still works...\n";
    std::cout << creator.SomeOperation() << "\n";
}

int main()
{

    std::cout << "App: Launched with ConcreteOperator1\n";
    Creator *creator1 = new ConcreteCreator1();
    ClientCode(*creator1);
    std::cout << "\n\n";

    std::cout << "App: Launched with ConcreteOperator2\n";
    Creator *creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator1;
    delete creator2;

    return 0;
}