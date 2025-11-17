#include "BodySegment.cpp"
#include "MoveableObject.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cmath>
#include <iostream>
// #include "MoveableObject.cpp"
// #include <vector>

class Lizard : public MoveableObject {
public:
  // BodySegment body_parts[1];
  std::array<BodySegment, 15> body_parts;
  std::array<sf::Vector2f, 15 * 2> shape_points; // has to be double body_parts
  std::array<sf::ConvexShape, 15> lizard_shapes;
  std::array<int, 15> segment_sizes = {30, 15, 35, 65, 45, 20, 10, 10,
                                       10, 10, 9,  7,  5,  3,  1

  };

  Lizard() {
    populateBodyParts();
    // lizard_shape.setPointCount(shape_points.size());
    // std::cout << lizard_shape.getPointCount();
    setLizardShape();
    setMaxSpeed(12);
  }

  float vectorDistance(sf::Vector2f v1, sf::Vector2f v2) {
    return std::sqrt(std::pow(v2.y - v1.y, 2) + std::pow(v2.x - v1.x, 2));
  }

  void updatePosition() override {
    if (getVelocity().length() > getMaxSpeed()) {
      setVelocityMagnitude(getMaxSpeed());
    }
    setPosition(getPosition() + getVelocity());
    pullBodyParts();
  }

  void pullBodyParts() {

    float speed = getMaxSpeed() - 1; // getVelocity().length();

    sf::Vector2f head_dir = getPosition() - body_parts[0].getPosition();
    if (vectorDistance(body_parts[0].getPosition(), getPosition()) > 15) {
      body_parts[0].changeVelocity(head_dir);
      body_parts[0].shape.setRotation(head_dir.normalized().angle());
      // body_parts[0].setVelocityMagnitude(getVelocity().length());
      body_parts[0].setVelocityMagnitude(speed);
    }

    for (int i = body_parts.size() - 1; i > 0; i--) {
      float dist_to_mother_segment = vectorDistance(
          body_parts[i].getPosition(), body_parts[i - 1].getPosition());

      if (dist_to_mother_segment >
          (body_parts[i].getRadius() + body_parts[i - 1].getRadius()) + 15) {
        sf::Vector2f direction =
            body_parts[i - 1].getPosition() - body_parts[i].getPosition();

        // TODO: restrict possible angles, try moving objects back if it
        // violates angle restrictions

        if (fabs(body_parts[i].getShape().getRotation().asDegrees() -
                 body_parts[i - 1].getShape().getRotation().asDegrees()) >
            135) {
          body_parts[i].changeVelocity(-direction);
          body_parts[i].shape.setRotation(direction.angle());
          body_parts[i].setVelocityMagnitude(speed);
        } else {

          body_parts[i].changeVelocity(direction);
          body_parts[i].shape.setRotation(direction.angle());
          body_parts[i].setVelocityMagnitude(speed);
        }

        // body_parts[i].changeVelocity(direction);
        // body_parts[i].shape.setRotation(direction.angle());
        // body_parts[i].setVelocityMagnitude(speed);
        std::cout << i << " "
                  << fabs(
                         body_parts[i].getShape().getRotation().asDegrees() -
                         body_parts[i - 1].getShape().getRotation().asDegrees())
                  << "\n";
        //  body_parts[i].shape.setPosition(body_parts[i].getPosition());
      }
    }
    for (int i = 1; i < body_parts.size(); i++) {
      float dist_to_mother_segment = vectorDistance(
          body_parts[i].getPosition(), body_parts[i - 1].getPosition());
      // float allowedAngles
      if (dist_to_mother_segment <
          (body_parts[i].getRadius() + body_parts[i - 1].getRadius())) {
        sf::Vector2f direction =
            body_parts[i].getPosition() - body_parts[i - 1].getPosition();
        body_parts[i].changeVelocity(direction);
      }
    }
    for (int i = 0; i < body_parts.size(); i++) {
      body_parts[i].updatePosition();
      body_parts[i].applyFriction();
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
      body_parts[i].setRadius(segment_sizes[i]);
      body_parts[i].setMaxSpeed(getMaxSpeed());
      body_parts[i].setFriction(getMaxSpeed() * .8);
      // body_parts[i].setMaxSpeed(9);
      body_parts[i].setAccel(getAccel());
      // delete new_segment;
    }
  }

  void setLizardShape() {
    getShapePointsFromParts();
    lizard_shapes[0].setPointCount(3);
    lizard_shapes[0].setPoint(0,
                              body_parts[0].getPointOnRadius(sf::degrees(0)));

    lizard_shapes[0].setPoint(1,
                              body_parts[0].getPointOnRadius(sf::degrees(-90)));

    lizard_shapes[0].setPoint(2,
                              body_parts[0].getPointOnRadius(sf::degrees(90)));

    // lizard_shapes[0].setPoint(
    //     3, body_parts[1].getPointOnRadius(sf::degrees(-90).wrapSigned()));

    // lizard_shapes[0].setPoint(
    //     4, body_parts[1].getPointOnRadius(sf::degrees(90).wrapSigned()));

    for (int i = 1; i < body_parts.size(); i++) {
      lizard_shapes[i].setPointCount(4);

      lizard_shapes[i].setPoint(
          0, body_parts[i - 1].getPointOnRadius(sf::degrees(90).wrapSigned()));

      lizard_shapes[i].setPoint(
          1, body_parts[i - 1].getPointOnRadius(sf::degrees(-90).wrapSigned()));

      lizard_shapes[i].setPoint(
          2, body_parts[i].getPointOnRadius(sf::degrees(-90).wrapSigned()));

      lizard_shapes[i].setPoint(
          3, body_parts[i].getPointOnRadius(sf::degrees(90).wrapSigned()));
    }
  }

  void getShapePointsFromParts() {
    for (int i = 0; i < body_parts.size(); i++) {
      sf::Angle angle;
      angle = sf::degrees(90);
      shape_points[i * 2] = body_parts[i].getPointOnRadius(angle);
      angle = sf::degrees(-90);
      shape_points[i * 2 + 1] = body_parts[i].getPointOnRadius(angle);
    }
    // for (int i = body_parts.size() - 1; i >= 0; i--) {
    //   sf::Angle angle;
    //   angle = sf::degrees(-90);
    //   shape_points[i + body_parts.size() ] =
    //       body_parts[i].getPointOnRadius(angle);
    // }
  }

  BodySegment getBodySegmentsFromIndex(int index) {
    // if (body_parts.size() = 0){ return NULL; }
    // if (index > sizeof(body_parts) ) {return NULL;}
    // if (index < 0) { return NULL; }

    return body_parts[index];
  }
};
