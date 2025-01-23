#include <iostream>

class Headphones
{

public:
    std::string label = "headphones";
    Headphones() = default;
    virtual ~Headphones() {}

    virtual void print(std::ostream &os) const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Headphones &obj)
    {
        obj.print(os);
        return os;
    }
};

class AppleHeadphones : public Headphones
{
public:
    std::string brand = "apple";
    AppleHeadphones() = default;
    virtual ~AppleHeadphones() {}

    virtual void print(std::ostream &os) const override
    {
        os << label << " [brand]: " << brand;
    }
};

class SamsungHeadphones : public Headphones
{
public:
    std::string brand = "samsung";
    SamsungHeadphones() = default;
    virtual ~SamsungHeadphones() {}

    virtual void print(std::ostream &os) const override
    {
        os << label << " [brand]: " << brand;
    }
};

class Phone
{
public:
    std::string label = "phone";
    Phone() = default;
    virtual ~Phone() {}

    virtual void print(std::ostream &os) const = 0;
    virtual void connecting(std::unique_ptr<Headphones> &headphones) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Phone &obj)
    {
        obj.print(os);
        return os;
    }
};

class ApplePhone : public Phone
{
public:
    std::string brand = "apple";
    ApplePhone() = default;
    virtual ~ApplePhone() {}

    virtual void print(std::ostream &os) const override
    {
        os << label << " [brand]: " << brand;
    }

    virtual void connecting(std::unique_ptr<Headphones> &headphones) const override
    {
        std::cout << "this:" << "\n";
        std::cout << *this << "\nconnected to:\n";
        std::cout << *headphones << "\n";
    }
};

class SamsungPhone : public Phone
{
public:
    std::string brand = "samsung";
    SamsungPhone() = default;
    virtual ~SamsungPhone() {}

    virtual void print(std::ostream &os) const override
    {
        os << label << " [brand]: " << brand;
    }

    virtual void connecting(std::unique_ptr<Headphones> &headphones) const override
    {
        std::cout << "this:" << "\n";
        std::cout << *this << "\nconnected to:\n";
        std::cout << *headphones << "\n";
    }
};

class AbstractFactory
{
public:
    virtual ~AbstractFactory() {}
    virtual std::unique_ptr<Headphones> createHeadphones() const = 0;
    virtual std::unique_ptr<Phone> createPhone() const = 0;
};

class AppleFactory : public AbstractFactory
{
public:
    virtual ~AppleFactory() {}
    virtual std::unique_ptr<Headphones> createHeadphones() const override
    {
        return std::make_unique<AppleHeadphones>();
    }
    virtual std::unique_ptr<Phone> createPhone() const override
    {
        return std::make_unique<ApplePhone>();
    }
};

class SamsungFactory : public AbstractFactory
{
public:
    virtual ~SamsungFactory() {}
    virtual std::unique_ptr<Headphones> createHeadphones() const override
    {
        return std::make_unique<SamsungHeadphones>();
    }
    virtual std::unique_ptr<Phone> createPhone() const override
    {
        return std::make_unique<SamsungPhone>();
    }
};

void clientCode(std::unique_ptr<AbstractFactory> &factory)
{
    std::unique_ptr<Headphones> headphones;
    std::unique_ptr<Phone> phone;

    headphones = factory->createHeadphones();
    phone = factory->createPhone();

    phone->connecting(headphones);
}

int main()
{
    std::cout << "working with abstract factory pattern...\n";

    std::unique_ptr<AbstractFactory> myFactory = std::make_unique<SamsungFactory>();

    clientCode(myFactory);

    myFactory = std::make_unique<AppleFactory>();

    clientCode(myFactory);

    return 0;
}