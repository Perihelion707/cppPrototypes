#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowEnums.hpp>

sf::Vector2f velocity(1, 1);
sf::Vector2f rectanlePosition(100, 100);

sf::Vector2f moveRectangle(sf::Vector2f position, sf::Vector2f velocity) {
  sf::Vector2f newPosition = position + velocity;
  // rect.setPosition(newPosition);
  return newPosition;
}

sf::Vector2f tryBounce(sf::Vector2u screenSize, sf::Vector2f rectangleSize,
                       sf::Vector2f rectanglePosition,
                       sf::Vector2i localPosition) {
  sf::Vector2f tempVelocity = velocity;

  int xBoundary = screenSize.x / 2;
  int yBoundary = screenSize.y / 2;
  int xSizeBuffer = rectangleSize.x / 2;
  int ySizeBuffer = rectangleSize.y / 2;

  if (rectanglePosition.x + rectangleSize.x > screenSize.x ||
      rectanlePosition.x < 0) {
    tempVelocity.x = velocity.x * -1;
  }
  if (rectanglePosition.y + rectangleSize.y > screenSize.y ||
      rectanlePosition.y < 0) {
    tempVelocity.y = velocity.y * -1;
  }
  return tempVelocity;
}

int main() {
  sf::RenderWindow window(sf::VideoMode({1200, 800}), "YIPPIE", sf::Style::None,
                          sf::State::Windowed);
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(120);
  sf::RectangleShape rect;
  rect.setPosition(rectanlePosition);
  rect.setSize(sf::Vector2f(100, 100));

  while (window.isOpen()) {
    sf::Vector2 screenSize = window.getSize();
    sf::Vector2 rectangleSize = rect.getSize();
    velocity = tryBounce(screenSize, rectangleSize, rectanlePosition,
                         window.getPosition());
    rectanlePosition = moveRectangle(rect.getPosition(), velocity);
    rect.setPosition(rectanlePosition);
    // RenderWindow
    window.display();
    window.clear();
    window.draw(rect);
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
    }
  }

  return 0;
}
