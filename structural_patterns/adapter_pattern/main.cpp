#include <iostream>

class ClientCode
{
public:
    ClientCode() = default;
    virtual ~ClientCode() = default;

    virtual std::string Request() const
    {
        return "Benchmark code";
    }
};

class ExternalCode
{
public:
    ExternalCode() = default;
    ~ExternalCode() = default;

    std::string CustomRequest()
    {
        return "3rdParty library result";
    }
};

class Adapter : public ClientCode
{
public:
    std::unique_ptr<ExternalCode> external;

    Adapter() = default;
    Adapter(std::unique_ptr<ExternalCode> &externalCode)
    {
        external = std::make_unique<ExternalCode>(*externalCode);
    }

    virtual std::string Request() const override
    {
        std::string fromExternal = external->CustomRequest();
        return "this is an adapter from: " + fromExternal;
    }
};

void clientExecution(std::unique_ptr<ClientCode> &target)
{
    std::cout << "=== From client execution ===\n";
    std::cout << target->Request() << "\n";
}

int main()
{
    std::cout << "Regular work:\n";
    std::unique_ptr<ClientCode> myCode = std::make_unique<ClientCode>();

    clientExecution(myCode);

    myCode = std::make_unique<Adapter>();
    clientExecution(myCode);

    std::cout << "== wrong usage of the library - it breaks the flow ==\n";
    std::unique_ptr<ExternalCode> externalCode = std::make_unique<ExternalCode>();
    std::cout << externalCode->CustomRequest() << "\n";

    return 0;
}