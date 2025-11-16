#include "BodySegment.cpp"
#include "MoveableObject.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
// #include <array>
#include <cmath>
#include <iostream>
// #include "MoveableObject.cpp"
// #include <vector>

class Lizard : public MoveableObject {
public:
  // BodySegment body_parts[1];
  std::array<BodySegment, 15> body_parts;
  Lizard() {
    populateBodyParts();
    setMaxSpeed(15);
  }

  float vectorDistance(sf::Vector2f v1, sf::Vector2f v2) {
    return std::sqrt(std::pow(v2.y - v1.y, 2) + std::pow(v2.x - v1.x, 2));
  }

  void updatePosition() override {
    if (getVelocity().length() > getMaxSpeed()) {
      setVelocityMagnitude(getMaxSpeed());
      // setVelocity(sf::Vector2f(getMaxSpeed()*getVelocity().x,getMaxSpeed()*getV));
    }
    // position += velocity;
    std::cout << getVelocity().length() << '\n';
    setPosition(getPosition() + getVelocity());
    // getBodySegmentsFromIndex(0).setPosition(getPosition());
    pullBodyParts();

    // sf::CircleShape tempCirc = getBodySegmentsFromIndex(0).getShape();
    // tempCirc.setPosition(getPosition());
    // body_parts[0] = tempCirc;
    // rect.setPosition(getPosition());
    // std::cout << "lizard position: " << getPosition().x << " " <<
    // getPosition().y <<"\n";
  }

  void pullBodyParts() {

    float speed = 10;

    body_parts[0].setPosition(getPosition());
    body_parts[0].updatePosition();
    for (int i = body_parts.size() - 1; i > 0; i--) {
      float dist_to_mother_segment = vectorDistance(
          body_parts[i].getPosition(), body_parts[i - 1].getPosition());

      if (dist_to_mother_segment >
          (body_parts[i].getRadius() + body_parts[i - 1].getRadius()) + 15) {
        // body_parts[i].setPosition(moveToward(
        //       body_parts[i].getPosition(),
        //       body_parts[i-1].getPosition(),
        //       speed//getVelocity().length()
        //   ));
        body_parts[i].changeVelocity(body_parts[i - 1].getPosition() -
                                     body_parts[i].getPosition());

        body_parts[i].setVelocityMagnitude(getVelocity().length());
      }
      body_parts[i].updatePosition();
      body_parts[i].applyFriction();

      // body_parts[i].shape.setPosition(body_parts[i].getPosition());
    }
    for (int i = 1; i < body_parts.size(); i++) {
      float dist_to_mother_segment = vectorDistance(
          body_parts[i].getPosition(), body_parts[i - 1].getPosition());
      if (dist_to_mother_segment <
          (body_parts[i].getRadius() + body_parts[i - 1].getRadius())) {
        // body_parts[i].setPosition(moveToward(
        //       body_parts[i].getPosition(),
        //       body_parts[i].getPosition()-body_parts[i-1].getPosition(),
        //       speed//getVelocity().length()
        //   ));
        body_parts[i].changeVelocity(body_parts[i].getPosition() -
                                     body_parts[i - 1].getPosition());
      }

      // body_parts[i].updatePosition();
      // body_parts[i].applyFriction();
    }
  }

  void populateBodyParts() {
    // std::array<int, 2> tests;

    // std::cout << sizeof(body_parts)<<" " <<tests.size();
    for (int i = 0; i < body_parts.size(); i++) {
      std::cout << i << "\n";
      // BodySegment* new_segment = new BodySegment(getPosition(), 10 - i);
      // body_parts[i] = new_segment;
      body_parts[i].setPosition(getPosition());
      body_parts[i].setRadius((float)10 - i / 2);
      body_parts[i].setFriction(getMaxSpeed() / 2);
      // body_parts[i].setMaxSpeed(9);
      body_parts[i].setAccel(8);
      // delete new_segment;
    }
  }

  BodySegment getBodySegmentsFromIndex(int index) {
    // if (body_parts.size() = 0){ return NULL; }
    // if (index > sizeof(body_parts) ) {return NULL;}
    // if (index < 0) { return NULL; }

    return body_parts[index];
  }
};
