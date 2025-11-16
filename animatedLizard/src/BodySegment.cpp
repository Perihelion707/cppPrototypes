#include "MoveableObject.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class BodySegment : public MoveableObject {
private:
  float radius;
  // sf::Vector2f position;
public:
  sf::CircleShape shape;

  BodySegment(sf::Vector2f position, float radius) {
    setPosition(position);
    setRadius(radius);

    setShape();
  }

  BodySegment() {
    setPosition(sf::Vector2f(0, 0));
    setRadius(10);
    setShape();
  }

  void updatePosition() override {
    // position += velocity;
    setPosition(getPosition() + getVelocity());
    // shape.setPosition(getPosition());
    shape.setPosition(getPosition());
    // setShape();
    // std::cout << getPosition().x <<"\n";
  }
  void setRadius(float radius) {
    this->radius = radius;
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius / 2, radius / 2));
  }
  float getRadius() { return radius; }

  void setShape() {
    shape.setRadius(getRadius());
    shape.setPosition(getPosition());

    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setFillColor(sf::Color::Transparent);

    std::cout << "shape set\n";
  }
  sf::CircleShape getShape() { return shape; }
};
