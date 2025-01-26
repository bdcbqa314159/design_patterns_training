#include <iostream>

class FontStyle
{
public:
    std::string font, color;
    int size = 0;

    FontStyle() = default;
    FontStyle(const std::string &newFont, const std::string &newColor, int newSize) : font(newFont), color(newColor), size(newSize) {}

    std::shared_ptr<FontStyle> clone() const
    {
        return std::make_shared<FontStyle>(*this);
    }

    std::string key() const
    {
        std::string key = font + "_" + color + "_" + std::to_string(size);
        return key;
    }
};

class StyleFactory
{
public:
    std::unordered_map<std::string, std::shared_ptr<FontStyle>> styles;
    StyleFactory() = default;

    std::shared_ptr<FontStyle> getStyle(const std::string &font, const std::string &color, int size)
    {
        std::string key = font + "_" + color + "_" + std::to_string(size);

        if (styles.find(key) == styles.end())
        {
            std::cout << "style: " << key << " not present, building it ...\n";
            styles[key] = std::make_shared<FontStyle>(font, color, size);
        }

        return styles[key];
    }

    std::shared_ptr<FontStyle> getStyle(std::shared_ptr<FontStyle> aStyle)
    {
        std::string key = aStyle->key();

        if (styles.find(key) == styles.end())
        {
            std::cout << "style: " << key << " not present, building it ...\n";
            styles[key] = aStyle;
        }

        return styles[key];
    }
};

class Character
{
public:
    char symbol = 0;
    std::shared_ptr<FontStyle> style;

    Character() = default;
    Character(char newSymbol, std::shared_ptr<FontStyle> sharedStyle) : symbol(newSymbol), style(sharedStyle) {}
};

int main()
{

    FontStyle first_fs("arial", "red", 1);
    FontStyle second_fs("times", "black", 2);

    std::shared_ptr<FontStyle> first = std::make_shared<FontStyle>("arial", "red", 1);
    std::shared_ptr<FontStyle> second = std::make_shared<FontStyle>("times", "black", 2);

    StyleFactory factory;
    std::shared_ptr<FontStyle> p1 = factory.getStyle(first);
    std::shared_ptr<FontStyle> p2 = factory.getStyle(second);
    std::shared_ptr<FontStyle> p3 = factory.getStyle("bold", "yellow", 12);

    Character a('a', p1);
    Character b('b', p2);

    first->font = "office";

    return 0;
}