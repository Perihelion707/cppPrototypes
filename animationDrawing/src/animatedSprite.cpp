
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class AnimatedSprite {

public:
  AnimatedSprite(sf::Texture texture_sheet) {
    this->texture_sheet = texture_sheet;
    sf::Sprite sprite(texture_sheet);
    // TODO:: make a default sprite and set it, change sprite in constructor
  }

  // void setScale(sf::Vector2f scale) { sprite.scale(scale); }
  // void setPosition(sf::Vector2f position) { sprite.setPosition(position); }

  // sf::Sprite getSprite() { return sprite; }

private:
  sf::Texture texture_sheet("/home/dpratt/Projects/cppProjects/"
                            "animationDrawing/art/DEFAULT_SPRITE.png");
  sf::Sprite sprite(texture_sheet);
};
