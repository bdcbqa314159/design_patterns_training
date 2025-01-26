#include <iostream>

struct Result
{
    int value = 0;
    std::string name;
    Result() = default;
    Result(int value, std::string name) : value(value), name(name) {}
};

class Database
{

public:
    std::unordered_map<std::string, int> accounts;

    static Database &createInstance()
    {
        static Database instance;
        return instance;
    }

    Result request(std::string key)
    {
        Result out(0, "not_found");
        if (accounts.find(key) != accounts.end())
        {
            out.name = key;
            out.value = accounts[key];
        }

        return out;
    }

    void insert(const Result &result)
    {
        accounts[result.name] = result.value;
    }

private:
    Database() = default;
    ~Database() {}

    Database(const Database &other) = delete;
    Database &operator=(const Database &other) = delete;
};

class Request
{

public:
    Request() = default;
    virtual ~Request() = default;
    virtual void identify(std::string bearer) = 0;
    virtual Result ask(Database &db, std::string key) const = 0;
    virtual void change(Database &db, std::string key, int value) const = 0;

    virtual std::unique_ptr<Request> clone() const = 0;
};

class RealRequest : public Request
{
public:
    RealRequest() = default;

    virtual void identify(std::string bearer) override
    {
    }

    virtual Result ask(Database &db, std::string key) const override
    {
        return db.request(key);
    }

    virtual void change(Database &db, std::string key, int value) const override
    {
        Result temp(value, key);
        db.insert(temp);
    }

    virtual std::unique_ptr<Request> clone() const override
    {
        return std::make_unique<RealRequest>(*this);
    }
};

class Proxy : public Request
{
public:
    std::string bearer = "123abc";
    std::unique_ptr<Request> realReq;
    bool access = false;

    Proxy() = default;
    Proxy(std::unique_ptr<Request> &newRealReq)
    {
        this->realReq = newRealReq->clone();
    }

    virtual void identify(std::string bearer) override
    {
        if (this->bearer == bearer)
            access = true;
    }

    virtual Result ask(Database &db, std::string key) const override
    {
        if (access)
            return db.request(key);
        else
        {
            std::cout << "You don't have access to the db.\n";
            Result out;
            return out;
        }
    }

    virtual void change(Database &db, std::string key, int value) const override
    {
        if (access)
        {
            Result temp(value, key);
            db.insert(temp);
        }

        else
        {
            std::cout << "You don't have access to the db.\n";
        }
    }

    virtual std::unique_ptr<Request> clone() const override
    {
        std::unique_ptr<Proxy> out = std::make_unique<Proxy>();
        out->realReq = this->realReq->clone();
        return out;
    }
};

int main()
{
    Result one(12, "Alex"), two(23, "Anton"), three(100, "Claudio");
    Database &db = Database::createInstance();
    db.insert(one);
    db.insert(two);
    db.insert(three);

    std::unique_ptr<Request> myReq = std::make_unique<RealRequest>();
    auto res = myReq->ask(db, "Anton");
    std::cout << res.name << " : " << res.value << "\n";

    myReq = std::make_unique<Proxy>(myReq);

    res = myReq->ask(db, "Anton");
    std::cout << res.name << " : " << res.value << "\n";

    myReq->identify("123abc");
    res = myReq->ask(db, "Anton");
    std::cout << res.name << " : " << res.value << "\n";

    return 0;
}