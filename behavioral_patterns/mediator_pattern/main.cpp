#include <iostream>
class ChatRoom
{
public:
    ChatRoom() = default;
    virtual ~ChatRoom() = default;
    virtual void broadcast(const std::string &from, const std::string &msg) = 0;
    virtual void message(const std::string &from, const std::string &to, const std::string &msg) = 0;
};

class Person
{
public:
    std::string name;
    ChatRoom *room = nullptr;
    std::vector<std::string> chat_log;

    Person() = default;
    Person(const std::string &name) : name(name) {}

    void say(const std::string &msg)
    {
        if (room)
            room->broadcast(name, msg);
        else
            std::cout << name << " is not in a chat room to talk.\n";
    }

    void receive(const std::string &from, const std::string &msg)
    {
        std::string full{from + ": \"" + msg + "\""};
        std::cout << "[" << name << "'s chat session] " << full << "\n";
        chat_log.emplace_back(full);
    }

    void private_message(const std::string &to, const std::string &msg)
    {
        if (room)
            room->message(name, to, msg);
        else
            std::cout << name << " is not in a chat room to talk.\n";
    }
};

class GoogleChat : public ChatRoom
{
public:
    std::unordered_map<std::string, std::shared_ptr<Person>> persons;
    GoogleChat() = default;

    void join(std::shared_ptr<Person> &person)
    {
        persons.insert({person->name, person});
        person->room = this;
    }

    void quit(const std::string &name)
    {
        if (persons.find(name) != persons.end())
        {
            persons[name]->room = nullptr;
        }
        else
        {
            std::cout << "person with " << name << " not in the chat\n";
        }
    }

    void broadcast(const std::string &from, const std::string &msg) override
    {
        if (persons.find(from) != persons.end())
        {
            auto it = persons.begin();
            for (; it != persons.end(); ++it)
            {
                if (it->first != from)
                {
                    it->second->receive(from, msg);
                }
            }
        }
        else
        {
            std::cout << "person with " << from << " not in the chat\n";
        }
    }

    void message(const std::string &from, const std::string &to, const std::string &msg) override
    {
        if (persons.find(to) != persons.end())
        {
            persons[to]->receive(from, msg);
        }
        else
        {
            std::cout << "person with " << to << " not in the chat\n";
        }
    }
};

int main()
{
    std::shared_ptr<GoogleChat> chat = std::make_shared<GoogleChat>();
    std::shared_ptr<Person> a = std::make_shared<Person>("arthur");
    std::shared_ptr<Person> b = std::make_shared<Person>("matt");
    std::shared_ptr<Person> c = std::make_shared<Person>("mark");

    chat->join(a);
    chat->join(b);
    chat->join(c);

    a->say("hello everyone");
    b->say("hello arthur");
    b->private_message("arthur", "can we talk privately?");
    c->say("hello the community!");
    c->private_message("matt", "hey matt, still up for a drink later?");
    b->private_message("mark", "hey mark, always up :)");

    return 0;
}