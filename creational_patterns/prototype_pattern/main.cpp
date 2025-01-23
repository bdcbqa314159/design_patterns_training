#include <iostream>

class Memory
{
public:
    int capacity = 0;
    Memory() = default;
    Memory(int capacity) : capacity(capacity)
    {
    }

    void set_capacity(int capacity)
    {
        this->capacity = capacity;
    }

    virtual void print(std::ostream &os) const = 0;
    virtual ~Memory() {}

    friend std::ostream &operator<<(std::ostream &os, const Memory &obj)
    {
        obj.print(os);
        return os;
    }
};

class RAM : public Memory
{
public:
    RAM() = default;
    RAM(int capacity) : Memory(capacity) {}

    virtual void print(std::ostream &os) const
    {
        os << "RAM capacity : " << capacity;
    }
};

class SSD : public Memory
{
public:
    SSD() = default;
    SSD(int capacity) : Memory(capacity) {}
    virtual void print(std::ostream &os) const
    {
        os << "SSD capacity : " << capacity;
    }
};

class Computer
{
public:
    SSD ssd;
    RAM ram;
    int serial = 0;

    Computer() = default;
    Computer(int serial) : serial(serial) {}
    virtual ~Computer() {}

    virtual void print(std::ostream &os) const = 0;
    virtual std::unique_ptr<Computer> clone() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Computer &obj)
    {
        obj.print(os);
        return os;
    }

    void set_ram(int capacity)
    {
        ram.set_capacity(capacity);
    }

    void set_ssd(int capacity)
    {
        ssd.set_capacity(capacity);
    }
};

class Desktop : public Computer
{
public:
    std::string label;

    Desktop() = default;
    Desktop(int serial, std::string label) : Computer(serial), label(label) {}
    virtual ~Desktop() {}

    virtual void print(std::ostream &os) const override
    {
        os << "[desktop computer]\n";
        os << "label: " << label << "\n";
        os << "specs:\n";
        os << ram << "\n";
        os << ssd << "\n";
    }

    virtual std::unique_ptr<Computer> clone() const override
    {
        return std::make_unique<Desktop>(*this);
    }
};

class Laptop : public Computer
{
public:
    std::string hash;

    Laptop() = default;
    Laptop(int serial, std::string hash) : Computer(serial), hash(hash) {}
    virtual ~Laptop() {}

    virtual void print(std::ostream &os) const override
    {
        os << "[laptop computer]\n";
        os << "hash id: " << hash << "\n";
        os << "specs:\n";
        os << ram << "\n";
        os << ssd << "\n";
    }

    virtual std::unique_ptr<Computer> clone() const override
    {
        return std::make_unique<Laptop>(*this);
    }
};

enum class COMPUTER_TYPE
{
    DESKTOP,
    LAPTOP,
};

class MyComputerFactory
{

public:
    std::unordered_map<COMPUTER_TYPE, std::unique_ptr<Computer>> my_map;
    MyComputerFactory()
    {
        std::string label = "desktop_hp", hash = "#e12b_laptop";
        my_map[COMPUTER_TYPE::DESKTOP] = std::make_unique<Desktop>(123, label);
        my_map[COMPUTER_TYPE::LAPTOP] = std::make_unique<Laptop>(120, hash);
    }

    std::unique_ptr<Computer> produce(COMPUTER_TYPE type)
    {
        return my_map[type]->clone();
    }
};

class SpecAdder
{

public:
    void operator()(int ram, int ssd, std::unique_ptr<Computer> &obj)
    {
        obj->set_ram(ram);
        obj->set_ssd(ssd);
    }
};

int main()
{
    std::cout << "Final example for prototype pattern...\n";

    std::cout << "Standard of two computers done in the factory.\n";
    MyComputerFactory theFactory;

    std::cout << "Elements:\n";

    std::cout << *theFactory.my_map[COMPUTER_TYPE::DESKTOP] << "\n";
    std::cout << *theFactory.my_map[COMPUTER_TYPE::LAPTOP] << "\n";

    std::cout << "production starts:\n";

    std::unique_ptr<Computer>
        command_1 = theFactory.produce(COMPUTER_TYPE::DESKTOP);
    std::unique_ptr<Computer>
        command_2 = theFactory.produce(COMPUTER_TYPE::LAPTOP);

    std::cout << "Adding specs...\n";

    SpecAdder mySpecAdder;

    int ram = 230, ssd = 300;

    mySpecAdder(ram, ssd, command_1);

    ram = 1230, ssd = 3000;
    mySpecAdder(ram, ssd, command_1);

    std::cout << "Two clients wants two differents computers:\n";
    std::cout << *command_1;
    std::cout << "\n======\n";
    std::cout << *command_2;
    std::cout << "\n";

    return 0;
}