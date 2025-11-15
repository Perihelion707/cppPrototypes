#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

int getSign(int number) { return number / abs(number); }
float getSign(float number) { return number / std::abs(number); }

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

class SquarePlayer {
public:
  sf::Vector2f position;
  sf::Vector2f velocity;

  sf::RectangleShape square;

  float accel = 2;
  int scale = 75;
  float max_speed = 10.0;
  float friction = 1.0;

  void initializeSquare() {
    square.setPosition(position);
    square.setSize(sf::Vector2f(scale, scale));
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
};

sf::Vector2f getInputVector() {

  sf::Vector2f input_dir;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    input_dir.y = -1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    input_dir.y = 1;
  } else {
    input_dir.y = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    input_dir.x = -1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    input_dir.x = 1;
  } else {
    input_dir.x = 0;
  }
  return input_dir;
}

int main() {
  sf::RenderWindow window(sf::VideoMode({1200, 800}), "MoveSquare",
                          sf::Style::None, sf::State::Windowed);
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(60);
  window.display();
  window.requestFocus();
  SquarePlayer sp;
  sp.initializeSquare();
  while (window.isOpen()) {
    sp.changeVelocity(getInputVector());
    sp.updatePosition();
    sp.applyFriction();
    // RenderWindow
    window.display();
    window.clear();
    window.draw(sp.square);
    // test if escape is pressed to close app
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
    }
  }
  return 0;
};
