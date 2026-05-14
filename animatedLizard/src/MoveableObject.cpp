#include <SFML/System/Vector2.hpp>
#include <cmath>
#pragma once

class MoveableObject {
private:
  sf::Vector2f position = sf::Vector2f(10, 10);
  sf::Vector2f velocity = sf::Vector2f(0, 0);

  float accel = 2;
  int scale = 75;
  float maxSpeed = 10.0;
  float friction = 1.0;

public:
  float moveToward(
      float movingVariable,
      float finalVariable,
      float moveAmount
    ) {
      if (movingVariable == finalVariable) {
        return movingVariable;
      }
      if (movingVariable > finalVariable) {
        if (movingVariable - moveAmount <= finalVariable) {
          return finalVariable;
        }
        return movingVariable - moveAmount;
      }
      if (movingVariable < finalVariable) {
        if (movingVariable + moveAmount >= finalVariable) {
          return finalVariable;
        }
        return movingVariable + moveAmount;
      }
      return movingVariable;
  }

  sf::Vector2f moveToward(
      sf::Vector2f movingVariable,
      sf::Vector2f finalVariable,
      float moveAmount
    ) {
      return sf::Vector2f(
          moveToward(movingVariable.x, finalVariable.x, moveAmount),
          moveToward(movingVariable.y, finalVariable.y, moveAmount));
  }

  void changeVelocity(sf::Vector2f inputedDir, bool tryNormalize = true) {
    // inputedDir = inputedDir.normalized();
    if (fabs(inputedDir.length()) > 0 && tryNormalize) {
      inputedDir = inputedDir.normalized();
    } else if (tryNormalize) {
      inputedDir = sf::Vector2f(0, 0);
    }
    setVelocity(getVelocity() + (inputedDir * accel));
    // velocity += (inputedDir * accel);
    if (std::abs(getVelocity().x) > getMaxSpeed()) {
      if (getVelocity().x > 0) {
        // velocity.x = maxSpeed;
        setVelocity(sf::Vector2f(getMaxSpeed(), getVelocity().y));
      } else if (getVelocity().x < 0) {
        // velocity.x = -maxSpeed;
        setVelocity(sf::Vector2f(-getMaxSpeed(), getVelocity().y));
      }
    }

    if (std::abs(getVelocity().y) > getMaxSpeed()) {
      if (getVelocity().y > 0) {
        // velocity.x = maxSpeed;
        setVelocity(sf::Vector2f(getVelocity().x, getMaxSpeed()));
      } else if (getVelocity().y < 0) {
        // velocity.x = -maxSpeed;
        setVelocity(sf::Vector2f(getVelocity().x, -getMaxSpeed()));
      }
    }
  }

  virtual void updatePosition() {
    // position += velocity;
    setPosition(getPosition() + getVelocity());
    // getBodySegmentsFromIndex(0).setPosition(getPosition());
  }

  void applyFriction() {
    // velocity.x =
    // velocity.x = moveToward(velocity.x, 0.0, friction);
    // velocity.y = moveToward(velocity.y, 0.0, friction);
    setVelocity(sf::Vector2f(moveToward(getVelocity().x, 0.0, getFriction()),
                             moveToward(getVelocity().y, 0.0, getFriction())));
  }

  void setPosition(sf::Vector2f position) { this->position = position; }
  sf::Vector2f getPosition() { return position; }

  void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
  sf::Vector2f getVelocity() { return velocity; }

  void setVelocityMagnitude(float magnitude) {
    if (getVelocity().length() > 0) {
      this->velocity = getVelocity().normalized() * magnitude;
    }
  }

  void setAccel(float accel) { this->accel = accel; }
  float getAccel() { return accel; }

  void setScale(int scale) { this->scale = scale; }
  int getScale() { return scale; }

  void setMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
  float getMaxSpeed() { return maxSpeed; }

  void setFriction(float friction) { this->friction = friction; }
  float getFriction() { return friction; }
};
