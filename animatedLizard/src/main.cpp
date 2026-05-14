#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Angle.hpp>
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

  sf::Vector2f inputDir;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    inputDir.y = -1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    inputDir.y = 1;
  } else {
    inputDir.y = 0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    inputDir.x = -1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    inputDir.x = 1;
  } else {
    inputDir.x = 0;
  }
  if (fabs(inputDir.length()) > 0) {
    return inputDir.normalized();
  }
  return inputDir;
}

sf::Angle turn() {
  float turnAmount = 00;
  float turnSpeed = 40;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    turnAmount -= turnSpeed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    turnAmount += turnSpeed;
  }
  return sf::degrees(turnAmount);
}

sf::Vector2f angleToVec2(sf::Angle angle) {
  // soh o/h cah a/h toa o/a
  float x = cos(angle.asRadians());
  float y = sin(angle.asRadians());

  return sf::Vector2f(x, y);
}

sf::Vector2f getTurnInput(sf::Angle angle) {
  angle += turn();
  float speed = 10;
  sf::Vector2f inputDir;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    inputDir += angleToVec2(angle);
    inputDir = inputDir.normalized() * speed;
  }

  return inputDir;
}

void updateLizard(Lizard liz) {
  liz.changeVelocity(getInputVector());
  liz.updatePosition();
  // liz.applyFriction();
}

int cycleInt(int i, int cycleInt) {
  i++;
  i = i % cycleInt;
  return i;
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
  //const sf::Font font(
  //    "/usr/share/fonts/TTF/JetBrainsMonoNLNerdFontPropo-Medium.ttf");
  //sf::Text Speedometer(font, "Press [SPACE] to cycle display types.", 10);
  int displayType = 0;
  while (window.isOpen()) {

    // RenderWindow
    // window.draw(rect);

    // liz.changeVelocity(
    //     getTurnInput(liz.getBodySegmentsFromIndex(0).getShape().getRotation()),
    //     false);
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
    //window.draw(Speedometer);
    for (int i = 0; i < liz.bodyParts.size(); i++) {
      switch (displayType) {

      case 1:
        liz.setLizardLooks(true);
        window.draw(liz.getBodySegmentsFromIndex(i).getShape());
        break;
      case 2:
        window.draw(liz.getBodySegmentsFromIndex(i).getShape());
        break;
      case 3:
        window.draw(liz.lizardShapes[i]);
        window.draw(liz.getBodySegmentsFromIndex(i).getShape());
        break;
      default:
        window.draw(liz.lizardShapes[i]);
      }
    }
    window.display();
    // test if escape is pressed to close app
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        displayType = cycleInt(displayType, 4);
        std::cout << "Cycled displayType\n";
      }
    }
  }
  return 0;
};
