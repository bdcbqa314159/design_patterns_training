#include <iostream>
class Reader;
class IReader
{
public:
    virtual ~IReader() = default;
    IReader() = default;
    virtual void update(const std::string &news_to_read) = 0;
};
class INews
{
public:
    virtual void subscribe(std::shared_ptr<Reader> &reader) = 0;
    virtual void unsubscribe(const std::string &id) = 0;
    virtual void notify() = 0;
};

class Reader : public IReader
{
public:
    std::string id, news_received;
    INews *newspaper;

    Reader() = default;
    Reader(const std::string &id) : id(id) {}

    void unsubscribe()
    {
        newspaper->unsubscribe(id);
        newspaper = nullptr;
    }

    virtual void update(const std::string &news_to_read) override
    {
        news_received = news_to_read;
    }
};

class News : public INews
{
public:
    std::string scoop;
    std::unordered_map<std::string, std::shared_ptr<Reader>> readers;
    News() = default;

    void update_scoop(const std::string &aScoop)
    {
        scoop = aScoop;
    }

    virtual void subscribe(std::shared_ptr<Reader> &reader) override
    {
        readers.insert({reader->id, reader});
        reader->newspaper = this;
    }

    virtual void unsubscribe(const std::string &id) override
    {
        if (readers.find(id) != readers.end())
        {
            readers.erase(id);
        }
    }
    virtual void notify() override
    {
        std::unordered_map<std::string, std::shared_ptr<Reader>>::iterator it = readers.begin();
        for (; it != readers.end(); ++it)
        {
            it->second->update(scoop);
        }
    }
};

int main()
{
    std::shared_ptr<News> journal = std::make_shared<News>();
    std::shared_ptr<Reader> a = std::make_shared<Reader>("123+");
    std::shared_ptr<Reader> b = std::make_shared<Reader>("89%^");

    std::shared_ptr<Reader> c = std::make_shared<Reader>("valide_checked");

    journal->subscribe(a);
    journal->subscribe(b);
    journal->subscribe(c);

    journal->update_scoop("a car just passed by");

    journal->notify();
    a->unsubscribe();

    std::shared_ptr<Reader> d = std::make_shared<Reader>("toto1");
    journal->subscribe(d);
    journal->update_scoop("the life is great");
    journal->notify();

    return 0;
}