//
// File: CarControlTouchScreenRudder.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 12:00 05/02/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _CONTROLLERS_CAR_CONTROL_TOUCH_SCREEN_RUDDER_H_
#define _CONTROLLERS_CAR_CONTROL_TOUCH_SCREEN_RUDDER_H_

#include "Common/UniqueTouchPositions.h"
#include "ICarControl.h"

#include "oxygine-framework.h"

namespace Controllers {
class CarControlTouchScreenRudder : public ICarControl {
 public:
  CarControlTouchScreenRudder(oxygine::Actor* const gameView);

 private:
  void setGameView(oxygine::Actor* const gameView);

  void update();

  void beginTouch(oxygine::TouchEvent* touch);
  void moveTouch(oxygine::TouchEvent* touch);
  void endTouch(oxygine::TouchEvent* touch);

  double enginePowerByTouches(const oxygine::Vector2& left, const oxygine::Vector2& right);
  double wheelTurnByTouches(const oxygine::Vector2& left, const oxygine::Vector2& right);

 private:
  UniqueTouchPositions m_touchPositions;
};
};

#endif /* _CONTROLLERS_CAR_CONTROL_TOUCH_SCREEN_RUDDER_H_ */