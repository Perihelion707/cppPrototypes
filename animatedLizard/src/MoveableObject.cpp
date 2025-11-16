#include <SFML/System/Vector2.hpp>
#include <cmath>
#pragma once

class MoveableObject {
private:
  sf::Vector2f position = sf::Vector2f(10, 10);
  sf::Vector2f velocity = sf::Vector2f(0, 0);

  float accel = 2;
  int scale = 75;
  float max_speed = 10.0;
  float friction = 1.0;

public:
  float moveToward(float moving_variable, float final_variable,
                   float move_amount) {
    if (moving_variable == final_variable) {
      return moving_variable;
    }
    if (moving_variable > final_variable) {
      if (moving_variable - move_amount <= final_variable) {
        return final_variable;
      }
      return moving_variable - move_amount;
    }
    if (moving_variable < final_variable) {
      if (moving_variable + move_amount >= final_variable) {
        return final_variable;
      }
      return moving_variable + move_amount;
    }
    return moving_variable;
  }

  sf::Vector2f moveToward(sf::Vector2f moving_variable,
                          sf::Vector2f final_variable, float move_amount) {

    return sf::Vector2f(
        moveToward(moving_variable.x, final_variable.x, move_amount),
        moveToward(moving_variable.y, final_variable.y, move_amount));
  }

  void changeVelocity(sf::Vector2f inputedDir, bool try_normalize = true) {
    // inputedDir = inputedDir.normalized();
    if (fabs(inputedDir.length()) > 0 && try_normalize) {
      inputedDir = inputedDir.normalized();
    } else if (try_normalize) {
      inputedDir = sf::Vector2f(0, 0);
    }
    setVelocity(getVelocity() + (inputedDir * accel));
    // velocity += (inputedDir * accel);
    if (std::abs(getVelocity().x) > getMaxSpeed()) {
      if (getVelocity().x > 0) {
        // velocity.x = max_speed;
        setVelocity(sf::Vector2f(getMaxSpeed(), getVelocity().y));
      } else if (getVelocity().x < 0) {
        // velocity.x = -max_speed;
        setVelocity(sf::Vector2f(-getMaxSpeed(), getVelocity().y));
      }
    }

    if (std::abs(getVelocity().y) > getMaxSpeed()) {
      if (getVelocity().y > 0) {
        // velocity.x = max_speed;
        setVelocity(sf::Vector2f(getVelocity().x, getMaxSpeed()));
      } else if (getVelocity().y < 0) {
        // velocity.x = -max_speed;
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

  void setMaxSpeed(float max_speed) { this->max_speed = max_speed; }
  float getMaxSpeed() { return max_speed; }

  void setFriction(float friction) { this->friction = friction; }
  float getFriction() { return friction; }
};
