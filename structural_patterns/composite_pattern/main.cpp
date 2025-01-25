#include <iostream>

class HTMLElement
{
public:
    virtual ~HTMLElement() = default;
    virtual void render() const = 0;
    virtual void changeTag(const std::string &tag) = 0;
    virtual std::string giveTag() const = 0;
    virtual void add(std::unique_ptr<HTMLElement> &toBeAdded) = 0;
    virtual std::unique_ptr<HTMLElement> clone() const = 0;
};

class SimpleElement : public HTMLElement
{
public:
    std::string tagName;
    SimpleElement() = default;
    SimpleElement(const std::string &tag) : tagName(tag) {}

    virtual void changeTag(const std::string &tag) override
    {
        tagName = tag;
    }

    virtual std::string giveTag() const override
    {
        return tagName;
    }

    virtual void render() const override
    {
        std::cout << "<" << tagName << "></" << tagName << ">\n";
    }

    virtual std::unique_ptr<HTMLElement> clone() const override
    {
        return std::make_unique<SimpleElement>(*this);
    }

    virtual void add(std::unique_ptr<HTMLElement> &toBeAdded) override {}

    virtual ~SimpleElement() = default;
};

class CompositeElement : public HTMLElement
{
public:
    std::string tagName;
    std::vector<std::unique_ptr<HTMLElement>> children;

    CompositeElement() = default;
    CompositeElement(std::string tag) : tagName(tag) {}

    virtual std::string giveTag() const override
    {
        return tagName;
    }

    virtual void changeTag(const std::string &tag) override
    {
        tagName = tag;

        for (const auto &child : children)
        {
            std::string old = child->giveTag();
            child->changeTag("changed" + old);
        }
    }

    virtual void add(std::unique_ptr<HTMLElement> &toBeAdded) override
    {
        children.push_back(toBeAdded->clone());
    }

    virtual void render() const override
    {
        std::cout << "<" << tagName << ">\n";
        for (const auto &child : children)
            child->render();

        std::cout << "</" << tagName << ">\n";
    }

    virtual std::unique_ptr<HTMLElement> clone() const override
    {
        std::unique_ptr<CompositeElement> copy = std::make_unique<CompositeElement>(this->tagName);
        for (const auto &child : this->children)
        {
            copy->children.push_back(child->clone());
        }
        return copy;
    }
};

int main()
{
    std::unique_ptr<HTMLElement> div = std::make_unique<CompositeElement>("div");
    std::unique_ptr<HTMLElement> p = std::make_unique<SimpleElement>("p");
    std::unique_ptr<HTMLElement> button = std::make_unique<SimpleElement>("button");

    div->add(p);
    div->add(button);

    p->changeTag("pp");
    button->changeTag("bb");

    div->render();

    std::cout << "================\n";

    std::unique_ptr<HTMLElement> div1 = div->clone();
    div1->changeTag("newDiv");

    div1->render();

    std::cout << "================\n";

    div->add(div);
    div->render();

    return 0;
}