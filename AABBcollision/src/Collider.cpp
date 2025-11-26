#include <SFML/System/Vector2.hpp>
#include <iostream>

class Collider {
private:
  sf::Vector2f position;
  sf::Vector2f scale;
  const float COLLISION_MARGIN = 2;

public:
  bool isCollidingWith(Collider &otherCollider, bool use_margin = true) {
    // HARD&SOFT COLLISION for effiency's sake

    // SOFT COLLISION
    // the goal is if its far enough away to not bother checking if they are
    // colliding
    // but im lazy so shmaybe later

    // HARD COLLISION
    bool collision_x =
        getPositon().x + getScale().x >=
            otherCollider.getPositon().x + COLLISION_MARGIN * (int)use_margin &&
        otherCollider.getPositon().x + otherCollider.getScale().x >=
            getPositon().x + COLLISION_MARGIN * (int)use_margin;

    bool collision_y =
        getPositon().y + getScale().y >=
            otherCollider.getPositon().y + COLLISION_MARGIN * (int)use_margin &&
        otherCollider.getPositon().y + otherCollider.getScale().y >=
            getPositon().y + COLLISION_MARGIN * (int)use_margin;
    std::cout << getPositon().x + getScale().x - otherCollider.getPositon().x
              << " "
              << otherCollider.getPositon().x + otherCollider.getScale().x -
                     getPositon().x
              << "\n";

    return collision_x && collision_y;
  }

  bool wouldCollideWith(sf::Vector2f new_position, Collider &otherCollider) {
    sf::Vector2f old_position = getPositon();
    setPositon(new_position);
    bool would_collide = isCollidingWith(otherCollider);
    setPositon(old_position);
    return would_collide;
  }

  sf::Vector2f getPositon() { return position; }
  void setPositon(sf::Vector2f new_position) { position = new_position; }

  sf::Vector2f getScale() { return scale; }
  void setScale(sf::Vector2f new_scale) { scale = new_scale; }

  sf::Vector2f getCenter() {
    return getPositon() + sf::Vector2f(getScale().x / 2, getScale().y / 2);
  }

  float getSoftRadius() {
    // sf::Vector2f center = getCenter();
    sf::Vector2f local_center = getCenter() - getPositon();
    return local_center.length();
  }
};
