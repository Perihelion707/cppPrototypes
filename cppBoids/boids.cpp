#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <random>

sf::Vector2f angleToVec2(float angle) {
  float radians = angle * (sf::priv::pi / 180);
  float x = std::cos(radians);
  float y = std::sin(radians);
  return sf::Vector2f(x, y);
}
// soh cah toa
// sin opoosite/hypotnuse
// cos adjacant / hypotnuse
// toa opoosite / adjacant
sf::Vector2f angleToVec2(sf::Angle angle) {
  float radians = angle.wrapSigned().asRadians();
  float x = std::cos(radians);
  float y = std::sin(radians);
  return sf::Vector2f(x, y);
}
// TODO:: make boids turn to center, turn away from others, and turn toward
// average direction
class Boid {
public:
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Angle rotation;
  float scale = 5;
  float initial_speed = 2;
  sf::ConvexShape sprite;

  void setupSprite() {
    sprite.setPointCount(3);
    sprite.setPoint(0, sf::Vector2f(0, 5));
    sprite.setPoint(1, sf::Vector2f(0, -5));
    sprite.setPoint(2, sf::Vector2f(12, 0));
    sprite.setPosition(position);
    sprite.setRotation(rotation);
    sprite.scale(sf::Vector2f(scale, scale));
  }

  void initializeBoid() {

    int x_spawnpoint = rand() % 1200;
    int y_spawnpoint = rand() % 800;
    rotation = sf::degrees(rand() % 180);
    position = sf::Vector2f(x_spawnpoint, y_spawnpoint);
    setupSprite();

    velocity = (angleToVec2(rotation.wrapSigned().asDegrees())) * initial_speed;
    angleTurn(rotation);
    std::cout << velocity.x << " " << velocity.y << '\n';
  }

  void updatePosition() {
    position += velocity;
    sprite.setPosition(position);
  }

  void angleTurn(sf::Angle angle, float turn_weight = .2) {
    sf::Angle new_dir = sf::degrees(angle.asDegrees() * turn_weight +
                                    rotation.asDegrees() * (turn_weight));
    sprite.setRotation(sf::Angle(new_dir));
    velocity = initial_speed * angleToVec2(new_dir);
  }
  void tryLoop(sf::Vector2u bounds) {
    // sf::Vector2i looped_position =
    //    sf::Vector2i((int)position.x % bounds.x, (int)position.y % bounds.y);
    // position = sf::Vector2f(looped_position.x, looped_position.y);
    if (position.x > bounds.x + 10) {
      position.x = -5;
    }
    if (position.y > bounds.y + 10) {
      position.y = -5;
    }

    if (position.x < -10) {
      position.x = bounds.x + 5;
    }
    if (position.y < -10) {
      position.y = bounds.y + 5;
    }
  }

  sf::Angle turnToCenter(sf::Vector2u screenSize) {
    sf::Vector2f center =
        sf::Vector2f((float)screenSize.x / 2, (float)screenSize.y / 2);

    sf::Angle dir_to_center = position.angleTo(center);
    return dir_to_center;
  }

  void calculateRotation(sf::Vector2u screen_size, sf::Angle average_angle) {
    sf::Angle new_angle;
    new_angle += turnToCenter(screen_size) + average_angle;
    new_angle /= 2;
    angleTurn(new_angle, .75);
  }
};

sf::Angle getAverageAngle(int boid_amount, Boid boids[]) {
  sf::Angle total_rotation;
  for (int i = 0; i < boid_amount; i++) {
    total_rotation += sf::degrees(boids[i].rotation.asDegrees());
  }
  return total_rotation / boid_amount;
}

int main() {
  sf::RenderWindow window(sf::VideoMode({1200, 800}), "YIPPIE", sf::Style::None,
                          sf::State::Windowed);
  window.setPosition(sf::Vector2i(0, 0));
  window.setFramerateLimit(120);

  sf::RectangleShape rect;
  rect.setSize(sf::Vector2f(10, 10));
  rect.setPosition(sf::Vector2f(600, 400));

  const int boid_amount = 20;
  sf::Angle average_angle;

  Boid boids[boid_amount];
  for (int current_boid_amount = 0; current_boid_amount < boid_amount;
       current_boid_amount++) {
    srand(time({}) + current_boid_amount);

    boids[current_boid_amount].initializeBoid();
  }

  while (window.isOpen()) {
    // RenderWindow
    window.display();
    window.clear();
    float temp_rotation;
    window.draw(rect);
    for (int i = 0; i < boid_amount; i++) {
      boids[i].tryLoop(window.getSize());
      boids[i].updatePosition();
      // boids[i].turnToCenter(window.getSize());
      // boids[i].angleTurn(average_angle);
      boids[i].calculateRotation(window.getSize(), average_angle);
      window.draw(boids[i].sprite);
    }
    average_angle = getAverageAngle(boid_amount, boids);
    // window.draw(test_boid.sprite);
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        window.close();
    }
  }

  return 0;
}
