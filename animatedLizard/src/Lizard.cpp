#include "BodySegment.cpp"
#include "MoveableObject.cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cmath>
#include <iostream>
#pragma once
// #include "MoveableObject.cpp"
// #include <vector>

class Lizard : public MoveableObject {
public:
  // BodySegment body_parts[1];
  bool spiteFilled = true;
  std::array<BodySegment, 30> bodyParts;
  std::array<sf::Vector2f, 30 * 2> shapePoints; // has to be double body_parts
  std::array<sf::ConvexShape, 30> lizardShapes;
  std::array<int, 30> segmentSizes = {
      20, 30, 10, 15, 35, 45, 65, 65, 45, 40, 25, 20, 15, 10, 10, 10,
      10, 10, 10, 10, 9,  9,  7,  7,  5,  5,  5,  5,  5,  5

  };
  
  Lizard() {
    populateBodyParts();
    // lizard_shape.setPointCount(shapePoints.size());
    // std::cout << lizard_shape.getPointCount();
    setLizardShape();
    setLizardLooks();
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
    
    sf::Vector2f headDir = getPosition() - bodyParts[0].getPosition();
    if (headDir.length() > 20) {
      bodyParts[0].setPosition(moveToward(
          bodyParts[0].getPosition(),
          bodyParts[0].getPosition() + headDir.normalized() * speed, 15));
      bodyParts[0].shape.setRotation(headDir.normalized().angle());
    }
    for (int i = 1; i < bodyParts.size(); i++) {
      float distToMotherSegment = vectorDistance(
          bodyParts[i].getPosition(), bodyParts[i - 1].getPosition());
      float followDist =
          (bodyParts[i].getRadius() + bodyParts[i - 1].getRadius() + 5);
      sf::Vector2f direction =
          bodyParts[i - 1].getPosition() - bodyParts[i].getPosition();
      if (distToMotherSegment > followDist) {

        // TODO: restrict possible angles, try moving objects back if it
        // violates angle restrictions
        float moveAmount = distToMotherSegment / 2;
        bodyParts[i].setPosition(moveToward(
            bodyParts[i].getPosition(),
            bodyParts[i].getPosition() + (direction.normalized() * speed),
            15));
        bodyParts[i].shape.setRotation(direction.angle());
      }
    }
    for (int i = 0; i < bodyParts.size(); i++) {
      bodyParts[i].updatePosition();
      bodyParts[i].applyFriction();
    }
  }
  void populateBodyParts() {
    // std::array<int, 2> tests;

    // std::cout << sizeof(body_parts)<<" " <<tests.size();
    for (int i = 0; i < bodyParts.size(); i++) {
      std::cout << i << "\n";
      // BodySegment* new_segment = new BodySegment(getPosition(), 10 - i);
      // body_parts[i] = new_segment;
      bodyParts[i].setPosition(getPosition());
      bodyParts[i].setRadius(segmentSizes[i]);
      bodyParts[i].setMaxSpeed(getMaxSpeed());
      bodyParts[i].setFriction(getMaxSpeed() * .8);
      // body_parts[i].setMaxSpeed(9);
      bodyParts[i].setAccel(getAccel());
      // delete new_segment;
    }
  }
  void setLizardLooks(bool filled = false) {
    for (int i = 0; i < lizardShapes.size(); i++) {
      lizardShapes[i].setOutlineThickness(2);
      lizardShapes[i].setOutlineColor(sf::Color::White);
      if (!filled)
        lizardShapes[i].setFillColor(sf::Color::Transparent);
    }
  }
  void setLizardShape() {
    getShapePointsFromParts();
    lizardShapes[0].setPointCount(3);
    lizardShapes[0].setPoint(0,
                              bodyParts[0].getPointOnRadius(sf::degrees(0)));

    lizardShapes[0].setPoint(1,
                              bodyParts[0].getPointOnRadius(sf::degrees(-90)));

    lizardShapes[0].setPoint(2,
                              bodyParts[0].getPointOnRadius(sf::degrees(90)));

    for (int i = 1; i < bodyParts.size(); i++) {
      lizardShapes[i].setPointCount(4);

      lizardShapes[i].setPoint(
          0, bodyParts[i - 1].getPointOnRadius(sf::degrees(90).wrapSigned()));

      lizardShapes[i].setPoint(
          1, bodyParts[i - 1].getPointOnRadius(sf::degrees(-90).wrapSigned()));

      lizardShapes[i].setPoint(
          2, bodyParts[i].getPointOnRadius(sf::degrees(-90).wrapSigned()));

      lizardShapes[i].setPoint(
          3, bodyParts[i].getPointOnRadius(sf::degrees(90).wrapSigned()));
    }
  }

  void getShapePointsFromParts() {
    for (int i = 0; i < bodyParts.size(); i++) {
      sf::Angle angle;
      angle = sf::degrees(90);
      shapePoints[i * 2] = bodyParts[i].getPointOnRadius(angle);
      angle = sf::degrees(-90);
      shapePoints[i * 2 + 1] = bodyParts[i].getPointOnRadius(angle);
    }
  }

  BodySegment getBodySegmentsFromIndex(int index) {
    return bodyParts[index];
  }
};
