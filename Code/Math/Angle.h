#ifndef CHALLENGE_ANGLE_HPP
#define CHALLENGE_ANGLE_HPP

#include <Math\Constants.h>


  inline float Degree(const float& _value){
    return ( 360 * _value / Constants::TAU );
  }

  inline float Radian(const float& _value){
    return ( _value * Constants::TAU / 360 );
  }
#endif // !namespace Challenge
