#include <iostream>

class Node
{
public:
    int data = 0;
    std::unique_ptr<Node> next;

    Node() = default;
    Node(int data) : data(data) {}
    Node(int data, std::unique_ptr<Node> next) : data(data), next(std::move(next)) {}

    std::unique_ptr<Node> clone() const
    {
        std::unique_ptr<Node> out = std::make_unique<Node>(this->data);
        if (this->next)
        {
            out->next = this->next->clone();
        }
        return out;
    }
};

class LinkedList
{
public:
    std::unique_ptr<Node> head;

    LinkedList() = default;
    LinkedList(std::unique_ptr<Node> aHead) : head(std::move(aHead)) {}

    void insert(std::unique_ptr<Node> element)
    {
        if (head)
        {
            Node *current = head.get();

            while (current->next.get())
            {
                current = current->next.get();
            }

            current->next = std::move(element);
        }
        else
        {
            head = std::move(element);
        }
    }

    void print(std::ostream &os) const
    {
        if (head)
        {
            Node *current = head.get();

            while (current)
            {
                os << current->data << "->";
                current = current->next.get();
            }
        }

        os << "X";
    }

    friend std::ostream &operator<<(std::ostream &os, const LinkedList &obj)
    {
        obj.print(os);
        return os;
    }

    struct Iterator
    {
        friend class LinkedList;

        Node *previous_node = nullptr, *current_node = nullptr;
        Iterator() = default;
        Iterator(const std::unique_ptr<Node> &node) : current_node(node.get()) {}

        Iterator &operator++()
        {
            if (current_node)
            {
                previous_node = current_node;
                current_node = current_node->next.get();
            }

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tempIter = *this;
            ++*this;
            return tempIter;
        }

        bool operator!=(const Iterator &other) const
        {
            return this->current_node != other.current_node;
        }

        int operator*() const
        {
            return this->current_node->data;
        }
    };

    Iterator begin() const
    {
        return Iterator(this->head);
    }

    Iterator end() const
    {
        return Iterator();
    }
};

int main()
{
    LinkedList myList;
    myList.insert(std::make_unique<Node>(3));

    std::vector<std::unique_ptr<Node>> myData;

    myData.push_back(std::make_unique<Node>(4));
    myData.push_back(std::make_unique<Node>(5));
    myData.push_back(std::make_unique<Node>(6));

    for (auto &node : myData)
    {
        myList.insert(node->clone());
    }

    std::cout << myList << "\n";

    std::cout << "with iterator:\n";
    LinkedList::Iterator it = myList.begin();
    for (; it != myList.end(); ++it)
    {
        std::cout << *it << "->";
    }
    std::cout << "X\n";

    return 0;
}