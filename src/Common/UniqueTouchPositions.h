//
//File: UniqueTouchPositions.h
//Description:
//Author: Ivlev Alexander. Stef
//Created: 16:27 29/1/2016
//Copyright (c) SIA 2016. All Right Reserved.
//

#ifndef SIA_CAR_GAME_UNIQUE_TOUCH_POSITIONS_H_
#define SIA_CAR_GAME_UNIQUE_TOUCH_POSITIONS_H_

#include "oxygine-framework.h"

class UniqueTouchPositions {
 public:
  void addTouch(oxygine::TouchEvent* touch);
  void moveTouch(oxygine::TouchEvent* touch);
  void removeTouch(oxygine::TouchEvent* touch);
  std::vector<oxygine::Vector2> touchPositions();

 private:
  static oxygine::Vector2 sIncorrectTouch;

  std::vector<oxygine::Vector2> m_data;
};

#endif /* SIA_CAR_GAME_UNIQUE_TOUCH_POSITIONS_H_ */
