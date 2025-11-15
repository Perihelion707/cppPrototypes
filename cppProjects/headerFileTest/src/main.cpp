#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
//#include "../headerFiles/SquarePlayer.hpp"
#include "SquarePlayer.cpp"
#include <iostream>

int getSign(int number) { return number / abs(number); }
float getSign(float number) { return number / std::abs(number); }



sf::Vector2f getInputVector() {

  sf::Vector2f input_dir;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    input_dir.y = -1;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    input_dir.y = 1;
  } else {
    input_dir.y = 0; }

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
  SquarePlayer sp;

  sp.initializeSquare();
  std::cout << "penis";

  while (window.isOpen()) {
    window.clear();
    sp.changeVelocity(getInputVector());
    sp.updatePosition();
    sp.applyFriction();
    // RenderWindow
    //window.draw(sp.square);
    sf::RectangleShape rect;
    rect.setPosition(sf::Vector2f(10,10));
    rect.setSize(sf::Vector2f(100,100));
    //window.draw(rect);
    window.draw(sp.square);
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
