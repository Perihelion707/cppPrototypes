#include "MoveableObject.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class BodySegment : public MoveableObject {
private:
  float radius;
  // sf::Vector2f position;
public:
  sf::CircleShape shape;

  BodySegment(sf::Vector2f position, float radius) {
    setRadius(radius);
    setPosition(position);
    setShape();
  }

  BodySegment() {
    setRadius(10);
    setPosition(sf::Vector2f(0, 0));
    setShape();
  }

  void updatePosition() override {
    // position += velocity;
    if (getVelocity().length() > 0) {
      // shape.setRotation(getVelocity().angle().wrapUnsigned());
    }
    setPosition(getPosition() + getVelocity());
    // shape.setPosition(getPosition());
    shape.setPosition(getPosition());
    // setShape();
    // std::cout << getPosition().x <<"\n";
  }
  void setRadius(float radius) {
    this->radius = radius;
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius));
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

  sf::Vector2f getPointOnRadius(sf::Angle angle) {
    // getPosition()
    float x = getRadius() * cos(angle.wrapSigned().asRadians() +
                                shape.getRotation().wrapSigned().asRadians());
    float y = getRadius() * sin(angle.wrapSigned().asRadians() +
                                shape.getRotation().wrapSigned().asRadians());

    return getPosition() + sf::Vector2f(x, y);
  }
};
