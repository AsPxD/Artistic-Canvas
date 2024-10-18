#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

enum class Tool { Circle, Rectangle, Triangle };

class Shape {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setColor(const sf::Color& color) = 0;
    virtual void resize(float factor) = 0;
    virtual void move(float dx, float dy) = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    sf::CircleShape circle;
public:
    Circle(float x, float y, float radius, const sf::Color& color) {
        circle.setRadius(radius);
        circle.setPosition(x - radius, y - radius);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(1);
        circle.setFillColor(color);
    }
    void draw(sf::RenderWindow& window) override {
        window.draw(circle);
    }
    void setColor(const sf::Color& color) override {
        circle.setFillColor(color);
    }
    void resize(float factor) override {
        circle.setRadius(circle.getRadius() * factor);
        circle.setPosition(circle.getPosition().x - circle.getRadius() * (factor - 1), 
                           circle.getPosition().y - circle.getRadius() * (factor - 1));
    }
    void move(float dx, float dy) override {
        circle.move(dx, dy);
    }
};

class Rectangle : public Shape {
    sf::RectangleShape rectangle;
public:
    Rectangle(float x, float y, float width, float height, const sf::Color& color) {
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setPosition(x - width / 2, y - height / 2);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(1);
        rectangle.setFillColor(color);
    }
    void draw(sf::RenderWindow& window) override {
        window.draw(rectangle);
    }
    void setColor(const sf::Color& color) override {
        rectangle.setFillColor(color);
    }
    void resize(float factor) override {
        rectangle.setSize(rectangle.getSize() * factor);
        rectangle.setPosition(rectangle.getPosition().x - rectangle.getSize().x * (factor - 1) / 2, 
                              rectangle.getPosition().y - rectangle.getSize().y * (factor - 1) / 2);
    }
    void move(float dx, float dy) override {
        rectangle.move(dx, dy);
    }
};

class Triangle : public Shape {
    sf::ConvexShape triangle;
public:
    Triangle(float x, float y, float size, const sf::Color& color) {
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0, -size / 2));
        triangle.setPoint(1, sf::Vector2f(-size / 2, size / 2));
        triangle.setPoint(2, sf::Vector2f(size / 2, size / 2));
        triangle.setPosition(x, y);
        triangle.setOutlineColor(sf::Color::Black);
        triangle.setOutlineThickness(1);
        triangle.setFillColor(color);
    }
    void draw(sf::RenderWindow& window) override {
        window.draw(triangle);
    }
    void setColor(const sf::Color& color) override {
        triangle.setFillColor(color);
    }
    void resize(float factor) override {
        for (size_t i = 0; i < 3; ++i) {
            sf::Vector2f point = triangle.getPoint(i);
            point *= factor;
            triangle.setPoint(i, point);
        }
    }
    void move(float dx, float dy) override {
        triangle.move(dx, dy);
    }
};

class ArtisticCanvas {
    sf::RenderWindow window;
    sf::Font font;
    std::vector<Shape*> shapes;
    sf::Color currentColor;
    Tool currentTool;
    Shape* selectedShape;
    sf::RectangleShape circleButton, rectangleButton, triangleButton;
    sf::Text circleLabel, rectangleLabel, triangleLabel;
public:
    ArtisticCanvas() : window(sf::VideoMode(800, 600), "Artistic Canvas"), currentColor(sf::Color::Blue), currentTool(Tool::Circle), selectedShape(nullptr) {
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
        }
        // Initialize buttons and labels
        circleButton.setSize(sf::Vector2f(100, 30));
        circleButton.setPosition(10, 10);
        circleButton.setFillColor(sf::Color::Transparent); // Remove color

        rectangleButton.setSize(sf::Vector2f(100, 30));
        rectangleButton.setPosition(120, 10);
        rectangleButton.setFillColor(sf::Color::Transparent); // Remove color

        triangleButton.setSize(sf::Vector2f(100, 30));
        triangleButton.setPosition(230, 10);
        triangleButton.setFillColor(sf::Color::Transparent); // Remove color

        circleLabel.setFont(font);
        circleLabel.setString("Circle");
        circleLabel.setCharacterSize(20);
        circleLabel.setPosition(10, 10);
        circleLabel.setFillColor(sf::Color::Black);

        rectangleLabel.setFont(font);
        rectangleLabel.setString("Rectangle");
        rectangleLabel.setCharacterSize(20);
        rectangleLabel.setPosition(120, 10);
        rectangleLabel.setFillColor(sf::Color::Black);

        triangleLabel.setFont(font);
        triangleLabel.setString("Triangle");
        triangleLabel.setCharacterSize(20);
        triangleLabel.setPosition(230, 10);
        triangleLabel.setFillColor(sf::Color::Black);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    handleMousePress(event.mouseButton);
                } else if (event.type == sf::Event::KeyPressed) {
                    handleKeyPress(event.key);
                }
            }

            window.clear();
            drawBackground(window);
            for (auto shape : shapes)
                shape->draw(window);
            window.draw(circleButton);
            window.draw(rectangleButton);
            window.draw(triangleButton);
            window.draw(circleLabel);
            window.draw(rectangleLabel);
            window.draw(triangleLabel);
            window.display();
        }
    }

    void drawBackground(sf::RenderWindow& window) {
        sf::VertexArray gradient(sf::TrianglesStrip, 4);
        gradient[0].position = sf::Vector2f(0, 0);
        gradient[1].position = sf::Vector2f(window.getSize().x, 0);
        gradient[2].position = sf::Vector2f(0, window.getSize().y);
        gradient[3].position = sf::Vector2f(window.getSize().x, window.getSize().y);

        gradient[0].color = sf::Color(255, 223, 186); // Light peach
        gradient[1].color = sf::Color(255, 200, 200); // Light pink
        gradient[2].color = sf::Color(200, 255, 255); // Light cyan
        gradient[3].color = sf::Color(255, 255, 255); // White

        window.draw(gradient);
    }

    void handleMousePress(const sf::Event::MouseButtonEvent& mouseEvent) {
        if (mouseEvent.button == sf::Mouse::Left) {
            if (circleButton.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Circle;
            } else if (rectangleButton.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Rectangle;
            } else if (triangleButton.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Triangle;
            } else {
                if (currentTool == Tool::Circle) {
                    shapes.push_back(new Circle(mouseEvent.x, mouseEvent.y, 20, currentColor));
                } else if (currentTool == Tool::Rectangle) {
                    shapes.push_back(new Rectangle(mouseEvent.x, mouseEvent.y, 40, 20, currentColor));
                } else if (currentTool == Tool::Triangle) {
                    shapes.push_back(new Triangle(mouseEvent.x, mouseEvent.y, 30, currentColor));
                }
                selectedShape = shapes.back();
            }
        }
    }

    void handleKeyPress(const sf::Event::KeyEvent& keyEvent) {
        if (keyEvent.code == sf::Keyboard::Num1) {
            currentTool = Tool::Circle;
        } else if (keyEvent.code == sf::Keyboard::Num2) {
            currentTool = Tool::Rectangle;
        } else if (keyEvent.code == sf::Keyboard::Num3) {
            currentTool = Tool::Triangle;
        } else if (keyEvent.code == sf::Keyboard::Add && selectedShape) {
            selectedShape->resize(1.1f);
        } else if (keyEvent.code == sf::Keyboard::Subtract && selectedShape) {
            selectedShape->resize(0.9f);
        } else if (keyEvent.code == sf::Keyboard::R) {
            currentColor = sf::Color::Red;
            if (selectedShape) selectedShape->setColor(currentColor);
        } else if (keyEvent.code == sf::Keyboard::G) {
            currentColor = sf::Color::Green;
            if (selectedShape) selectedShape->setColor(currentColor);
        } else if (keyEvent.code == sf::Keyboard::B) {
            currentColor = sf::Color::Blue;
            if (selectedShape) selectedShape->setColor(currentColor);
        } else if (keyEvent.code == sf::Keyboard::D && selectedShape) {
            auto it = std::find(shapes.begin(), shapes.end(), selectedShape);
            if (it != shapes.end()) {
                delete *it;
                shapes.erase(it);
                selectedShape = nullptr;
            }
        } else if (selectedShape) {
            if (keyEvent.code == sf::Keyboard::Left) {
                selectedShape->move(-5, 0);
            } else if (keyEvent.code == sf::Keyboard::Right) {
                selectedShape->move(5, 0);
            } else if (keyEvent.code == sf::Keyboard::Up) {
                selectedShape->move(0, -5);
            } else if (keyEvent.code == sf::Keyboard::Down) {
                selectedShape->move(0, 5);
            }
        }
    }

    ~ArtisticCanvas() {
        for (auto shape : shapes)
            delete shape;
    }
};

int main() {
    ArtisticCanvas app;
    app.run();
    return 0;
}
