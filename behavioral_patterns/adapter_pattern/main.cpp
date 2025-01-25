#include <iostream>

class Foo
{

public:
    int id{};
    Foo() = default;
    Foo(int id) : id(id) {}

    void printMe(std::ostream &os) const
    {
        os << "foo - id: " << id;
    }

    friend std::ostream &operator<<(std::ostream &os, const Foo &obj)
    {
        obj.printMe(os);
        return os;
    }

    std::unique_ptr<Foo> clone()
    {
        return std::make_unique<Foo>(*this);
    }
};

class Bar
{
public:
    std::unique_ptr<Foo> myFoo = std::make_unique<Foo>();
    std::string name;

    Bar() = default;

    Bar(const std::string &name, std::unique_ptr<Foo> &foo) : name(name)
    {
        myFoo = foo->clone();
    }

    Bar(const Bar &other) : name(other.name)
    {
        myFoo = other.myFoo->clone();
    }

    void printMe(std::ostream &os) const
    {
        os << "bar - name: " << name << "\n";
        os << "with foo: " << *myFoo;
    }

    friend std::ostream &operator<<(std::ostream &os, const Bar &obj)
    {
        obj.printMe(os);
        return os;
    }
};

int main()
{
    std::cout << "hello...\n";

    Foo me(4);
    std::cout << "test: " << me << "\n";

    std::unique_ptr<Foo> newMe = me.clone();
    std::cout << *newMe << "\n";

    Bar bar;
    std::string name = "myName";

    Bar anotherBar(name, newMe);

    Bar finalBar(anotherBar);

    std::cout << "finals:\n";
    std::cout << bar << "\n"
              << anotherBar
              << "\n"
              << finalBar
              << "\n";

    return 0;
}