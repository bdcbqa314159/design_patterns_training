#include <iostream>

class Letter
{
public:
    virtual ~Letter() {}
    virtual std::string id() const = 0;

    friend std::ostream &operator<<(std::ostream &os, const Letter &obj)
    {
        os << obj.id();
        return os;
    }
};

class LetterA : public Letter
{
public:
    virtual ~LetterA()
    {
        std::cout << "deleting A...\n";
    }

    virtual std::string id() const override
    {
        return "A";
    }
};

class LetterB : public Letter
{
public:
    virtual ~LetterB()
    {
        std::cout << "deleting B...\n";
    }

    virtual std::string id() const override
    {
        return "B";
    }
};

enum class LetterType{
    LetterA,
    LetterB,
};

class LetterCreator
{

public:
    virtual ~LetterCreator() {}
    virtual std::unique_ptr<Letter> create() const = 0;
};

class CreatorLetterA: public LetterCreator{
public:

    virtual ~CreatorLetterA(){
        std::cout<<"deleting creator letter A...\n";
    }

    virtual std::unique_ptr<Letter> create() const override{
        return std::make_unique<LetterA>();
    }
};

class CreatorLetterB: public LetterCreator{
public:

    virtual ~CreatorLetterB(){
        std::cout<<"deleting creator letter B...\n";
    }

    virtual std::unique_ptr<Letter> create() const override{
        return std::make_unique<LetterB>();
    }
};

std::unique_ptr<Letter> clientLetterCreation(LetterType type_letter){
    std::unique_ptr<LetterCreator> myCreator;

    switch (type_letter){
        case LetterType::LetterA:
            myCreator = std::make_unique<CreatorLetterA>();
            break;
        case LetterType::LetterB:
            myCreator = std::make_unique<CreatorLetterB>();
            break;
        default:
            std::cout<<"unknown type\n";
            return nullptr;
    }

    return myCreator->create();
}

void letterValuation(std::unique_ptr<Letter> &theLetter){

    if (theLetter)
        std::cout << "Working with letter: " << *theLetter << "\n";
    else{
        std::cout<<"unknown type asked...\n";
    }
}

int main()
{

    std::unique_ptr<Letter> myLetter;
    letterValuation(myLetter);
    
    myLetter = clientLetterCreation(LetterType::LetterA);

    letterValuation(myLetter);

    myLetter = clientLetterCreation(LetterType::LetterB);

    letterValuation(myLetter);
    
    return 0;
}