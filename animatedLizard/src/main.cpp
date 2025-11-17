#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
// #include "../headerFiles/SquarePlayer.hpp"
// #include "BodySegment.cpp"
//

#include "Lizard.cpp"
#include <bits/stdc++.h>

int getSign(int number) { return number / abs(number); }
float getSign(float number) { return number / std::abs(number); }

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
  if (fabs(input_dir.length()) > 0) {
    return input_dir.normalized();
  }
  return input_dir;
}
void updateLizard(Lizard liz) {
  liz.changeVelocity(getInputVector());
  liz.updatePosition();
  // liz.applyFriction();
}

int main() {
  sf::RenderWindow window(sf::VideoMode({1200, 800}), "MoveSquare",
                          sf::Style::None, sf::State::Windowed);
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(60);

  Lizard liz;

  sf::CircleShape testShape;
  testShape.setOrigin(sf::Vector2f(8, 8));
  testShape.setRadius(8);
  testShape.setPosition(sf::Vector2f(0, 0));
  testShape.setFillColor(sf::Color::Green);

  window.requestFocus();
  // const sf::Font font("arial.ttf");
  // sf::Text Speedometer("debug");

  while (window.isOpen()) {
    // RenderWindow
    // window.draw(rect);

    liz.changeVelocity(getInputVector());
    liz.updatePosition();
    liz.applyFriction();
    liz.setLizardShape();
    // string speed = std::to_string(liz.getVelocity().length());
    // stringstream test;
    // test<<speed.str()
    // Speedometer.setString(test);

    testShape.setPosition(liz.getPosition());
    // updateLizard(liz);
    window.clear();
    window.draw(testShape);
    // window.draw(liz.lizard_shape);
    //  window.draw(liz.rect);
    //  window.draw(liz.getBodySegmentsFromIndex(0).shape);
    //  window.draw(Speedometer);
    for (int i = 0; i < liz.body_parts.size(); i++) {
      window.draw(liz.lizard_shapes[i]);
      // window.draw(liz.getBodySegmentsFromIndex(i).getShape());
    }
    window.display();
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
