#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

class BodySegment {
  private:
    sf::Vector2f position;
    float radius;

  public:

    sf::CircleShape shape;

    BodySegment(
      sf::Vector2f position,
      float radius
    ){
      setPosition(position);
      setRadius(radius);

      setShape();
    }

    BodySegment(){
      setPosition(sf::Vector2f(0,0));
      setRadius(10);
      setShape();
    }
  

    void setPosition(sf::Vector2f position){
      this->position = position;
      shape.setPosition(getPosition());
      //std::cout << "part position: " << shape.getPosition().x << " " << shape.getPosition().y <<"\n";
      //std::cout << "part position: " << getPosition().x << " " << getPosition().y <<"\n";
    }

    sf::Vector2f getPosition(){
      return position;
    }
    
    void setRadius(float radius){
      this->radius = radius;
      shape.setRadius(radius);
    }
    float getRadius(){
      return radius;
    }

    void setShape() {
      shape.setRadius(getRadius());
      shape.setPosition(getPosition());
    
      shape.setOutlineColor(sf::Color::White);
      shape.setOutlineThickness(2);
      shape.setFillColor(sf::Color::Transparent);
    }
    
    sf::CircleShape getShape(){
      return shape;
    }
};
