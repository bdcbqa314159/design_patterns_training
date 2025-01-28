#include <iostream>

class BankAccount
{
public:
    int balance = 0;
    BankAccount() = default;
    BankAccount(int balance) : balance(balance) {}

    void deposit(int amount) { balance += amount; }
    void withdraw(int amount) { balance -= amount; }
};

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class BankAccountCommand : public Command
{
public:
    enum class Action : bool
    {
        deposit,
        withdraw
    };

    Action action;
    int amount = 0;
    BankAccount &account;

    BankAccountCommand(Action a, int amount, BankAccount &acc) : action(a), amount(amount), account(acc) {}

    void execute() override
    {
        if (action == Action::deposit)
            account.deposit(amount);
        else
            account.withdraw(amount);
    }
};

int main()
{
    BankAccount ba1(1000);
    BankAccount ba2(20000);

    std::vector<BankAccountCommand> commands{BankAccountCommand(BankAccountCommand::Action::withdraw, 200, ba1), BankAccountCommand(BankAccountCommand::Action::deposit, 1000, ba2)};
    for (auto &command : commands)
        command.execute();

    std::cout << ba1.balance << "\n"
              << ba2.balance << "\n";

    return 0;
}