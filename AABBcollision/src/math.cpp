#include <iostream>

int getSign(int number) { return number / abs(number); }
float getSign(float number) { return number / std::abs(number); }

float moveToward(float movingVariable, float finalVariable, float moveAmount) {
  if (movingVariable == finalVariable) {
    return movingVariable;
  }
  if (movingVariable > finalVariable) {
    if (movingVariable - moveAmount <= finalVariable) {
      return finalVariable;
    }
    return movingVariable - moveAmount;
  }
  if (movingVariable < finalVariable) {
    if (movingVariable + moveAmount >= finalVariable) {
      return finalVariable;
    }
    return movingVariable + moveAmount;
  }
  return movingVariable;
}
