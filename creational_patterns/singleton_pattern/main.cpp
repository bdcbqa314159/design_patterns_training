#include <iostream>
#include <memory>
#include <thread>

class MeyerSingleton
{

public:
    static MeyerSingleton &createInstance(std::string value)
    {
        static MeyerSingleton instance(value);
        return instance;
    }

    std::string getValue() const
    {
        return value;
    }

private:
    std::string value;
    MeyerSingleton() = default;
    ~MeyerSingleton() {}
    MeyerSingleton(std::string value) : value(value) {}

    MeyerSingleton(const MeyerSingleton &other) = delete;
    MeyerSingleton &operator=(const MeyerSingleton &other) = delete;
};

void threadFoo()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    MeyerSingleton &s1 = MeyerSingleton::createInstance("FOO");
    std::cout << s1.getValue() << "\n";
}

void threadBar()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    MeyerSingleton &s1 = MeyerSingleton::createInstance("BAR");
    std::cout << s1.getValue() << "\n";
}

int main()
{
    std::cout << "working with singleton pattern...\n";
    std::thread t1(threadFoo);
    std::thread t2(threadBar);

    t1.join();
    t2.join();

    return 0;
}