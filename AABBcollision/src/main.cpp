#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

// #include "Collider.cpp"
#include "SquarePlayer.cpp"
// #include <iostream>

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
  SquarePlayer obj;
  obj.setPosition(sf::Vector2f(600, 400));
  obj.updatePosition();
  while (window.isOpen()) {
    sp.changeVelocity(getInputVector());
    sp.tryMove(obj);
    // sp.updatePosition();
    sp.applyFriction();
    sp.displayCollision(obj);
    // RenderWindow
    window.display();
    window.clear();
    window.draw(sp.square);
    window.draw(obj.square);
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
