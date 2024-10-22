#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

enum class Tool { Circle, Rectangle, Triangle, Eraser };

class Shape {
public:
    virtual void draw(sf::RenderTarget& target) = 0; // Change here
    virtual void setColor(const sf::Color& color) = 0;
    virtual void resize(float factor) = 0;
    virtual void move(float dx, float dy) = 0;
    virtual void rotate(float angle) = 0;
    virtual bool contains(float x, float y) const = 0;
    virtual sf::Color getColor() const = 0;
    virtual Shape* clone() const = 0;
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
    void draw(sf::RenderTarget& target) override { // Change here
        target.draw(circle);
    }
    void setColor(const sf::Color& color) override {
        circle.setFillColor(color);
    }
    void resize(float factor) override {
        float newRadius = circle.getRadius() * factor;
        circle.setRadius(newRadius);
        circle.setPosition(circle.getPosition().x - newRadius * (factor - 1), 
                           circle.getPosition().y - newRadius * (factor - 1));
    }
    void move(float dx, float dy) override {
        circle.move(dx, dy);
    }
    void rotate(float angle) override {
        circle.rotate(angle);
    }
    bool contains(float x, float y) const override {
        return circle.getGlobalBounds().contains(x, y);
    }
    sf::Color getColor() const override {
        return circle.getFillColor();
    }
    Shape* clone() const override {
        return new Circle(circle.getPosition().x + circle.getRadius(), 
                          circle.getPosition().y + circle.getRadius(), 
                          circle.getRadius(), circle.getFillColor());
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
    void draw(sf::RenderTarget& target) override { // Change here
        target.draw(rectangle);
    }
    void setColor(const sf::Color& color) override {
        rectangle.setFillColor(color);
    }
    void resize(float factor) override {
        sf::Vector2f newSize = rectangle.getSize() * factor;
        rectangle.setSize(newSize);
        rectangle.setPosition(rectangle.getPosition().x - newSize.x * (factor - 1) / 2, 
                              rectangle.getPosition().y - newSize.y * (factor - 1) / 2);
    }
    void move(float dx, float dy) override {
        rectangle.move(dx, dy);
    }
    void rotate(float angle) override {
        rectangle.rotate(angle);
    }
    bool contains(float x, float y) const override {
        return rectangle.getGlobalBounds().contains(x, y);
    }
    sf::Color getColor() const override {
        return rectangle.getFillColor();
    }
    Shape* clone() const override {
        return new Rectangle(rectangle.getPosition().x + rectangle.getSize().x / 2, 
                             rectangle.getPosition().y + rectangle.getSize().y / 2, 
                             rectangle.getSize().x, rectangle.getSize().y, rectangle.getFillColor());
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
    void draw(sf::RenderTarget& target) override { // Change here
        target.draw(triangle);
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
    void rotate(float angle) override {
        triangle.rotate(angle);
    }
    bool contains(float x, float y) const override {
        return triangle.getGlobalBounds().contains(x, y);
    }
    sf::Color getColor() const override {
        return triangle.getFillColor();
    }
    Shape* clone() const override {
        return new Triangle(triangle.getPosition().x, triangle.getPosition().y, 
                            triangle.getPoint(2).x * 2, triangle.getFillColor());
    }
};

class ArtisticCanvas {
    sf::RenderWindow window;
    std::vector<Shape*> shapes;
    sf::Color currentColor;
    Tool currentTool;
    Shape* selectedShape;
    sf::RectangleShape colorPalette[5];
    sf::RectangleShape toolButtons[8];
    sf::Font font;
    sf::Text toolLabels[8];
    sf::VertexArray gradient;

public:
    ArtisticCanvas() : window(sf::VideoMode(1000, 700), "Artistic Canvas"), currentColor(sf::Color::Blue), currentTool(Tool::Circle), selectedShape(nullptr) {
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
        }
        setupUI();
    }

    void setupUI() {
        // Create a gradient manually
        gradient.setPrimitiveType(sf::TrianglesStrip);
        gradient.resize(4);
        gradient[0].position = sf::Vector2f(0, 0);
        gradient[1].position = sf::Vector2f(window.getSize().x, 0);
        gradient[2].position = sf::Vector2f(0, window.getSize().y);
        gradient[3].position = sf::Vector2f(window.getSize().x, window.getSize().y);

        gradient[0].color = sf::Color::White;
        gradient[1].color = sf::Color::White;
        gradient[2].color = sf::Color(255, 192, 203); // Light pink
        gradient[3].color = sf::Color(255, 192, 203);

        sf::Color paletteColors[5] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta };
        for (int i = 0; i < 5; ++i) {
            colorPalette[i].setSize(sf::Vector2f(30, 30));
            colorPalette[i].setPosition(10 + i * 40, 10);
            colorPalette[i].setFillColor(paletteColors[i]);
        }

        const char* labels[8] = { "Circle", "Rectangle", "Triangle", "Eraser", "Clear", "Duplicate", "Invert", "Download" };
        for (int i = 0; i < 8; ++i) {
            toolButtons[i].setSize(sf::Vector2f(100, 30));
            toolButtons[i].setPosition(10 + i * 110, 50);
            toolButtons[i].setFillColor(sf::Color(200, 200, 200, 150)); // Light gray with transparency
            toolLabels[i].setFont(font);
            toolLabels[i].setCharacterSize(20);
            toolLabels[i].setFillColor(sf::Color::Black);
            toolLabels[i].setString(labels[i]);
            toolLabels[i].setPosition(toolButtons[i].getPosition());
        }
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
            window.draw(gradient); // Draw the gradient
            drawUI();
            for (auto shape : shapes)
                shape->draw(window);
            window.display();
        }
    }

    void drawUI() {
        for (auto& colorBox : colorPalette)
            window.draw(colorBox);
        for (auto& button : toolButtons)
            window.draw(button);
        for (auto& label : toolLabels)
            window.draw(label);
    }

    void handleMousePress(const sf::Event::MouseButtonEvent& mouseEvent) {
        if (mouseEvent.button == sf::Mouse::Left) {
            for (int i = 0; i < 5; ++i) {
                if (colorPalette[i].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                    currentColor = colorPalette[i].getFillColor();
                    if (selectedShape) selectedShape->setColor(currentColor);
                    return;
                }
            }
            if (toolButtons[0].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Circle;
            } else if (toolButtons[1].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Rectangle;
            } else if (toolButtons[2].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Triangle;
            } else if (toolButtons[3].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                currentTool = Tool::Eraser;
            } else if (toolButtons[4].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                clearShapes();
            } else if (toolButtons[5].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                duplicateShape();
            } else if (toolButtons[6].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                invertShapeColor();
            } else if (toolButtons[7].getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                saveCanvas();
            } else {
                createShape(mouseEvent.x, mouseEvent.y);
            }
        }
    }

    void createShape(float x, float y) {
        switch (currentTool) {
            case Tool::Circle:
                shapes.push_back(new Circle(x, y, 30, currentColor));
                break;
            case Tool::Rectangle:
                shapes.push_back(new Rectangle(x, y, 60, 30, currentColor));
                break;
            case Tool::Triangle:
                shapes.push_back(new Triangle(x, y, 40, currentColor));
                break;
            case Tool::Eraser:
                eraseShape(x, y);
                return;
        }
        selectedShape = shapes.back();
    }

    void eraseShape(float x, float y) {
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if ((*it)->contains(x, y)) {
                delete *it;
                shapes.erase(it);
                break;
            }
        }
    }

    void clearShapes() {
        for (auto shape : shapes)
            delete shape;
        shapes.clear();
        selectedShape = nullptr;
    }

    void handleKeyPress(const sf::Event::KeyEvent& keyEvent) {
        if (selectedShape) {
            if (keyEvent.code == sf::Keyboard::Add) {
                selectedShape->resize(1.1f);
            } else if (keyEvent.code == sf::Keyboard::Subtract) {
                selectedShape->resize(0.9f);
            } else if (keyEvent.code == sf::Keyboard::Delete) {
                auto it = std::find(shapes.begin(), shapes.end(), selectedShape);
                if (it != shapes.end()) {
                    delete *it;
                    shapes.erase(it);
                    selectedShape = nullptr;
                }
            } else if (keyEvent.code == sf::Keyboard::Left || keyEvent.code == sf::Keyboard::A) {
                selectedShape->move(-5, 0);
            } else if (keyEvent.code == sf::Keyboard::Right || keyEvent.code == sf::Keyboard::D) {
                selectedShape->move(5, 0);
            } else if (keyEvent.code == sf::Keyboard::Up || keyEvent.code == sf::Keyboard::W) {
                selectedShape->move(0, -5);
            } else if (keyEvent.code == sf::Keyboard::Down || keyEvent.code == sf::Keyboard::S) {
                selectedShape->move(0, 5);
            } else if (keyEvent.code == sf::Keyboard::Q) {
                selectedShape->rotate(-5);
            } else if (keyEvent.code == sf::Keyboard::E) {
                selectedShape->rotate(5);
            } else if (keyEvent.code == sf::Keyboard::F) {
                moveToFront(selectedShape);
            } else if (keyEvent.code == sf::Keyboard::B) {
                moveToBack(selectedShape);
            } else if (keyEvent.code == sf::Keyboard::C) {
                duplicateShape();
            } else if (keyEvent.code == sf::Keyboard::I) {
                invertShapeColor();
            } else if (keyEvent.code == sf::Keyboard::S) {
                saveCanvas();
            }
        }
    }

    void moveToFront(Shape* shape) {
        auto it = std::find(shapes.begin(), shapes.end(), shape);
        if (it != shapes.end()) {
            shapes.erase(it);
            shapes.push_back(shape);
        }
    }

    void moveToBack(Shape* shape) {
        auto it = std::find(shapes.begin(), shapes.end(), shape);
        if (it != shapes.end()) {
            shapes.erase(it);
            shapes.insert(shapes.begin(), shape);
        }
    }

    void duplicateShape() {
        if (selectedShape) {
            Shape* newShape = selectedShape->clone();
            newShape->move(10, 10); // Slight offset for visibility
            shapes.push_back(newShape);
            selectedShape = newShape;
        }
    }

    void invertShapeColor() {
        if (selectedShape) {
            sf::Color color = selectedShape->getColor();
            sf::Color invertedColor(255 - color.r, 255 - color.g, 255 - color.b);
            selectedShape->setColor(invertedColor);
        }
    }

    void saveCanvas() {
        sf::RenderTexture renderTexture;
        renderTexture.create(window.getSize().x, window.getSize().y);
        renderTexture.clear();
        renderTexture.draw(gradient); // Draw the gradient
        for (auto shape : shapes)
            shape->draw(renderTexture);
        renderTexture.display();

        sf::Texture texture = renderTexture.getTexture();
        sf::Image screenshot = texture.copyToImage();
        screenshot.saveToFile("artwork.png");
    }

    ~ArtisticCanvas() {
        clearShapes();
    }
};

int main() {
    ArtisticCanvas app;
    app.run();
    return 0;
}
