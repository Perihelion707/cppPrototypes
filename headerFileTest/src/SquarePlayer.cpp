#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
//#include "../headerFiles/SquarePlayer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

class SquarePlayer {
public:
  sf::Vector2f position = sf::Vector2f(10,10);
  sf::Vector2f velocity = sf::Vector2f(0,0);

  sf::RectangleShape square;

  float accel = 2;
  int scale = 75;
  float max_speed = 10.0;
  float friction = 1.0;

  SquarePlayer () {
    initializeSquare();
  }

  void initializeSquare() {
    square.setPosition(position);
    square.setSize(sf::Vector2f(scale, scale));
    //square.setFillColor(sf::Color::White);
    std::cout << "square initialized \n";
  }
   
  float moveToward(float movingVariable, float finalVariable, float moveAmount) {
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
  void updatePosition() {
    position += velocity;
    square.setPosition(position);
  }

  void changeVelocity(sf::Vector2f inputedDir) {
    velocity += (inputedDir * accel);
    if (std::abs(velocity.x) > max_speed) {
      if (velocity.x > 0) {
        velocity.x = max_speed;
      } else if (velocity.x < 0) {
        velocity.x = -max_speed;
      }
    }

    if (std::abs(velocity.y) > max_speed) {
      if (velocity.y > 0) {
        velocity.y = max_speed;
      } else if (velocity.y < 0) {
        velocity.y = -max_speed;
      }
    }
  }

  void applyFriction() {
    // velocity.x =
    velocity.x = moveToward(velocity.x, 0.0, friction);
    velocity.y = moveToward(velocity.y, 0.0, friction);
  }

  sf::RectangleShape getSquare(){
    return square;
  }
};
