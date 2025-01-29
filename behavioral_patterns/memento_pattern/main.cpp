#include <iostream>

class Memento
{
public:
    virtual ~Memento() = default;
    Memento() = default;

    virtual std::string getMessage() const = 0;
    virtual std::unique_ptr<Memento> clone() const = 0;
    virtual void print(std::ostream &os) const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Memento &obj)
    {
        obj.print(os);
        return os;
    }
};

class ConcreteMemento : public Memento
{
public:
    std::string message;

    ConcreteMemento() = default;
    ConcreteMemento(const std::string &aMessage) : message(aMessage) {}

    virtual std::string getMessage() const override
    {
        return message;
    }

    virtual std::unique_ptr<Memento> clone() const override
    {
        return std::make_unique<ConcreteMemento>(*this);
    }

    virtual void print(std::ostream &os) const override
    {
        os << "state: " << message;
    }

    virtual ~ConcreteMemento() = default;
};

class Writer
{
public:
    std::string message;
    Writer() = default;
    Writer(const std::string &aMessage) : message(aMessage) {}

    void writeMe(const std::string &aMessage)
    {
        message = aMessage;
    }

    std::unique_ptr<Memento> save() const
    {
        ConcreteMemento out(message);
        return out.clone();
    }

    void restore(std::unique_ptr<Memento> &memento)
    {
        message = memento->getMessage();
    }
};

class CareTaker
{
public:
    std::unique_ptr<Writer> writer;
    std::vector<std::unique_ptr<Memento>> mementos;

    CareTaker() = default;
    CareTaker(std::unique_ptr<Writer> aWriter) : writer(std::move(aWriter)) {}

    void typeMessage(const std::string &aMessage)
    {
        writer->writeMe(aMessage);
    }

    void backup()
    {
        mementos.push_back(writer->save());
    }

    void undo()
    {
        if (!mementos.size())
            return;

        std::unique_ptr<Memento> memento = std::move(mementos.back());
        mementos.pop_back();

        writer->restore(memento);
    }

    void showHistory()
    {
        for (auto &memento : mementos)
        {
            std::cout << *memento << "\n";
        }
    }
};

int main()
{
    std::cout << "hello\n";
    std::unique_ptr<Writer> writer = std::make_unique<Writer>("hello world");
    CareTaker helper(std::move(writer));

    helper.typeMessage("HELLO WORLD");
    helper.backup();
    helper.typeMessage("&JEK:LSJ WOK");
    helper.undo();
    helper.typeMessage("my friend is my favourite book");
    helper.backup();
    helper.showHistory();

    helper.typeMessage("ljafldkhiwffdslajkfda");
    helper.undo();

    return 0;
}