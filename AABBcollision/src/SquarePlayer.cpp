#include "Collider.cpp"
#include "math.cpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
// #include <iostream>

class SquarePlayer {
private:
  sf::Vector2f position;
  sf::Vector2f velocity;

  float accel = 2;
  int scale = 75;
  float max_speed = 10.0;
  float friction = 1.0;

  void setAccel(float new_accel) { accel = new_accel; }
  void setScale(int new_scale) { scale = new_scale; }
  void setMaxSpeed(float new_max_speed) { max_speed = new_max_speed; }
  void setFriction(float new_friction) { friction = new_friction; }

public:
  sf::RectangleShape square;
  Collider col;

  SquarePlayer() { initializeSquare(); }

  void initializeSquare() {
    square.setPosition(getPosition());
    square.setSize(sf::Vector2f(getScale(), getScale()));
    col.setPositon(getPosition());
    col.setScale(square.getSize());
  }

  void setPosition(sf::Vector2f new_position) { position = new_position; }
  sf::Vector2f getPosition() { return position; }

  void setVelocity(sf::Vector2f new_velocity) { velocity = new_velocity; }
  sf::Vector2f getVelocity() { return velocity; }

  float getAccel() { return accel; }
  int getScale() { return scale; }
  float getMaxSpeed() { return max_speed; }
  float getFriction() { return friction; }

  void updatePosition() {
    // position += velocity;
    setPosition(getPosition() + getVelocity());
    square.setPosition(getPosition());
    col.setPositon(getPosition());
  }

  void changeVelocity(sf::Vector2f inputedDir) {
    setVelocity(getVelocity() + (inputedDir * getAccel()));

    if (std::abs(getVelocity().x) > getMaxSpeed()) {
      if (getVelocity().x > 0) {
        setVelocity(sf::Vector2f(getMaxSpeed(), getVelocity().y));
      } else if (getVelocity().x < 0) {
        setVelocity(sf::Vector2f(-getMaxSpeed(), getVelocity().y));
      }
    }

    if (std::abs(getVelocity().y) > getMaxSpeed()) {
      if (getVelocity().y > 0) {
        setVelocity(sf::Vector2f(getVelocity().x, getMaxSpeed()));
      } else if (getVelocity().y < 0) {
        setVelocity(sf::Vector2f(getVelocity().x, -getMaxSpeed()));
      }
    }
  }

  void applyFriction() {
    // velocity.x =
    sf::Vector2f new_velocity;
    new_velocity.x = moveToward(getVelocity().x, 0.0, getFriction());
    new_velocity.y = moveToward(getVelocity().y, 0.0, getFriction());
    setVelocity(new_velocity);
  }

  void displayCollision(SquarePlayer &object) {
    bool is_colliding = col.isCollidingWith(object.col, false);
    if (is_colliding) {
      square.setFillColor(sf::Color::Red);
    } else {
      square.setFillColor(sf::Color::White);
    }
    // std::cout << is_colliding << "\n";
  }
  void tryMove(SquarePlayer &obj) {
    if (col.wouldCollideWith(getPosition() + getVelocity(), obj.col)) {
      setVelocity(sf::Vector2f(0, 0));
      return;
    }
    updatePosition();
  }
};
