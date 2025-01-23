#include <iostream>

class PersonalObject
{

public:
    std::string name;
    int id = 0, privacy = 0;
    char type = 0;

    virtual void print(std::ostream &os) const
    {
        os << "[Personal Object]\n";
        os << "name: " << name << "\n";
        os << "id: " << id << "\n";
        os << "type: " << type;
    }

    friend std::ostream &operator<<(std::ostream &os, const PersonalObject &obj)
    {
        obj.print(os);
        return os;
    }

    std::unique_ptr<PersonalObject> clone()
    {
        return std::make_unique<PersonalObject>(*this);
    }
};

class PersonalObjectBuilder
{
public:
    std::unique_ptr<PersonalObject> myObj = std::make_unique<PersonalObject>();
    virtual void addName() = 0;
    virtual void addId() = 0;
    virtual void addType() = 0;

    PersonalObjectBuilder() = default;

    virtual ~PersonalObjectBuilder() {}

    std::unique_ptr<PersonalObject> getObject()
    {
        return myObj->clone();
    }

    void reset()
    {
        myObj = std::make_unique<PersonalObject>();
    }
};

class StandardBuilder : public PersonalObjectBuilder
{
public:
    StandardBuilder() = default;
    virtual ~StandardBuilder() {}

    virtual void addName() override
    {
        myObj->name = "standard";
    }

    virtual void addId() override
    {
        myObj->id = 123;
    }

    virtual void addType() override
    {
        myObj->type = 'A';
    }
};

class PremiumBuilder : public PersonalObjectBuilder
{
public:
    PremiumBuilder() = default;
    virtual ~PremiumBuilder() {}

    virtual void addName() override
    {
        myObj->name = "premium";
    }

    virtual void addId() override
    {
        myObj->id = 100;
    }

    virtual void addType() override
    {
        myObj->type = 'Z';
    }
};

class ProBuilder : public PersonalObjectBuilder
{
public:
    ProBuilder() = default;
    virtual ~ProBuilder() {}

    virtual void addName() override
    {
        myObj->name = "pro";
    }

    virtual void addId() override
    {
        myObj->id = 90;
    }

    virtual void addType() override
    {
        myObj->type = 'O';
    }
};

class Director
{
public:
    std::unique_ptr<PersonalObjectBuilder> builder;

    Director() = default;

    void setBuilder(std::unique_ptr<PersonalObjectBuilder> other_builder)
    {
        builder = std::move(other_builder);
    }

    void swichToStandard()
    {
        setBuilder(std::make_unique<StandardBuilder>());
    }

    void swichToPremium()
    {
        setBuilder(std::make_unique<PremiumBuilder>());
    }

    void swichToPro()
    {
        setBuilder(std::make_unique<ProBuilder>());
    }

    std::unique_ptr<PersonalObject> fullObject()
    {
        builder->reset();
        builder->addId();
        builder->addName();
        builder->addType();
        return builder->getObject();
    }

    std::unique_ptr<PersonalObject> objectNoID()
    {
        builder->reset();
        builder->addName();
        builder->addType();
        return builder->getObject();
    }

    std::unique_ptr<PersonalObject> objectNoType()
    {
        builder->reset();
        builder->addId();
        builder->addName();
        return builder->getObject();
    }

    std::unique_ptr<PersonalObject> objectOnlyName()
    {
        builder->reset();
        builder->addName();
        return builder->getObject();
    }
};

int main()
{
    std::cout << "builder pattern...\n";

    Director myDirector;

    std::unique_ptr<PersonalObject> test;

    myDirector.swichToStandard();
    test = myDirector.fullObject();
    std::cout << *test << "\n";

    myDirector.swichToPremium();
    test = myDirector.fullObject();
    std::cout << *test << "\n";

    myDirector.swichToPro();
    test = myDirector.fullObject();
    std::cout << *test << "\n";

    test = myDirector.objectOnlyName();
    std::cout << *test << "\n";

    test = myDirector.objectNoID();
    std::cout << *test << "\n";

    return 0;
}