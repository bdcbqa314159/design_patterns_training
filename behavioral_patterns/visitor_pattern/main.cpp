#include <iostream>

class Circle;
class Square;

class ShapeVisitor
{
public:
    virtual void visit(Circle &circle) = 0;
    virtual void visit(Square &square) = 0;
};

class Shape
{
public:
    virtual void accept(ShapeVisitor &visitor) = 0;
    virtual void print(std::ostream &os) const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
    Shape() = default;
    friend std::ostream &operator<<(std::ostream &os, const Shape &obj)
    {
        obj.print(os);
        return os;
    }
};

class Circle : public Shape
{
public:
    double radius{};
    Circle(double radius) : radius(radius) {}
    void accept(ShapeVisitor &visitor) override
    {
        visitor.visit(*this);
    }
    virtual void print(std::ostream &os) const override
    {
        os << "a cercle\n";
    }

    virtual void draw() const override
    {
        std::cout << "drawing a circle\n";
    }
};

class Square : public Shape
{
public:
    double side{};
    Square(double side) : side(side) {}
    void accept(ShapeVisitor &visitor) override
    {
        visitor.visit(*this);
    }
    virtual void print(std::ostream &os) const override
    {
        os << "a square\n";
    }

    virtual void draw() const override
    {
        std::cout << "drawing a square\n";
    }
};

class DrawingVisitor : public ShapeVisitor
{
public:
    void visit(Circle &circle) override
    {
        circle.draw();
    }

    void visit(Square &square) override
    {
        square.draw();
    }
};

class AreaVisitor : public ShapeVisitor
{
public:
    void visit(Circle &circle) override
    {
        double area = 2 * M_PI * circle.radius;
        std::cout << "the area of this circle is " << area << "area units\n";
    }

    void visit(Square &square) override
    {
        double area = square.side * square.side;
        std::cout << "the area of this square is " << area << "area units\n";
    }
};

int main()
{
    std::vector<std::unique_ptr<Shape>> figures;
    std::unique_ptr<Shape> fig = std::make_unique<Circle>(1.);
    figures.push_back(std::move(fig));
    fig = std::make_unique<Square>(2.);
    figures.push_back(std::move(fig));

    DrawingVisitor visitor_draw;
    AreaVisitor visitor_area;

    std::cout << "===== drawing =====\n";

    for (auto &fig : figures)
        fig->accept(visitor_draw);

    std::cout << "===== calculating area =====\n";

    for (auto &fig : figures)
        fig->accept(visitor_area);

    return 0;
}