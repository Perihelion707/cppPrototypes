#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "BodySegment.cpp"
#include <iostream>
#include <array>
#include <cmath>
//#include <vector>

class Lizard {
  private:
    sf::Vector2f position = sf::Vector2f(10,10);
    sf::Vector2f velocity = sf::Vector2f(0,0);

    float accel = 2;
    int scale = 75;
    float max_speed = 10.0;
    float friction = 1.0;


    //std::vector<BodySegment> body_parts;
  public:
    
    //BodySegment body_parts[1]; 
    std::array<BodySegment, 15> body_parts;
    sf::RectangleShape rect;
    Lizard(){
      populateBodyParts();

      rect.setPosition(getPosition());
      rect.setScale(sf::Vector2f(40,40));
      
      //body_parts.reserve();
    }
    
    float vectorDistance(sf::Vector2f v1, sf::Vector2f v2){
      return std::sqrt(
          std::pow(v2.y -v1.y, 2) + std::pow(v2.x -v1.x,2)
          );
    }

    float moveToward(float moving_variable, float final_variable, float move_amount) {
      if (moving_variable == final_variable) {
        return moving_variable;
      }
      if (moving_variable > final_variable) {
        if (moving_variable - move_amount <= final_variable) {
          return final_variable;
        }
        return moving_variable - move_amount;
      }
      if (moving_variable < final_variable) {
        if (moving_variable + move_amount >= final_variable) {
          return final_variable;
        }
        return moving_variable + move_amount;
      }
      return moving_variable;
    }

    sf::Vector2f moveToward(
        sf::Vector2f moving_variable,
        sf::Vector2f final_variable,
        float move_amount
    ){

      return sf::Vector2f(
        moveToward(
          moving_variable.x,
          final_variable.x,
          move_amount),
        moveToward(
          moving_variable.y,
          final_variable.y,
          move_amount)
        );
    }
    void updatePosition() {
      //position += velocity;
      setPosition(getPosition()+getVelocity());
      //getBodySegmentsFromIndex(0).setPosition(getPosition());
      pullBodyParts();
      //sf::CircleShape tempCirc = getBodySegmentsFromIndex(0).getShape();
      //tempCirc.setPosition(getPosition());
      //body_parts[0] = tempCirc;
      //rect.setPosition(getPosition());
      //std::cout << "lizard position: " << getPosition().x << " " << getPosition().y <<"\n";
    }

    void pullBodyParts(){
      
      float speed = 5;


      body_parts[0].setPosition(getPosition());
      for(int i = body_parts.size()-1; i > 0 ;i--){
        float dist_to_mother_segment = vectorDistance
          (
              body_parts[i].getPosition(),
              body_parts[i-1].getPosition()
          );

        if(
            dist_to_mother_segment > (
              body_parts[i].getRadius()+body_parts[i-1].getRadius()
              )*2+5
        ) {
          body_parts[i].setPosition(moveToward(
                body_parts[i].getPosition(),
                body_parts[i-1].getPosition(),
                getVelocity().length()
            ));

          
        }
      }
    }

    void changeVelocity(sf::Vector2f inputedDir) {
      //inputedDir = inputedDir.normalized();
      setVelocity(getVelocity() + (inputedDir*accel));
      //velocity += (inputedDir * accel);
      if (std::abs(getVelocity().x) > getMaxSpeed()) {
        if (getVelocity().x > 0) {
          //velocity.x = max_speed;
          setVelocity(sf::Vector2f(getMaxSpeed(), getVelocity().y));
        } else if (getVelocity().x < 0) {
          //velocity.x = -max_speed;
          setVelocity(sf::Vector2f(-getMaxSpeed(), getVelocity().y));
        }
      }

      if (std::abs(getVelocity().y) > getMaxSpeed()) {
        if (getVelocity().y > 0) {
          //velocity.x = max_speed;
          setVelocity(sf::Vector2f(getVelocity().x, getMaxSpeed()));
        } else if (getVelocity().y < 0) {
          //velocity.x = -max_speed;
          setVelocity(sf::Vector2f(getVelocity().x,-getMaxSpeed() ));
        }
      }
    }

    void applyFriction() {
      // velocity.x =
      //velocity.x = moveToward(velocity.x, 0.0, friction);
      //velocity.y = moveToward(velocity.y, 0.0, friction);
      setVelocity(sf::Vector2f(
        moveToward(getVelocity().x, 0.0, getFriction()),
        moveToward(getVelocity().y,0.0, getFriction())
        ));
    }
    
    void populateBodyParts() {
      //std::array<int, 2> tests;

      //std::cout << sizeof(body_parts)<<" " <<tests.size();
      for(int i = 0; i < body_parts.size() ; i++){
        std::cout << i << "\n";
        //BodySegment* new_segment = new BodySegment(getPosition(), 10 - i);
        //body_parts[i] = new_segment;
        body_parts[i].setPosition(getPosition());
        body_parts[i].setRadius((float)10-i/2);
        //delete new_segment;
      }
    }


    BodySegment getBodySegmentsFromIndex(int index){
      //if (body_parts.size() = 0){ return NULL; }
      //if (index > sizeof(body_parts) ) {return NULL;}
      //if (index < 0) { return NULL; }

      return body_parts[index];
    }



    void setPosition(sf::Vector2f position){
      this->position = position;
    }
    sf::Vector2f getPosition(){
      return position;
    }

    void setVelocity(sf::Vector2f velocity){
      this->velocity = velocity;
    }
    sf::Vector2f getVelocity(){
      return velocity;
    }

    void setAccel(float accel){
      this->accel = accel;
    }
    float getAccel(){
      return accel;
    }

    void setScale(int scale){
      this->scale = scale;
    }
    int getScale(){
      return scale;
    }
    
    void setMaxSpeed(float max_speed){
      this->max_speed = max_speed;
    }
    float getMaxSpeed(){
      return max_speed;
    }

    void setFriction(float friction){
      this->friction = friction;
    }
    float getFriction(){
      return friction;
    }
};
