#include <iostream>

class PurchaseRequest
{
public:
    int amount = 0;
    bool approved_status = false;
    std::string approved_by;

    PurchaseRequest() = default;
    PurchaseRequest(int anAmount) : amount(anAmount) {}

    int getAmount() const { return amount; }

    void processPR(const std::string &approver)
    {
        approved_status = true;
        approved_by = approver;
    }

    void status(std::ostream &os) const
    {
        os << "---- Purchase Order Summary ----\n";
        os << "Amount: " << amount << "\n";
        os << "Approved Status: " << approved_status << "\n";
        os << "Approver Name: " << approved_by << "\n";
        os << "--------------------------------";
    }

    friend std::ostream &operator<<(std::ostream &os, const PurchaseRequest &obj)
    {
        obj.status(os);
        return os;
    }
};

class Employee
{
public:
    std::string name;
    int approval_limit = 0;
    std::unique_ptr<Employee> next;

    Employee() = default;
    virtual ~Employee() = default;
    Employee(const std::string &aName, int anApprovalLimit) : name(aName), approval_limit(anApprovalLimit) {}
    Employee(const std::string &aName, int anApprovalLimit, std::unique_ptr<Employee> aNext) : name(aName), approval_limit(anApprovalLimit), next(std::move(aNext)) {}

    bool handle(PurchaseRequest &request)
    {
        std::cout << name << "[ ";
        if (request.getAmount() <= approval_limit)
        {
            std::cout << "O ] ";
            return true;
        }
        else
        {
            std::cout << "X ] ";
            return false;
        }
    }

    void approve(PurchaseRequest &request)
    {
        request.processPR(name);
    }

    virtual std::unique_ptr<Employee> clone() const = 0;
};

class Junior : public Employee
{
public:
    Junior() : Employee("Junior", 500) {}
    virtual std::unique_ptr<Employee> clone() const override
    {
        std::unique_ptr<Junior> out = std::make_unique<Junior>();
        if (this->next)
            out->next = this->next->clone();
        return out;
    }
};

class SeniorAssociate : public Employee
{
public:
    SeniorAssociate() : Employee("SeniorAssociate", 1500) {}
    virtual std::unique_ptr<Employee> clone() const override
    {
        std::unique_ptr<SeniorAssociate> out = std::make_unique<SeniorAssociate>();
        if (this->next)
            out->next = this->next->clone();
        return out;
    }
};

class Manager : public Employee
{
public:
    Manager() : Employee("Manager", 3000) {}
    virtual std::unique_ptr<Employee> clone() const override
    {
        std::unique_ptr<Manager> out = std::make_unique<Manager>();
        if (this->next)
            out->next = this->next->clone();
        return out;
    }
};

class Node
{
public:
    int data;
    std::unique_ptr<Node> next;

    Node() = default;
    virtual ~Node() = default;
    Node(int data) : data(data) {}
    Node(int data, std::unique_ptr<Node> next) : data(data), next(std::move(next)) {}
    virtual std::unique_ptr<Node> clone() const = 0;
};

class EmployeeCOR
{
public:
    std::unique_ptr<Employee> head;
    EmployeeCOR() = default;
    EmployeeCOR(std::unique_ptr<Employee> head) : head(std::move(head)) {}

    void insert(std::unique_ptr<Employee> element)
    {
        Employee *current = head.get();
        while (current->next.get())
        {
            current = current->next.get();
        }
        current->next = std::move(element);
    }

    void handlingCOR(PurchaseRequest &request)
    {

        Employee *current = head.get();
        while (current)
        {
            if (current->handle(request))
            {
                current->approve(request);
                return;
            }
            current = current->next.get();
        }
    }
};

int main()
{
    std::unique_ptr<Employee> junior = std::make_unique<Junior>();
    std::unique_ptr<Employee> seniorAssociate = std::make_unique<SeniorAssociate>();
    std::unique_ptr<Employee> manager = std::make_unique<Manager>();

    EmployeeCOR chain(junior->clone());
    chain.insert(seniorAssociate->clone());
    chain.insert(manager->clone());

    PurchaseRequest PR_200(1600);

    chain.handlingCOR(PR_200);
    std::cout << "\n"
              << PR_200 << "\n";

    std::vector<PurchaseRequest> PRs{PurchaseRequest(200), PurchaseRequest(600), PurchaseRequest(1600), PurchaseRequest(5000)};
    for (auto &pr : PRs)
    {
        std::cout << "\n";
        std::cout << "Approval chain\n";
        chain.handlingCOR(pr);
        std::cout << "\n\n";
        std::cout << pr << "\n";
    }

    return 0;
}
