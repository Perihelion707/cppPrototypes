#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
// #include <iostream>

#include "animatedSprite.cpp"

int main() {
  sf::RenderWindow window(sf::VideoMode({1200, 800}), "animation test",
                          sf::Style::None, sf::State::Windowed);

  AnimatedSprite sprite;
  // sf::Texture texture(
  //     "/home/dpratt/Projects/cppProjects/animationDrawing/art/LittleGuy.png");
  //  texture.loadFromFile(
  //      "/home/dpratt/Projects/cppProjects/animationDrawing/art/LittleGuy.png",
  //      false, sf::IntRect());
  // sf::Sprite sprite(texture);

  sprite.setScale(sf::Vector2f(10, 10));
  sprite.setPosition(sf::Vector2f(500, 300));
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(60);
  window.display();
  window.requestFocus();
  while (window.isOpen()) {
    // RenderWindow

    window.clear();
    window.draw(sprite.getSprite());
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
